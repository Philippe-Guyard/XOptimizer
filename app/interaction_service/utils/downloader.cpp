#include <QCoreApplication>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <iostream>
#include <string>
#pragma once

class Downloader: public QObject{
        Q_OBJECT
public:
		Downloader(QObject *parent=nullptr):QObject(parent){
				connect(&m_manager, &QNetworkAccessManager::finished, this, &Downloader::handle_finished);
		}

		void download(const std::string &region, const std::string &department, const QString & filename){
				QNetworkRequest request;
				QUrl url = QUrl(QString::fromStdString("https://download.openstreetmap.fr/extracts/europe/france/" + region + "/" + department + ".osm.pbf"));
				request.setUrl(url);
				request.setAttribute(QNetworkRequest::User, filename);
				m_manager.get(request);
		}
		Q_SIGNAL void finished(bool);
private:
		void handle_finished(QNetworkReply *reply){
				bool ok = false;
				if(reply->error() == QNetworkReply::NoError){
						QByteArray read = reply->readAll();
						QString filename = reply->request().attribute(QNetworkRequest::User).toString();
						QFile out(filename);
						if(out.open(QIODevice::WriteOnly)){
								out.write(read);
								out.close();
								ok = true;
						}
				}
				else{
						qDebug() << reply->error() << reply->errorString();
				}
				reply->deleteLater();
				Q_EMIT finished(ok);
		}
		QNetworkAccessManager m_manager;
};

#include "downloader.moc"
