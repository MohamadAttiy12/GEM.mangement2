#include "Splash.h"
#include "ui_splash.h"
#include "Members.h"  // شاشة الأعضاء التي قمنا بتحويلها سابقاً
#include "Coachs.h"   // شاشة المدربين
#include "Finance.h"  // شاشة المدفوعات
#include "Login.h"    // شاشة تسجيل الدخول

Splash::Splash(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::Splash)
{
    ui->setupUi(this);

    // لإزالة إطار النافذة (يجعلها Undecorated مثل كود Java الخاص بك)
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    // لجعل النافذة في منتصف الشاشة
    this->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            this->size(),
            qApp->desktop()->availableGeometry()
        )
    );
}

Splash::~Splash()
{
    delete ui;
}

// الانتقال لصفحة إدارة الأعضاء
void Splash::on_btnManageMembers_clicked()
{
    Members* membersPage = new Members();
    membersPage->show();
    this->close();
}

void Splash::on_btnManageCoaches_clicked()
{
    Coachs* coachesPage = new Coachs();
    coachesPage->show();
    this->close();
}

void Splash::on_btnPayment_clicked()
{
    Finance* financePage = new Finance();
    financePage->show();
    this->close();
}

void Splash::on_btnLogout_clicked()
{
    Login* loginPage = new Login();
    loginPage->show();
    this->close();
}