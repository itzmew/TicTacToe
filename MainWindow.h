#pragma once

#include <QMainWindow>
#include "scene.h"
#include <ui_MainWindow.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Scene* m_scene;
    Ui::MainWindow* ui;
};
