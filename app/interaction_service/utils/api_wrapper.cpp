#include "api_wrapper.h"

OpenStreetMapWrapper::OpenStreetMapWrapper(QObject *parent):QObject(parent){
		connect(&manager, &QNetworkAccessManager::finished, this, &OpenStreetMapWrapper::handle_finished);
}

void OpenStreetMapWrapper::download(const std::string &region, const std::string &department, const QFile& outfile){
		QNetworkRequest request;
		QUrl url = QUrl(QString::fromStdString("https://download.openstreetmap.fr/extracts/europe/france/" + region + "/" + department + ".osm.pbf"));
		request.setUrl(url);
		request.setAttribute(QNetworkRequest::User, outfile.fileName());
		manager.get(request);
}

void OpenStreetMapWrapper::searchCSV(QFile& file, QFile& outfile){
		QNetworkRequest request(QUrl("https://api-adresse.data.gouv.fr/search/csv/")); // Free API provided by the French government
		request.setAttribute(QNetworkRequest::User, outfile.fileName());
		QHttpMultiPart *multipart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

		QHttpPart postpart;
		postpart.setHeader(QNetworkRequest::ContentDispositionHeader,
											 QString("form-data; name=%1; filename=%2")
											 .arg("data", file.fileName()));
		postpart.setBodyDevice(&file);
		multipart->append(postpart);

		QHttpPart longitude, latitude, addresse;

		longitude.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=result_columns"));
		longitude.setBody("longitude");
		multipart->append(longitude);

		latitude.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=result_columns"));
		latitude.setBody("latitude");
		multipart->append(latitude);

		latitude.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=columns"));
		latitude.setBody("adresse");
		multipart->append(latitude);

		file.setParent(multipart);
		manager.post(request, multipart);
}

void OpenStreetMapWrapper::handle_finished(QNetworkReply *reply){
		if(reply->error() == QNetworkReply::NoError){
				QByteArray read = reply->readAll();
				QString filename = reply->request().attribute(QNetworkRequest::User).toString();
				QFile out(filename);
				if(out.open(QIODevice::WriteOnly)){
						out.write(read);
						out.close();
				}
		}
		else{
				qDebug() << reply->error() << reply->errorString();
		}
		reply->deleteLater();
//				QCoreApplication::quit(); You need to implement it
}

#include "api_wrapper.moc"

/*
int main(int argc, char *argv[])
{
		QCoreApplication a(argc, argv);
		OpenStreetMapWrapper A;


		// Example of use

        QFile file("/Users/markdaychman/Desktop/johanna.csv");
		file.open(QIODevice::ReadWrite);

        QFile outfile("/Users/markdaychman/Desktop/output.csv");
		outfile.open(QIODevice::ReadWrite);


		// Search

		A.searchCSV(file, outfile);

		// Downloader

		std::string region = "corse";
		std::string department = "haute_corse";

		return a.exec();
}
*/




