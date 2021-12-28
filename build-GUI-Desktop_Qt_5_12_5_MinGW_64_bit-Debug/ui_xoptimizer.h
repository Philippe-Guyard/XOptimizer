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
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_XOptimizer
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page_3;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QComboBox *CitycomboBox_2;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QComboBox *DepartmentcomboBox;
    QLabel *label_3;
    QPushButton *NextButton;
    QWidget *page_2;
    QLabel *loaderlabel;
    QLabel *label_4;
    QWidget *page_4;
    QPushButton *pushButton;
    QTableWidget *tableWidget;
    QWidget *layoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *filelabel;
    QPushButton *uploadFileButton;
    QWidget *page;
    QWidget *page_5;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *XOptimizer)
    {
        if (XOptimizer->objectName().isEmpty())
            XOptimizer->setObjectName(QString::fromUtf8("XOptimizer"));
        XOptimizer->resize(800, 600);
        centralwidget = new QWidget(XOptimizer);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 801, 571));
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        layoutWidget = new QWidget(page_3);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(240, 260, 341, 71));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        CitycomboBox_2 = new QComboBox(layoutWidget);
        CitycomboBox_2->setObjectName(QString::fromUtf8("CitycomboBox_2"));

        verticalLayout_2->addWidget(CitycomboBox_2);

        layoutWidget_2 = new QWidget(page_3);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(240, 190, 341, 70));
        verticalLayout = new QVBoxLayout(layoutWidget_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget_2);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        DepartmentcomboBox = new QComboBox(layoutWidget_2);
        DepartmentcomboBox->setObjectName(QString::fromUtf8("DepartmentcomboBox"));

        verticalLayout->addWidget(DepartmentcomboBox);

        label_3 = new QLabel(page_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(240, 80, 341, 41));
        QFont font;
        font.setPointSize(16);
        font.setBold(false);
        font.setWeight(50);
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignCenter);
        NextButton = new QPushButton(page_3);
        NextButton->setObjectName(QString::fromUtf8("NextButton"));
        NextButton->setGeometry(QRect(240, 400, 341, 31));
        stackedWidget->addWidget(page_3);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        loaderlabel = new QLabel(page_2);
        loaderlabel->setObjectName(QString::fromUtf8("loaderlabel"));
        loaderlabel->setGeometry(QRect(350, 210, 81, 81));
        loaderlabel->setAutoFillBackground(false);
        loaderlabel->setScaledContents(true);
        label_4 = new QLabel(page_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(320, 310, 141, 20));
        label_4->setAutoFillBackground(true);
        label_4->setAlignment(Qt::AlignCenter);
        stackedWidget->addWidget(page_2);
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        pushButton = new QPushButton(page_4);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(410, 30, 371, 61));
        tableWidget = new QTableWidget(page_4);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(20, 120, 761, 421));
        layoutWidget_3 = new QWidget(page_4);
        layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(20, 30, 371, 59));
        verticalLayout_3 = new QVBoxLayout(layoutWidget_3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        filelabel = new QLabel(layoutWidget_3);
        filelabel->setObjectName(QString::fromUtf8("filelabel"));

        verticalLayout_3->addWidget(filelabel);

        uploadFileButton = new QPushButton(layoutWidget_3);
        uploadFileButton->setObjectName(QString::fromUtf8("uploadFileButton"));

        verticalLayout_3->addWidget(uploadFileButton);

        stackedWidget->addWidget(page_4);
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        stackedWidget->addWidget(page);
        page_5 = new QWidget();
        page_5->setObjectName(QString::fromUtf8("page_5"));
        stackedWidget->addWidget(page_5);
        XOptimizer->setCentralWidget(centralwidget);
        menubar = new QMenuBar(XOptimizer);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        XOptimizer->setMenuBar(menubar);
        statusbar = new QStatusBar(XOptimizer);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        XOptimizer->setStatusBar(statusbar);

        retranslateUi(XOptimizer);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(XOptimizer);
    } // setupUi

    void retranslateUi(QMainWindow *XOptimizer)
    {
        XOptimizer->setWindowTitle(QApplication::translate("XOptimizer", "XOptimizer", nullptr));
        label_2->setText(QApplication::translate("XOptimizer", "Choose your city:", nullptr));
        label->setText(QApplication::translate("XOptimizer", "Choose your department:", nullptr));
        label_3->setText(QApplication::translate("XOptimizer", "WELCOME TO XOPTIMIZER", nullptr));
        NextButton->setText(QApplication::translate("XOptimizer", "Next", nullptr));
        loaderlabel->setText(QString());
        label_4->setText(QApplication::translate("XOptimizer", "Fetching data...", nullptr));
        pushButton->setText(QApplication::translate("XOptimizer", "Submit and optimize", nullptr));
        filelabel->setText(QApplication::translate("XOptimizer", "No file chosen. Click the button below to upload", nullptr));
        uploadFileButton->setText(QApplication::translate("XOptimizer", "Upload file", nullptr));
    } // retranslateUi

};

namespace Ui {
    class XOptimizer: public Ui_XOptimizer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XOPTIMIZER_H
