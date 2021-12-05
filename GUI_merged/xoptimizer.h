#ifndef XOPTIMIZER_H
#define XOPTIMIZER_H
#include <QStandardItemModel>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class XOptimizer; }
QT_END_NAMESPACE

class XOptimizer : public QMainWindow
{
    Q_OBJECT

public:
    XOptimizer(QWidget *parent = nullptr);
    ~XOptimizer();

private slots:
    void on_DepartmentcomboBox_currentTextChanged(const QString &arg1);

    void on_uploadFileButton_clicked();

    void on_pushButton_clicked();

    void saveFile(const QString &name);

    void on_CitycomboBox_2_currentTextChanged(const QString &arg1);

    void on_NextButton_clicked();

    void on_stackedWidget_currentChanged(int arg1);

    void change_page(int a);

private:
    Ui::XOptimizer *ui;
};
#endif // XOPTIMIZER_H
