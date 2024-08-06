#pragma once

#include <QObject>
#include "model.h"

class Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(Model *model, QObject* parent = nullptr);

    void handleClicked(int row, int col);

private:
    Model* m_model;
};
