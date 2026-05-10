#ifndef MEMBERS_H
#define MEMBERS_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QMessageBox>

namespace Ui { class Members; }

class Members : public QMainWindow {
    Q_OBJECT

public:
    explicit Members(QWidget* parent = nullptr);
    ~Members();

private slots:
    void on_AddBtn_clicked();
    void on_EditBtn_clicked();
    void on_DeleteBtn_clicked();
    void on_MemberTable_clicked(const QModelIndex& index);
    void on_labelCoaches_clicked(); 

private:
    Ui::Members* ui;
    QSqlDatabase db;
    int Key = 0; 

    void DisplayMembers();
    void GetCoach();
    int CountMember();
    void setupDatabase();
};

#endif 