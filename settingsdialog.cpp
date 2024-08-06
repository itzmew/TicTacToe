#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QMessageBox>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog),
    m_configManager(new ConfigManager("config.ini"))
{
    ui->setupUi(this);

    loadSettings();

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &SettingsDialog::onSaveButtonClicked);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
    delete m_configManager;
}

void SettingsDialog::loadSettings()
{
    auto config = m_configManager->readConfig();

    ui->m_user->setText(QString::fromStdString(config["username"]));
    ui->m_address->setText(QString::fromStdString(config["address"]));
    ui->m_port->setText(QString::fromStdString(config["port"]));
}

void SettingsDialog::saveSettings()
{
    std::map<std::string, std::string> config;
    config["username"] = ui->m_user->text().toStdString();
    config["address"] = ui->m_address->text().toStdString();
    config["port"] = ui->m_port->text().toStdString();

    m_configManager->saveConfig(config);
}

void SettingsDialog::onSaveButtonClicked()
{
    saveSettings();
    QMessageBox::information(this, "Settings", "Settings have been saved successfully.");
}
