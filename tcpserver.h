#include "itcpserver.h"
#include <map>

class TicTacToeClientSession;

class ITicTacToeServer
{
public:
    using ClientName = const std::string;

    virtual bool addClient( ClientName&, const std::weak_ptr<TicTacToeClientSession>&, std::string& errorText ) = 0;
};

class TicTacToeClientSession: public TcpClientSession
{
    ITicTacToeServer& m_ticTacToeServer;

public:
    TicTacToeClientSession( ITicTacToeServer& ticTacToeServer, boost::asio::ip::tcp::socket&& socket )
        :
        TcpClientSession( std::move(socket) ), m_ticTacToeServer(ticTacToeServer)
    {}

    void onMessage( const std::string& request ) override
    {
        std::cout << "TicTacToeClientSession::onMessage: " << request;

        if ( request.empty() || request.back() != '\0' )
        {
            std::cerr << "TcpClientSession bad request: " << request << std::endl;
            return;
        }

        std::vector<std::string> tokens;
        boost::split( tokens, request, boost::is_any_of(",") );

        std::string command = tokens[0];

        if ( command == "Hello" )
        {
            if ( tokens.size() < 2 )
            {
                std::cerr << "TcpClientSession bad request (2): " << request << std::endl;
                return;
            }

            auto playerName = tokens[1];
            std::cout << "playerName: " << playerName << std::endl;

            std::string errorText;
            if ( ! m_ticTacToeServer.addClient( playerName, std::dynamic_pointer_cast<TicTacToeClientSession>( shared_from_this() ), errorText ) )
            {
                std::string response = "Failed," + errorText;
                write( response );
                return;
            }

            std::string response = "Ok";
            write( response );
            read();
        }
        else if ( command == "Bye" )
        {
        }
        else if ( command == "GetPlayers" )
        {
        }
        else if ( command == "Turn" )
        {
        }
    }
};

class TicTacToeServer: public TcpServer, public ITicTacToeServer
{
    std::map<ClientName,std::weak_ptr<TicTacToeClientSession>> m_clientMap;

public:
    TicTacToeServer( const std::string& addr, const std::string& port ) : TcpServer( addr, port ) {}

    virtual std::shared_ptr<TcpClientSession> createSession( boost::asio::ip::tcp::socket&& socket ) override
    {
        auto ptr = std::make_shared<TicTacToeClientSession>( *this, std::move(socket) );
        return ptr->shared_from_this();
    }

    virtual bool addClient( ClientName& clientName, const std::weak_ptr<TicTacToeClientSession>& session, std::string& errorText ) override
    {
        std::cout << "TicTacServer::addClient: " << clientName;
        if ( auto it = m_clientMap.find( clientName ); it != m_clientMap.end() )
        {
            return false;
        }

        m_clientMap[clientName] = session;
        return true;
    }
};
