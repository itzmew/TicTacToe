#pragma once
#include <QDialog>
#include "configmanager.h"

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

private slots:
    void onSaveButtonClicked();

private:
    Ui::SettingsDialog *ui;
    ConfigManager* m_configManager;
    void loadSettings();
    void saveSettings();
};

