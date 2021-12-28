#include "xoptimizer.h"
#include "ui_xoptimizer.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <iostream>
#include <QDebug>
#include <QStandardItemModel>
#include <QMovie>
#include <QTimer>
#include <fstream>
#include <QtDebug>
#include <QTextCodec>
using namespace std;

QString chosenCity;
QString chosenDepartment;
QStringList departments = { "Auvergne-Rhône-Alpes", "Bourgogne-Franche-Comté", "Bretagne", "Centre-Val de Loire",};


map<QString, QStringList> cities ={
    {"Auvergne-Rhône-Alpes", { "Ain ", "Allier ", "Ardèche " "Cantal ","Drôme ", "Isère ", "Loire ", "Haute-Loire", "Puy-de-Dôme", "Rhône ",}},
    {"Bourgogne-Franche-Comté", { "Côte-d'Or", "Doubs ", "Jura " "Nièvre ", "Haute-Saône", "Saône-et-Loire", "Yonne ", "Territoire de Belfort"}},
    {"Bretagne", { "Côtes-d'Armor", "Finistère ", "Ille-et-Vilaine" "Morbihan",}},
    {"Centre-Val de Loire", { "Cher ", "Eure-et-Loir", "Indre-et-Loire" "Indre ", "Loiret "}}
};


void XOptimizer::load_regions(){

    map<QString, QStringList> regions_list;
    QStringList departments_list;
    QDir dir(".");
    QString path = dir.absolutePath() + "/departements-region.csv";

    QFile file(path);

    if(!file.open(QFile::ReadOnly | QFile::Text)){

        QMessageBox::warning(this, "title", "file not open");
    }

    QTextStream in(&file);
    in.setCodec("UTF-8");

    string key, value, number;
    QString garbage = in.readLine();
    while (!in.atEnd()) {
        QString s=in.readLine();


        QStringList linesplit = s.split(',');
        QString qvalue = linesplit[1];
        QString qkey = linesplit[2];

        departments_list << qkey;
        regions_list[qkey] << qvalue;
        }


    qDebug().nospace() << departments_list;
    departments_list.removeDuplicates();
    departments = departments_list;
    cities = regions_list;

}

XOptimizer::XOptimizer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::XOptimizer)
{
    load_regions();

    ui->setupUi(this);
    //Setting up the drop boxes
    ui->DepartmentcomboBox->addItems(departments);
//    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
//    ui->quickWidget->show();

    QDir dir(".");
    QString movielocation = dir.absolutePath() + "/loader.gif";
    QMovie *movie = new QMovie(movielocation);
    ui-> loaderlabel ->setMovie(movie);
    movie->start();

}

XOptimizer::~XOptimizer()
{
    delete ui;
}


void XOptimizer::on_DepartmentcomboBox_currentTextChanged(const QString &arg1)
{   ui->CitycomboBox_2->clear();
    ui->CitycomboBox_2->addItems( cities[arg1]);
    chosenDepartment = arg1;
}
void XOptimizer::on_CitycomboBox_2_currentTextChanged(const QString &arg1)
{
    chosenCity = arg1;
}


void XOptimizer::on_uploadFileButton_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Choose a file", QDir::homePath(), "All files (*.*);;Data files (*.csv)");
    ui->filelabel->setText(file_name);
    ui->uploadFileButton->setText("Upload a different file");

    QFile file(file_name);

    if(!file.open(QFile::ReadOnly | QFile::Text)){

        QMessageBox::warning(this, "title", "file not open");
    }
    QTextStream in(&file);
    in.setCodec("UTF-8");


    int n = 0;
    while (!in.atEnd()){
      ui->tableWidget->insertRow(n);
      QString s=in.readLine(); // reads line from file
      QStringList linesplit = s.split(',');
      ui->tableWidget->setColumnCount(linesplit.length());
      for( int i = 0; i<linesplit.length(); i++){
          ui->tableWidget->setItem(n, i, new QTableWidgetItem(linesplit[i]));
      }
      n = n + 1;
    }

}



void XOptimizer::on_pushButton_clicked()
{
    QDir dir(".");
    QString file_name = dir.absolutePath() + "/writefile.txt";
    saveFile(file_name); //To this file the edited data is saved and then we give this file to Marten

    QFile file(file_name);
    //Pass it to Marten here
    ui->stackedWidget->setCurrentIndex(3);

}

void XOptimizer::saveFile(const QString &name)
{
QFile file(name);

if (file.open(QFile::WriteOnly | QIODevice::Text))
{


    QTextStream data( &file );
    QStringList strList;
    for( int r = 0; r < ui->tableWidget->rowCount(); ++r )
        {
            strList.clear();
            for( int c = 0; c < ui->tableWidget->columnCount(); ++c )
            {   QTableWidgetItem* item = ui->tableWidget->item(r,c);
                if (!item || item->text().isEmpty())
                {
                    ui->tableWidget->setItem(r,c,new QTableWidgetItem("0"));
                }
                strList << ui->tableWidget->item( r, c )->text();

            }
            QString a = strList.join(",")+"\n";
            data << a;
        }
    }

    file.close();
}



#include <unistd.h>

void XOptimizer::on_NextButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    QTimer::singleShot(1000, this, [this]() { ui->stackedWidget->setCurrentIndex(2); } );


}

void XOptimizer::change_page(int a){

    ui->stackedWidget->setCurrentIndex(a);

}


void XOptimizer::on_stackedWidget_currentChanged(int arg1)
{

}

