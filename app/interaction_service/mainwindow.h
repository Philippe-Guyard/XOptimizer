#ifndef XOPTIMIZER_H
#define XOPTIMIZER_H
#include <QStandardItemModel>
#include <QMainWindow>
#include <map>
#include <interaction_service.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_DepartmentcomboBox_currentTextChanged(const QString &arg1);

    void on_uploadFileButton_clicked();

    void on_pushButton_clicked();

    void saveFile(const QString &name);

    void on_CitycomboBox_2_currentTextChanged(const QString &arg1);

    void on_NextButton_clicked();

    void on_stackedWidget_currentChanged(int arg1);

    void change_page(int a);

    void load_regions();


    void on_pushButton_2_clicked();

private:
    QTimer *loading_timer;
    Ui::MainWindow *ui;
    std::unique_ptr<XOptimizer::InteractionService> interaction_service;
};
#endif // XOPTIMIZER_H
