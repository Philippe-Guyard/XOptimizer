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
#include <QtQuick>
using namespace std;

QString chosenCity;
QString chosenDepartment;
//QStringList departments = { "Auvergne-Rhône-Alpes", "Bourgogne-Franche-Comté", "Bretagne", "Centre-Val de Loire",};
QStringList departments = {"Corse", "Auvergne", "Ile-de-France"};
map<QString, QStringList> cities = {
    {"Corse", {"Haute Corse", "Corse Du Sud"}},
    {"Auvergne", {"Haute Loire"}},
    {"Ile-de-France", {"Paris"}}
};

std::string to_api_string(const QString& human) {
    return human.toLower().replace(" ", "_").replace("-", "_").toStdString();
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
    , ui(new Ui::MainWindow)
    , map_data() {
    ui->setupUi(this);
    //Setting up the drop boxes
    ui->DepartmentcomboBox->addItems(departments);

    QDir dir(".");
    QString movielocation = dir.absolutePath() + "/loader.gif";
    QMovie *movie = new QMovie(movielocation);
    ui-> loaderlabel ->setMovie(movie);
    movie->start();

    map_data.clearPath();
    ui->quickWidget->engine()->rootContext()->setContextProperty("data_out", &map_data);

    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
    // QQuickItem* mapView = ui->quickWidget->rootObject()->childItems().first();

    // Set property
    // mapView->setProperty("center", QVariant::fromValue(QGeoCoordinate(0, 0)));
    ui->quickWidget->show();

    interaction_service = std::make_unique<XOptimizer::InteractionService>();
    loading_timer = new QTimer(this);
    change_page(0);
}



MainWindow::~MainWindow()
{
    delete loading_timer;
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
    ui->tableWidget->clearContents();
    QString file_name = QFileDialog::getOpenFileName(this, "Choose a file", QDir::homePath(), "All files (*.*);;Data files (*.csv)");
    ui->filelabel->setText(file_name);
    ui->uploadFileButton->setText("Upload a different file");

    QFile file(file_name);
    QVector<QVector<QString>> table_values;
    interaction_service->read_csv_as_table(&file, table_values);
    ui->tableWidget->setRowCount(table_values.size());
    ui->tableWidget->setColumnCount(table_values[0].size());
    for(int i = 0; i < table_values.size(); ++i) {
        for(int j = 0; j < table_values[i].size(); ++j) {
            ui->tableWidget->setItem(i, j, new QTableWidgetItem(table_values[i][j]));
        }
    }

    file.close();
}



void MainWindow::on_pushButton_clicked()
{
    QDir dir(".");
    QString file_name = dir.absolutePath() + "/writefile.csv";
    saveFile(file_name); //To this file the edited data is saved and then we give this file to Marten

    QFile file(file_name);
    bool can_optimize = interaction_service->optimize_csv(&file);
    if (!can_optimize) {
        QMessageBox::warning(this, "Invalid input", "There is a problem in your input");
        return;
    }

    ui->label_4->setText("Optimizing...");
    ui->stackedWidget->setCurrentIndex(1);

    loading_timer->setInterval(500);
    connect(loading_timer, &QTimer::timeout, [this] () {
        QVector<QVector<QString>> table_values;
        QVector<QVector<std::pair<double, double>>> cycles;
        if (this->interaction_service->get_optimized_orders(table_values, cycles)) {
            this->ui->tableWidget_2->setColumnCount(table_values[0].size());
            this->ui->tableWidget_2->setRowCount(table_values.size());
            for(int i = 0; i < table_values.size(); ++i) {
                for(int j = 0; j < table_values[i].size(); ++j) {
                    this->ui->tableWidget_2->setItem(i, j, new QTableWidgetItem(table_values[i][j]));
                }
            }

            this->ui->stackedWidget->setCurrentIndex(3);
            this->loading_timer->stop();

            this->map_data.setGnssLatitude(cycles[0][0].first);
            this->map_data.setGnssLongitude(cycles[0][0].second);
            this->map_data.setGnssPosition(QGeoCoordinate(cycles[0][0].first, cycles[0][0].second));

            for (auto path : cycles) {
                for(auto point : path) {
                    this->map_data.addCoordinateToPath(point.first, point.second);
                }

                //Complete the cycle since we take that into account too
                this->map_data.addCoordinateToPath(path[0].first, path[0].second);
            }
        }
    });
    loading_timer->start();
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

        file.close();
    }


}



#include <unistd.h>

void MainWindow::on_NextButton_clicked()
{  
    interaction_service->download_and_parse_map(to_api_string(chosenDepartment), to_api_string(chosenCity));

    ui->stackedWidget->setCurrentIndex(1);
    QTimer::singleShot(5000, this, [this]() { ui->stackedWidget->setCurrentIndex(2); } );
}

void MainWindow::change_page(int a){
    ui->stackedWidget->setCurrentIndex(a);
}


void MainWindow::on_stackedWidget_currentChanged(int arg1)
{

}


void MainWindow::on_pushButton_2_clicked()
{
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
}

