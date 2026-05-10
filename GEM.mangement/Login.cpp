#include "Login.h"
#include "ui_login.h"
#include "Splash.h" 

Login::Login(QWidget* parent) : QMainWindow(parent), ui(new Ui::Login) {
    ui->setupUi(this);

   
    ui->jpassword->setEchoMode(QLineEdit::Password);
}

Login::~Login() {
    delete ui;
}


void Login::on_blogin_clicked() {
    QString username = ui->jtuser->text();
    QString password = ui->jpassword->text();

    if (username.isEmpty()) {
        QMessageBox::warning(this, "Message", "Please fill out the UserName");
    }
    else if (password.isEmpty()) {
        QMessageBox::warning(this, "Message", "Please fill out the Password");
    }
    
    else if (username == "Admin" && password == "987654321") {
        QMessageBox::information(this, "Message", "Login Successful!");

       
        Splash* splash = new Splash();
        splash->show();
        this->close();
    }
    else {
        QMessageBox::critical(this, "Message", "Wrong username or password!");
    }
}

void Login::on_jcshow_password_toggled(bool checked) {
    if (checked) {
        ui->jpassword->setEchoMode(QLineEdit::Normal);
    }
    else {
        ui->jpassword->setEchoMode(QLineEdit::Password); 
    }
}



void Login::on_bexit_clicked() {
    exit(0);
}