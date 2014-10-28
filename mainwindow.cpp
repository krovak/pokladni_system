#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "string"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSqlDatabase eav= QSqlDatabase::addDatabase("QSQLITE");

    eav.setDatabaseName("eavtest.sqlite");
    eav.open();


    model = new QSqlTableModel(this);
    ui->vypisL->setText("something");
    QSqlQuery query;
    query.exec("select id from entity");
    while(query.next()){
        ui->vyberCb->addItem(query.value(0).toString());
    }





}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_vyberCb_activated(const QString &entita)
{
    QString name;
    QString value;
    QSqlQuery query;
    query.exec("select name, value from Value join Attribute on ATTRIBUTE.ID=attribute_id where entity_id="+entita);

    while (query.next()) {
            name = name + query.value(0).toString() + "\n";
            value = value + query.value(1).toString() + "\n";
             //qDebug() << name;
         }

    ui->vypisL->setText(name);
    ui->hodnotaL->setText(value);

}
