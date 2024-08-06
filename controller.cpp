#include "controller.h"

Controller::Controller(Model* model, QObject* parent)
    : QObject(parent)
    , m_model(model)
{
}

void Controller::handleClicked(int row, int col) {
    m_model->attemptToTurn(row, col);
}
