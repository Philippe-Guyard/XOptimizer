#ifndef API_WRAPPER_H
#include <QCoreApplication>
#include <QFile>
#include <QHttpMultiPart>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <iostream>

#define API_WRAPPER_H

class OpenStreetMapWrapper: public QObject{
	Q_OBJECT
public:
	OpenStreetMapWrapper(QObject* parent=nullptr);
	void download(const std::string&, const std::string&, const QFile&);
	void searchCSV(QFile&, QFile&);
	QNetworkAccessManager* get_manager();

private:
	QNetworkAccessManager manager;
	void handle_finished(QNetworkReply*);
};

#endif // API_WRAPPER_H
