#ifndef COACHS_H
#define COACHS_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QModelIndex>

QT_BEGIN_NAMESPACE
namespace Ui { class Coachs; }
QT_END_NAMESPACE

class Coachs : public QMainWindow {
    Q_OBJECT

public:
    Coachs(QWidget* parent = nullptr);
    ~Coachs();

private slots:
    void on_Addbtn_clicked();     // إضافة مدرب
    void on_Editbtn_clicked();    // تعديل مدرب
    void on_DeleteBtn_clicked();  // حذف مدرب
    void on_CoachTable_clicked(const QModelIndex& index); // اختيار من الجدول
    void displayCoachs();         // عرض البيانات
    int countCoach();             // حساب المعرف القادم

private:
    Ui::Coachs* ui;
    QSqlDatabase db;
    int key = 0; // المعرف المختار
};

#endif // COACHS_H