#pragma once

#include <QDialog>
#include <QAbstractButton>
#include <QDebug>

#include "src/preferences.h"

namespace Ui {
class PreferencesDialog;
}

class PreferencesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PreferencesDialog(QWidget *parent = 0);
    ~PreferencesDialog();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::PreferencesDialog *ui;
};
