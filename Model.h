#pragma once

#include <QObject>

class Model : public QObject
{
    Q_OBJECT

public:
    explicit Model(QObject* parent = nullptr);
    void attemptToTurn(int row, int col);
    void botTurn();
    bool getIsGameStarted();
    void setIsGameStarted(bool isGameStarted);
    void setisPlayerTurn(bool isPlayerTurn);
    enum PlayerFieldState { Empty, X, O };
    enum GameState { Unfinished, Draw, PlayerWin, BotWin };
    void setPlayerFighter(PlayerFieldState playerFieldState);
    void setBotFighter(PlayerFieldState playerFieldState);
    PlayerFieldState getSquare(int row, int col) const;
    GameState findWinner();

signals:
    void stateChanged();

private:
    void setSquare(int row, int col, PlayerFieldState playerFieldState);
    PlayerFieldState m_playerFighter;
    PlayerFieldState m_botFighter;
    bool m_isGameStarted;
    bool m_isPlayerTurn;
    QVector<QVector<PlayerFieldState>> m_gameField;
    bool isFieldEmpty(int row, int col);
    void makeTurn(int row, int col, PlayerFieldState state);
    std::pair<int, int> findBestMove();
    void updateBestMove(int score, int row, int col, int& bestScore, int& bestRow, int& bestCol);
    int minimax(QVector<QVector<PlayerFieldState>> &field, int depth, bool isMaximizing);
    int evaluateMove(QVector<QVector<PlayerFieldState>> &field, int depth, bool isMaximizing);
    GameState checkLine(PlayerFieldState a, PlayerFieldState b, PlayerFieldState c);
    GameState checkRows();
    GameState checkCols();
    GameState checkDiags();
    bool isFieldFull();
};
