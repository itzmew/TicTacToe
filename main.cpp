#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <iostream>

#include <QApplication>

#include "tcpserver.h"

void runClient()
{
    try
    {
        boost::asio::io_context         context;
        boost::asio::ip::tcp::socket    socket(context);

        boost::asio::ip::tcp::resolver  resolver(context);
        auto endpoints = resolver.resolve( "localhost", "15001" );

        boost::asio::connect( socket, endpoints );

        boost::asio::write( socket, boost::asio::buffer("Hello,Player1") );

        std::string response;
        boost::asio::read_until( socket, boost::asio::dynamic_buffer(response), "\0" );

        std::cout << "Client received response: " << response << std::endl;
    }
    catch( std::runtime_error& exception )
    {
        std::cerr << "Client exception: " << exception.what() << std::endl;
    }
    catch( ... )
    {
        std::cerr << "Client exception: ..." << std::endl;
    }
}

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    TicTacToeServer server( "127.0.0.1", "15001" );
    std::thread( [&server] { server.run(); }).detach();

    usleep(1000);

    runClient();

    return a.exec();
}
