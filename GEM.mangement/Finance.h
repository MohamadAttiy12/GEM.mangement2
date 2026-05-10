#ifndef FINANCE_H
#define FINANCE_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QUrl>
#include <QDate>

namespace Ui { class Finance; }

class Finance : public QMainWindow {
    Q_OBJECT

public:
    explicit Finance(QWidget* parent = nullptr);
    ~Finance();

private slots:
    void on_Savebtn_clicked();     // حفظ الدفع
    void on_Resetbtn_clicked();    // إعادة ضبط الحقول
    void on_Searchbtn_clicked();   // البحث برقم الهاتف
    void on_MemberCb_currentIndexChanged(const QString& arg1); // جلب المبلغ عند اختيار العضو

private:
    Ui::Finance* ui;
    QSqlDatabase db;
    void connectDatabase();
    void displayPayment();
    void getMembers();
    void generateReceipt(QString member, QString date, QString amount);
    void resetFields();
};

#endif