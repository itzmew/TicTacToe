#pragma once

#include <QMainWindow>
#include "Scene.h"
#include <ui_MainWindow.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Stage* m_stage;
    Ui::MainWindow* ui;
};
