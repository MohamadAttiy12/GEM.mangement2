#include "Members.h"
#include "ui_members.h"

Members::Members(QWidget* parent) : QMainWindow(parent), ui(new Ui::Members) {
    ui->setupUi(this);
    setupDatabase();
    DisplayMembers();
    GetCoach();
}

Members::~Members() {
    db.close();
    delete ui;
}

void Members::setupDatabase() {
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("gymdb");
    db.setUserName("root");
    db.setPassword("");

    if (!db.open()) {
        QMessageBox::critical(this, "Database Error", db.lastError().text());
    }
}


void Members::DisplayMembers() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM MemberTbl");
    ui->MemberTable->setModel(model);
}


void Members::GetCoach() {
    QSqlQuery query("SELECT CName FROM CoachTbl");
    ui->CoachCb->clear();
    while (query.next()) {
        ui->CoachCb->addItem(query.value(0).toString());
    }
}

void Members::on_AddBtn_clicked() {
    if (ui->MNameTb->text().isEmpty() || ui->PhoneTb->text().isEmpty()) {
        QMessageBox::warning(this, "Missing Information", "Please fill all fields");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO MemberTbl (MName, MPhone, MAge, MAmount, MTiming, MCoach, MGen) "
        "VALUES (?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(ui->MNameTb->text());
    query.addBindValue(ui->PhoneTb->text());
    query.addBindValue(ui->AgeTb->text().toInt());
    query.addBindValue(ui->AmountTb->text().toInt());
    query.addBindValue(ui->TimingCb->currentText());
    query.addBindValue(ui->CoachCb->currentText());
    query.addBindValue(ui->GenCb->currentText());

    if (query.exec()) {
        QMessageBox::information(this, "Success", "Member Saved");
        DisplayMembers();
    }
}


void Members::on_MemberTable_clicked(const QModelIndex& index) {
    int row = index.row();
    Key = ui->MemberTable->model()->index(row, 0).data().toInt(); 
    ui->MNameTb->setText(ui->MemberTable->model()->index(row, 1).data().toString());
    ui->PhoneTb->setText(ui->MemberTable->model()->index(row, 2).data().toString());
    ui->AgeTb->setText(ui->MemberTable->model()->index(row, 3).data().toString());
    ui->AmountTb->setText(ui->MemberTable->model()->index(row, 4).data().toString());

    ui->TimingCb->setCurrentText(ui->MemberTable->model()->index(row, 5).data().toString());
    ui->CoachCb->setCurrentText(ui->MemberTable->model()->index(row, 6).data().toString());
    ui->GenCb->setCurrentText(ui->MemberTable->model()->index(row, 7).data().toString());
}

void Members::on_DeleteBtn_clicked() {
    if (Key == 0) {
        QMessageBox::warning(this, "Error", "Select a member to delete");
    }
    else {
        QSqlQuery query;
        query.prepare("DELETE FROM MemberTbl WHERE MId = ?");
        query.addBindValue(Key);
        if (query.exec()) {
            QMessageBox::information(this, "Deleted", "Member Removed");
            DisplayMembers();
        }
    }
}