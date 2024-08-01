#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    //, m_stage(new Stage())
{
    ui->setupUi(this);
    /*setFixedSize(600, 600);
    setCentralWidget(m_stage);*/
}

MainWindow::~MainWindow() {
    //delete m_stage;
    delete ui;
}
