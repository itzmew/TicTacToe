#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "settingsdialog.h"
#include "QDebug"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionSettings, &QAction::triggered, this, [this]
            {
                SettingsDialog dialog(this);
                if(dialog.exec() == QDialog::Accepted)
                {
                    qDebug() << "Accepted";
                }
            });
}


MainWindow::~MainWindow() {
    delete ui;
}
