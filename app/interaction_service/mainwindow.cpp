#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "testing.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << "Before download.";
//    test_download(s);
    qDebug() << "After download.";
}

MainWindow::~MainWindow()
{
    delete ui;
}

