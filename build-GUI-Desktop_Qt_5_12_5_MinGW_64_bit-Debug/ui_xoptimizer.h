/********************************************************************************
** Form generated from reading UI file 'xoptimizer.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XOPTIMIZER_H
#define UI_XOPTIMIZER_H

#include <QtCore/QVariant>
#include <QtQuickWidgets/QQuickWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_XOptimizer
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QProgressBar *progressBar;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QComboBox *CitycomboBox_2;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QComboBox *DepartmentcomboBox;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_3;
    QLabel *filelabel;
    QPushButton *uploadFileButton;
    QTableWidget *tableWidget;
    QQuickWidget *quickWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *XOptimizer)
    {
        if (XOptimizer->objectName().isEmpty())
            XOptimizer->setObjectName(QString::fromUtf8("XOptimizer"));
        XOptimizer->resize(800, 600);
        centralwidget = new QWidget(XOptimizer);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(30, 470, 341, 41));
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(30, 530, 731, 20));
        progressBar->setValue(24);
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 100, 341, 55));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        CitycomboBox_2 = new QComboBox(layoutWidget);
        CitycomboBox_2->setObjectName(QString::fromUtf8("CitycomboBox_2"));

        verticalLayout_2->addWidget(CitycomboBox_2);

        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(30, 30, 341, 55));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget1);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        DepartmentcomboBox = new QComboBox(layoutWidget1);
        DepartmentcomboBox->setObjectName(QString::fromUtf8("DepartmentcomboBox"));

        verticalLayout->addWidget(DepartmentcomboBox);

        layoutWidget2 = new QWidget(centralwidget);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(30, 170, 341, 59));
        verticalLayout_3 = new QVBoxLayout(layoutWidget2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        filelabel = new QLabel(layoutWidget2);
        filelabel->setObjectName(QString::fromUtf8("filelabel"));

        verticalLayout_3->addWidget(filelabel);

        uploadFileButton = new QPushButton(layoutWidget2);
        uploadFileButton->setObjectName(QString::fromUtf8("uploadFileButton"));

        verticalLayout_3->addWidget(uploadFileButton);

        tableWidget = new QTableWidget(centralwidget);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(30, 240, 341, 211));
        quickWidget = new QQuickWidget(centralwidget);
        quickWidget->setObjectName(QString::fromUtf8("quickWidget"));
        quickWidget->setGeometry(QRect(390, 30, 391, 481));
        quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
        XOptimizer->setCentralWidget(centralwidget);
        menubar = new QMenuBar(XOptimizer);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 24));
        XOptimizer->setMenuBar(menubar);
        statusbar = new QStatusBar(XOptimizer);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        XOptimizer->setStatusBar(statusbar);

        retranslateUi(XOptimizer);

        QMetaObject::connectSlotsByName(XOptimizer);
    } // setupUi

    void retranslateUi(QMainWindow *XOptimizer)
    {
        XOptimizer->setWindowTitle(QApplication::translate("XOptimizer", "XOptimizer", nullptr));
        pushButton->setText(QApplication::translate("XOptimizer", "Submit and optimize", nullptr));
        label_2->setText(QApplication::translate("XOptimizer", "Choose your city:", nullptr));
        label->setText(QApplication::translate("XOptimizer", "Choose your department:", nullptr));
        filelabel->setText(QApplication::translate("XOptimizer", "No file chosen. Click the button below to upload", nullptr));
        uploadFileButton->setText(QApplication::translate("XOptimizer", "Upload file", nullptr));
    } // retranslateUi

};

namespace Ui {
    class XOptimizer: public Ui_XOptimizer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XOPTIMIZER_H
