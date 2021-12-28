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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
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
    QVBoxLayout *verticalLayout_10;
    QStackedWidget *stackedWidget;
    QWidget *page_3;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_3;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QComboBox *DepartmentcomboBox;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QComboBox *CitycomboBox_2;
    QVBoxLayout *verticalLayout_11;
    QSpacerItem *verticalSpacer;
    QPushButton *NextButton;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *verticalLayout_9;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QLabel *loaderlabel;
    QLabel *label_4;
    QSpacerItem *verticalSpacer_2;
    QWidget *page_4;
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QLabel *filelabel;
    QPushButton *uploadFileButton;
    QPushButton *pushButton;
    QTableWidget *tableWidget;
    QWidget *page;
    QWidget *page_5;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *XOptimizer)
    {
        if (XOptimizer->objectName().isEmpty())
            XOptimizer->setObjectName(QString::fromUtf8("XOptimizer"));
        XOptimizer->resize(820, 590);
        centralwidget = new QWidget(XOptimizer);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_10 = new QVBoxLayout(centralwidget);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        verticalLayout_5 = new QVBoxLayout(page_3);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(50, -1, 50, -1);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_3 = new QLabel(page_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QFont font;
        font.setPointSize(16);
        font.setBold(false);
        font.setWeight(50);
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label_3);


        verticalLayout_5->addLayout(verticalLayout_4);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(page_3);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        DepartmentcomboBox = new QComboBox(page_3);
        DepartmentcomboBox->setObjectName(QString::fromUtf8("DepartmentcomboBox"));

        verticalLayout->addWidget(DepartmentcomboBox);


        verticalLayout_5->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_2 = new QLabel(page_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        CitycomboBox_2 = new QComboBox(page_3);
        CitycomboBox_2->setObjectName(QString::fromUtf8("CitycomboBox_2"));

        verticalLayout_2->addWidget(CitycomboBox_2);


        verticalLayout_5->addLayout(verticalLayout_2);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_11->addItem(verticalSpacer);

        NextButton = new QPushButton(page_3);
        NextButton->setObjectName(QString::fromUtf8("NextButton"));

        verticalLayout_11->addWidget(NextButton);


        verticalLayout_5->addLayout(verticalLayout_11);

        verticalLayout_5->setStretch(0, 1);
        verticalLayout_5->setStretch(1, 1);
        verticalLayout_5->setStretch(2, 1);
        verticalLayout_5->setStretch(3, 3);
        stackedWidget->addWidget(page_3);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        verticalLayout_7 = new QVBoxLayout(page_2);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        loaderlabel = new QLabel(page_2);
        loaderlabel->setObjectName(QString::fromUtf8("loaderlabel"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(loaderlabel->sizePolicy().hasHeightForWidth());
        loaderlabel->setSizePolicy(sizePolicy);
        loaderlabel->setMaximumSize(QSize(100, 100));
        loaderlabel->setLayoutDirection(Qt::LeftToRight);
        loaderlabel->setAutoFillBackground(false);
        loaderlabel->setScaledContents(true);
        loaderlabel->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(loaderlabel);


        verticalLayout_9->addLayout(horizontalLayout);

        label_4 = new QLabel(page_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAutoFillBackground(true);
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout_9->addWidget(label_4);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer_2);


        verticalLayout_7->addLayout(verticalLayout_9);

        stackedWidget->addWidget(page_2);
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        verticalLayout_8 = new QVBoxLayout(page_4);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, 0, -1, -1);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        filelabel = new QLabel(page_4);
        filelabel->setObjectName(QString::fromUtf8("filelabel"));

        verticalLayout_3->addWidget(filelabel);

        uploadFileButton = new QPushButton(page_4);
        uploadFileButton->setObjectName(QString::fromUtf8("uploadFileButton"));

        verticalLayout_3->addWidget(uploadFileButton);


        horizontalLayout_4->addLayout(verticalLayout_3);

        pushButton = new QPushButton(page_4);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(pushButton);


        verticalLayout_6->addLayout(horizontalLayout_4);

        tableWidget = new QTableWidget(page_4);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        verticalLayout_6->addWidget(tableWidget);


        verticalLayout_8->addLayout(verticalLayout_6);

        stackedWidget->addWidget(page_4);
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        stackedWidget->addWidget(page);
        page_5 = new QWidget();
        page_5->setObjectName(QString::fromUtf8("page_5"));
        stackedWidget->addWidget(page_5);

        verticalLayout_10->addWidget(stackedWidget);

        XOptimizer->setCentralWidget(centralwidget);
        menubar = new QMenuBar(XOptimizer);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 820, 26));
        XOptimizer->setMenuBar(menubar);
        statusbar = new QStatusBar(XOptimizer);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        XOptimizer->setStatusBar(statusbar);

        retranslateUi(XOptimizer);

        stackedWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(XOptimizer);
    } // setupUi

    void retranslateUi(QMainWindow *XOptimizer)
    {
        XOptimizer->setWindowTitle(QApplication::translate("XOptimizer", "XOptimizer", nullptr));
        label_3->setText(QApplication::translate("XOptimizer", "WELCOME TO XOPTIMIZER", nullptr));
        label->setText(QApplication::translate("XOptimizer", "Choose your department:", nullptr));
        label_2->setText(QApplication::translate("XOptimizer", "Choose your city:", nullptr));
        NextButton->setText(QApplication::translate("XOptimizer", "Next", nullptr));
        loaderlabel->setText(QString());
        label_4->setText(QApplication::translate("XOptimizer", "Fetching data...", nullptr));
        filelabel->setText(QApplication::translate("XOptimizer", "No file chosen. Click the button below to upload", nullptr));
        uploadFileButton->setText(QApplication::translate("XOptimizer", "Upload file", nullptr));
        pushButton->setText(QApplication::translate("XOptimizer", "Submit and optimize", nullptr));
    } // retranslateUi

};

namespace Ui {
    class XOptimizer: public Ui_XOptimizer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XOPTIMIZER_H
