#include "coachs.h"
#include "ui_coachs.h"

Coachs::Coachs(QWidget* parent) : QMainWindow(parent), ui(new Ui::Coachs) {
    ui->setupUi(this);

    // إعداد الاتصال بقاعدة البيانات MySQL
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("gymdb");
    db.setUserName("root");
    db.setPassword("");

    if (!db.open()) {
        QMessageBox::critical(this, "Error", "Database Connection Failed!");
    }

    displayCoachs();
}

Coachs::~Coachs() {
    delete ui;
}

// عرض المدربين في الجدول (DisplayCoachs)
void Coachs::displayCoachs() {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query("SELECT * FROM CoachTbl", db);
    model->setQuery(query);
    ui->CoachTable->setModel(model);
}

// حساب المعرف القادم (CountCoach)
int Coachs::countCoach() {
    QSqlQuery query("SELECT MAX(CId) FROM CoachTbl", db);
    if (query.next()) {
        return query.value(0).toInt() + 1;
    }
    return 1;
}

// منطق زر الإضافة (AddbtnMouseClicked)
void Coachs::on_Addbtn_clicked() {
    if (ui->CNameTb->text().isEmpty() || ui->CPhoneTb->text().isEmpty()) {
        QMessageBox::warning(this, "Missing Information", "Please fill all fields!");
    }
    else {
        int nextId = countCoach();
        QSqlQuery query;
        query.prepare("INSERT INTO CoachTbl (CId, CName, CPhone, CAge, CAddress, CGen) "
            "VALUES (:id, :name, :phone, :age, :address, :gen)");
        query.bindValue(":id", nextId);
        query.bindValue(":name", ui->CNameTb->text());
        query.bindValue(":phone", ui->CPhoneTb->text());
        query.bindValue(":age", ui->CAgeTb->text().toInt());
        query.bindValue(":address", ui->CAddTb->text());
        query.bindValue(":gen", ui->CGenCb->currentText());

        if (query.exec()) {
            QMessageBox::information(this, "Success", "Trainer Saved");
            displayCoachs();
        }
        else {
            QMessageBox::critical(this, "Error", query.lastError().text());
        }
    }
}

// اختيار صف من الجدول (CoachTableMouseClicked)
void Coachs::on_CoachTable_clicked(const QModelIndex& index) {
    int row = index.row();
    key = ui->CoachTable->model()->index(row, 0).data().toInt();
    ui->CNameTb->setText(ui->CoachTable->model()->index(row, 1).data().toString());
    ui->CPhoneTb->setText(ui->CoachTable->model()->index(row, 2).data().toString());
    ui->CAgeTb->setText(ui->CoachTable->model()->index(row, 3).data().toString());
    ui->CAddTb->setText(ui->CoachTable->model()->index(row, 4).data().toString());
    ui->CGenCb->setCurrentText(ui->CoachTable->model()->index(row, 5).data().toString());
}

// منطق زر الحذف (DeleteBtnMouseClicked)
void Coachs::on_DeleteBtn_clicked() {
    if (key == 0) {
        QMessageBox::warning(this, "Selection", "Select a Coach to Delete");
    }
    else {
        QSqlQuery query;
        query.prepare("DELETE FROM CoachTbl WHERE CId = :id");
        query.bindValue(":id", key);

        if (query.exec()) {
            QMessageBox::information(this, "Success", "Coach Deleted");
            displayCoachs();
            key = 0; // إعادة تعيين المفتاح
        }
    }
}

// منطق زر التعديل (EditbtnMouseClicked)
void Coachs::on_Editbtn_clicked() {
    if (key == 0) {
        QMessageBox::warning(this, "Selection", "Please Select a Member to Edit");
    }
    else {
        QSqlQuery query;
        query.prepare("UPDATE CoachTbl SET CName=:name, CPhone=:phone, CAge=:age, "
            "CAddress=:address, CGen=:gen WHERE CId=:id");
        query.bindValue(":name", ui->CNameTb->text());
        query.bindValue(":phone", ui->CPhoneTb->text());
        query.bindValue(":age", ui->CAgeTb->text().toInt());
        query.bindValue(":address", ui->CAddTb->text());
        query.bindValue(":gen", ui->CGenCb->currentText());
        query.bindValue(":id", key);

        if (query.exec()) {
            QMessageBox::information(this, "Success", "Coach Updated");
            displayCoachs();
        }
    }
}