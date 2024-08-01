#pragma once

#include <QPainter>
#include <QtWidgets/qwidget.h>
#include <QtGui/qevent.h>
#include "Controller.h"
#include "Model.h"

class Stage : public QWidget
{
public:
    Stage(QWidget* parent = nullptr);
    void paintEvent(QPaintEvent* event) override;
    ~Stage();

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:
    void drawField(QPainter& painter);
    void drawX(QPainter& painter, int row, int col);
    void drawO(QPainter& painter, int row, int col);
    void drawGameResult(QPainter& painter);

    Model* m_model;
    Controller* m_controller;
};
