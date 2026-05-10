#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QMessageBox>

namespace Ui { class Login; }

class Login : public QMainWindow {
    Q_OBJECT

public:
    explicit Login(QWidget* parent = nullptr);
    ~Login();

private slots:
    void on_blogin_clicked();          
    void on_bexit_clicked();           
    void on_jcshow_password_toggled(bool checked); 

private:
    Ui::Login* ui;
    void initComponents();
};

#endif 