#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , m_stage(new Stage())
{
    setFixedSize(600, 600);
    setCentralWidget(m_stage);
}

MainWindow::~MainWindow() {
    delete m_stage;
}
