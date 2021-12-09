#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QStandardItemModel>
#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;
};
#endif // MainWindow_H
