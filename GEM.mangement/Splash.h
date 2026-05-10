#pragma once
#ifndef SPLASH_H
#define SPLASH_H

#include <QMainWindow>

namespace Ui {
    class Splash;
}

class Splash : public QMainWindow
{
    Q_OBJECT

public:
    explicit Splash(QWidget* parent = nullptr);
    ~Splash();

private slots:
    
    void on_btnManageMembers_clicked();
    void on_btnManageCoaches_clicked();
    void on_btnPayment_clicked();
    void on_btnLogout_clicked();

private:
    Ui::Splash* ui;
};

#endif 