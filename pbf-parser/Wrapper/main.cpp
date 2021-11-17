#include <QCoreApplication>
#include <QFile>
#include <QHttpMultiPart>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <iostream>

class OpenStreetMapWrapper: public QObject{
		Q_OBJECT
public:
		OpenStreetMapWrapper(QObject *parent=nullptr):QObject(parent){
				connect(&manager, &QNetworkAccessManager::finished, this, &OpenStreetMapWrapper::handle_finished);
		}

		void download(const std::string &region, const std::string &department, const QFile& outfile){
				QNetworkRequest request;
				QUrl url = QUrl(QString::fromStdString("https://download.openstreetmap.fr/extracts/europe/france/" + region + "/" + department + ".osm.pbf"));
				request.setUrl(url);
				request.setAttribute(QNetworkRequest::User, outfile.fileName());
				manager.get(request);
		}

		void searchCSV(QFile& file, QFile& outfile){
				QNetworkRequest request(QUrl("https://api-adresse.data.gouv.fr/search/csv/")); // Free API provided by the French government
				request.setAttribute(QNetworkRequest::User, outfile.fileName());
				QHttpMultiPart *multipart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
				QHttpPart postpart;
				postpart.setHeader(QNetworkRequest::ContentDispositionHeader,
													 QString("form-data; name=%1; filename=%2")
													 .arg("data", file.fileName()));
				postpart.setBodyDevice(&file);
				multipart->append(postpart);
				file.setParent(multipart);
				manager.post(request, multipart);
		}

private:
		QNetworkAccessManager manager;
		void handle_finished(QNetworkReply *reply){
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
};
#include <main.moc>
int main(int argc, char *argv[])
{
		QCoreApplication a(argc, argv);
		OpenStreetMapWrapper A;


		// Example of use

		QFile file("/Users/markdaychman/Desktop/search.csv");
		file.open(QIODevice::ReadWrite);

		QFile file2("/Users/markdaychman/Desktop/search2.csv");
		file2.open(QIODevice::ReadWrite);

		QFile outfile("/Users/markdaychman/Desktop/output.csv");
		outfile.open(QIODevice::ReadWrite);

		QFile outfile2("/Users/markdaychman/Desktop/output2.csv");
		outfile2.open(QIODevice::ReadWrite);

		QFile outfile3("/Users/markdaychman/Desktop/output3.pbf");
		outfile3.open(QIODevice::ReadWrite);


		// Search

		A.searchCSV(file, outfile);

		A.searchCSV(file2, outfile2);

		// Downloader

		std::string region = "corse";
		std::string department = "haute_corse";

		A.download(region, department, outfile3);

		return a.exec();
}




