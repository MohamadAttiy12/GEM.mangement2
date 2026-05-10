#include "Dashboard.h"
#include "Login.h" // نفترض وجود كلاس Login للواجهة التالية
#include <QPixmap>
#include <QFont>

Dashboard::Dashboard(QWidget* parent) : QMainWindow(parent) {
    initComponents();
}

Dashboard::~Dashboard() {}

void Dashboard::initComponents() {
    // إعداد النافذة الأساسية
    this->setFixedSize(450, 450); // تحديد مقاس ثابت للنافذة
    this->setWindowFlags(Qt::FramelessWindowHint); // جعل النافذة بدون إطار (Undecorated)
    this->setStyleSheet("background-color: white;");

    // 1. عنوان "Fitness Spot"
    titleLabel = new QLabel("Fitness Spot", this);
    titleLabel->setFont(QFont("Arial Black", 24));
    titleLabel->setGeometry(100, 10, 250, 40);

    // 2. الصورة (Image Label)
    imageLabel = new QLabel(this);
    QPixmap pixmap("D:/Gym Project/frontimage.jpg"); // مسار الصورة
    imageLabel->setPixmap(pixmap.scaled(330, 280, Qt::KeepAspectRatio));
    imageLabel->setGeometry(60, 60, 330, 280);

    // 3. زر Login
    loginButton = new QPushButton("Login", this);
    loginButton->setFont(QFont("Sitka Text", 18));
    loginButton->setGeometry(140, 340, 150, 40);
    loginButton->setStyleSheet("background-color: #006666; color: white; border-radius: 10px;");

    // 4. نص "to Proceed"
    proceedLabel = new QLabel("to Proceed", this);
    proceedLabel->setGeometry(150, 385, 100, 20);
    proceedLabel->setAlignment(Qt::AlignCenter);

    // ربط الحدث (Action Listener)
    connect(loginButton, &QPushButton::clicked, this, &Dashboard::onLoginClicked);
}

void Dashboard::onLoginClicked() {
    // فتح واجهة Login وإغلاق الحالية
    Login* loginWindow = new Login();
    loginWindow->show();
    this->close();
}