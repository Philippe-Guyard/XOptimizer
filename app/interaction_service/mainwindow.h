#ifndef XOPTIMIZER_H
#define XOPTIMIZER_H
#include <QStandardItemModel>
#include <QMainWindow>
#include <map>
#include <interaction_service.h>
#include <QGeoCoordinate>
#include <map>

class Data: public QObject{
    Q_OBJECT
    Q_PROPERTY(QGeoCoordinate gnssPosition READ gnssPosition WRITE setGnssPosition NOTIFY gnssPositionChanged)
    Q_PROPERTY(QVariantList path READ path WRITE setPath NOTIFY pathChanged)
public:
    const QGeoCoordinate &gnssPosition() const{
        return m_gnssPosition;
    }
    void setGnssLatitude(qreal latitude){
        QGeoCoordinate coordinate(latitude, m_gnssPosition.longitude());
        setGnssPosition(coordinate);
    }
    void setGnssLongitude(qreal longitude){
        QGeoCoordinate coordinate(m_gnssPosition.latitude(), longitude);
        setGnssPosition(coordinate);
    }
    void setGnssPosition(const QGeoCoordinate &newGnssPosition){
        if (m_gnssPosition == newGnssPosition)
            return;
        m_gnssPosition = newGnssPosition;
        emit gnssPositionChanged();
    }

    const QVariantList &path() const {
        return m_path;
    }

    void clearPath() {
        setPath(QVariantList());
    }

    void addCoordinateToPath(double latitude, double longitude) {
        QGeoCoordinate *coord = new QGeoCoordinate(latitude, longitude);
        m_path.append(QVariant::fromValue(*coord));
        delete coord;
        emit pathChanged();
    }

    void setPath(const QVariantList &newPath) {
        if(m_path == newPath)
            return;
        m_path = newPath;
        emit pathChanged();
    }

signals:
    void gnssPositionChanged();
    void pathChanged();
private:
    QGeoCoordinate m_gnssPosition;
    QVariantList m_path;
};

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
    Data map_data;
};
#endif // XOPTIMIZER_H
