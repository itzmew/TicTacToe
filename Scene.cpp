#include "Scene.h"

Stage::Stage(QWidget* parent)
    : m_model(new Model(this))
    , m_controller(new Controller(m_model, this))
{
    connect(m_model, &Model::stateChanged, this, QOverload<>::of(&Stage::update));
}

Stage::~Stage() {
    delete m_model;
    delete m_controller;
}

void Stage::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    drawField(painter);

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (m_model->getSquare(row, col) == Model::X) {
                drawX(painter, row, col);
            } else if (m_model->getSquare(row, col) == Model::O) {
                drawO(painter, row, col);
            }
        }
    }
    drawGameResult(painter);
}

void Stage::mousePressEvent(QMouseEvent* event) {
    int row = event->position().y() / (height() / 3);
    int col = event->position().x() / (width() / 3);
    m_controller->handleClicked(row, col);
}

void Stage::drawField(QPainter& painter) {
    int fieldWidth = width();
    int fieldHeight = height();

    for (int i = 1; i < 3; ++i) {
        painter.drawLine(i * fieldWidth / 3, 0, i * fieldWidth / 3, fieldHeight);
        painter.drawLine(0, i * fieldHeight / 3, fieldWidth, i * fieldHeight / 3);
    }
}

void Stage::drawX(QPainter& painter, int row, int col) {
    painter.setPen(QPen(Qt::red, 3));
    int squareWidth = width() / 3;
    int squareHeight = height() / 3;
    int margin = 10;

    painter.drawLine(col * squareWidth + margin, row * squareHeight + margin, (col + 1) * squareWidth - margin, (row + 1) * squareHeight - margin);
    painter.drawLine((col + 1) * squareWidth - margin, row * squareHeight + margin, col * squareWidth + margin, (row + 1) * squareHeight - margin);
}

void Stage::drawO(QPainter& painter, int row, int col) {
    painter.setPen(QPen(Qt::blue, 3));
    int squareWidth = width() / 3;
    int squareHeight = height() / 3;
    int margin = 10;

    painter.drawEllipse(col * squareWidth + margin, row * squareHeight + margin, squareWidth - 2 * margin, squareHeight - 2 * margin);
}

void Stage::drawGameResult(QPainter& painter) {
    Model::GameState gameState = m_model->findWinner();

    QString resultText;
    switch (gameState) {
    case Model::BotWin:
        resultText = "Bot Wins!";
        break;
    case Model::PlayerWin:
        resultText = "Player Wins!";
        break;
    case Model::Draw:
        resultText = "It's a Draw!";
        break;
    default:
        return;
    }

    painter.setPen(Qt::green);
    painter.setFont(QFont("Arial", 48, QFont::Bold));
    painter.drawText(rect(), Qt::AlignCenter, resultText);
}

