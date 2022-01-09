#include "xoptimizer.h"
#include "ui_xoptimizer.h"
#include <QMessageBox>
using namespace std;

QStringList departments = { "Auvergne-Rhône-Alpes", "Bourgogne-Franche-Comté", "Bretagne", "Centre-Val de Loire",};


map<QString, QStringList> cities ={
    {"Auvergne-Rhône-Alpes", { "Ain ", "Allier ", "Ardèche " "Cantal ","Drôme ", "Isère ", "Loire ", "Haute-Loire", "Puy-de-Dôme", "Rhône ",}},
    {"Bourgogne-Franche-Comté", { "Côte-d'Or", "Doubs ", "Jura " "Nièvre ", "Haute-Saône", "Saône-et-Loire", "Yonne ", "Territoire de Belfort"}},
    {"Bretagne", { "Côtes-d'Armor", "Finistère ", "Ille-et-Vilaine" "Morbihan",}},
    {"Centre-Val de Loire", { "Cher ", "Eure-et-Loir", "Indre-et-Loire" "Indre ", "Loiret "}}
};

XOptimizer::XOptimizer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::XOptimizer)
{
    ui->setupUi(this);

    //Setting up the drop boxes
    ui->DepartmentcomboBox->addItems(departments);
}

XOptimizer::~XOptimizer()
{
    delete ui;
}


void XOptimizer::on_DepartmentcomboBox_currentTextChanged(const QString &arg1)
{   ui->CitycomboBox_2->clear();
    ui->CitycomboBox_2->addItems( cities[arg1]);
}

