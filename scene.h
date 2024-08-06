#pragma once

#include <QPainter>
#include <QtWidgets/qwidget.h>
#include <QtGui/qevent.h>
#include "controller.h"
#include "model.h"

class Scene : public QWidget
{
public:
    Scene(QWidget* parent = nullptr);
    void paintEvent(QPaintEvent* event) override;
    ~Scene();

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
