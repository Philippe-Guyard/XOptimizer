#ifndef XOPTIMIZER_H
#define XOPTIMIZER_H

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

private:
    Ui::XOptimizer *ui;
};
#endif // XOPTIMIZER_H
