#include "mainwindow.h"
#include "ui_mainwindow.h"
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
//QStringList departments = { "Auvergne-Rhône-Alpes", "Bourgogne-Franche-Comté", "Bretagne", "Centre-Val de Loire",};
QStringList departments = {"Corse"};
map<QString, QStringList> cities = {
    {"Corse", {"Haute Corse", "Corse Du Sud"}}
};

std::string to_api_string(const QString& human) {
    return human.toLower().replace(" ", "_").toStdString();
}

/*
map<QString, QStringList> cities ={
    {"Auvergne-Rhône-Alpes", { "Ain ", "Allier ", "Ardèche " "Cantal ","Drôme ", "Isère ", "Loire ", "Haute-Loire", "Puy-de-Dôme", "Rhône ",}},
    {"Bourgogne-Franche-Comté", { "Côte-d'Or", "Doubs ", "Jura " "Nièvre ", "Haute-Saône", "Saône-et-Loire", "Yonne ", "Territoire de Belfort"}},
    {"Bretagne", { "Côtes-d'Armor", "Finistère ", "Ille-et-Vilaine" "Morbihan",}},
    {"Centre-Val de Loire", { "Cher ", "Eure-et-Loir", "Indre-et-Loire" "Indre ", "Loiret "}}
};
*/

void MainWindow::load_regions() {

}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
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

    interaction_service = std::make_unique<XOptimizer::InteractionService>();
}



MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_DepartmentcomboBox_currentTextChanged(const QString &arg1)
{   ui->CitycomboBox_2->clear();
    ui->CitycomboBox_2->addItems(cities[arg1]);
    chosenDepartment = arg1;
}
void MainWindow::on_CitycomboBox_2_currentTextChanged(const QString &arg1)
{
    chosenCity = arg1;
}


void MainWindow::on_uploadFileButton_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Choose a file", QDir::homePath(), "All files (*.*);;Data files (*.csv)");
    ui->filelabel->setText(file_name);
    ui->uploadFileButton->setText("Upload a different file");

    QFile file(file_name);
    QVector<QVector<QString>> table_values;
    interaction_service->read_csv_as_table(&file, table_values);
    ui->tableWidget->setColumnCount(table_values[0].size());
    for(int i = 0; i < table_values.size(); ++i) {
        ui->tableWidget->insertRow(i);
        for(int j = 0; j < table_values.size(); ++j) {
            ui->tableWidget->setItem(i, j, new QTableWidgetItem(table_values[i][j]));
        }
    }

    file.close();

    /*
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

    file.close();
    */
}



void MainWindow::on_pushButton_clicked()
{
    QDir dir(".");
    QString file_name = dir.absolutePath() + "/writefile.csv";
    saveFile(file_name); //To this file the edited data is saved and then we give this file to Marten

    QFile file(file_name);
    file.open(QIODevice::ReadWrite);
    interaction_service->optimize_csv(&file);
    //interaction_service->read_csv(&file);
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::saveFile(const QString &name)
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

void MainWindow::on_NextButton_clicked()
{  
    interaction_service->download_and_parse_map(to_api_string(chosenDepartment), to_api_string(chosenCity));

    ui->stackedWidget->setCurrentIndex(1);
    QTimer::singleShot(1000, this, [this]() { ui->stackedWidget->setCurrentIndex(2); } );
}

void MainWindow::change_page(int a){

    ui->stackedWidget->setCurrentIndex(a);

}


void MainWindow::on_stackedWidget_currentChanged(int arg1)
{
    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
    ui->quickWidget->show();
}

