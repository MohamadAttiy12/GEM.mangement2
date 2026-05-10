#include "Finance.h"
#include "ui_finance.h"

Finance::Finance(QWidget* parent) : QMainWindow(parent), ui(new Ui::Finance) {
    ui->setupUi(this);
    connectDatabase();
    displayPayment();
    getMembers();
}

void Finance::connectDatabase() {
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("gymdb");
    db.setUserName("root");
    db.setPassword("");
    if (!db.open()) {
        QMessageBox::critical(this, "Error", "Database Connection Failed");
    }
}

// جلب بيانات الدفع لعرضها في الجدول (QTableView)
void Finance::displayPayment() {
    QSqlTableModel* model = new QSqlTableModel(this, db);
    model->setTable("FinanceTbl");
    model->select();
    ui->PaymentTable->setModel(model);
}

// جلب أسماء الأعضاء للـ ComboBox
void Finance::getMembers() {
    QSqlQuery query("SELECT MName FROM MemberTbl");
    while (query.next()) {
        ui->MemberCb->addItem(query.value(0).toString());
    }
}

// حفظ الدفع وتوليد الوصل
void Finance::on_Savebtn_clicked() {
    QString member = ui->MemberCb->currentText();
    QString amount = ui->AmountTb->text();
    QDate date = ui->MonthTb->date();

    if (amount.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Missing Information");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO FinanceTbl(PPeriod, PMember, PAmount) VALUES (?,?,?)");
    query.addBindValue(date.toString("yyyy-MM-dd"));
    query.addBindValue(member);
    query.addBindValue(amount.toInt());

    if (query.exec()) {
        QMessageBox::information(this, "Success", "Payment Saved Successfully");
        displayPayment();

        auto choice = QMessageBox::question(this, "Receipt", "Do you want to generate a receipt?", QMessageBox::Yes | QMessageBox::No);
        if (choice == QMessageBox::Yes) {
            generateReceipt(member, date.toString("yyyy-MM-dd"), amount);
        }
        resetFields();
    }
}

// توليد ملف PDF (بديل iText)
void Finance::generateReceipt(QString member, QString date, QString amount) {
    QString fileName = QString("Receipt_%1_%2.pdf").arg(member).arg(QDateTime::currentMSecsSinceEpoch());
    QPdfWriter writer(fileName);
    writer.setPageSize(QPageSize(QPageSize::A4));

    QPainter painter(&writer);
    painter.setFont(QFont("Helvetica", 22, QFont::Bold));
    painter.drawText(2000, 1000, "FITNESS SPOT GYM");

    painter.setFont(QFont("Helvetica", 12));
    painter.drawText(2000, 1500, "Member Name: " + member);
    painter.drawText(2000, 1800, "Date: " + date);
    painter.drawText(2000, 2100, "Amount Paid: " + amount);
    painter.drawText(2000, 2500, "Thank you for staying fit with us!");

    painter.end();

    QMessageBox::information(this, "PDF", "Receipt generated successfully!");
    QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));
}

void Finance::resetFields() {
    ui->AmountTb->clear();
    ui->MonthTb->setDate(QDate::currentDate());
    ui->MemberCb->setCurrentIndex(0);
}