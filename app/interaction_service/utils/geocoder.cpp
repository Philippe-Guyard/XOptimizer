#include <QCoreApplication>
#include <QFile>
#include <QHttpMultiPart>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <iostream>

QHttpMultiPart *buildMultpart(QFile& file){

        QHttpMultiPart *multipart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

        QHttpPart postpart;
        postpart.setHeader(QNetworkRequest::ContentDispositionHeader, // I am not sure that it's the right header, but it works
                                             QString("form-data; name=%1; filename=%2")
                                             .arg("data", file.fileName()));
        postpart.setBodyDevice(&file);
        multipart->append(postpart);
        file.setParent(multipart);

        return multipart;
}

int main(int argc, char *argv[])
{
        QCoreApplication a(argc, argv);
        QNetworkAccessManager manager;

        QNetworkRequest request(QUrl("https://api-adresse.data.gouv.fr/search/csv/")); // Free API provided by the French government

        QFile file("/Users/markdaychman/Desktop/search.csv");
        file.open(QIODevice::ReadWrite);

        QHttpMultiPart *multipart = buildMultpart(file);
        QNetworkReply *reply = manager.post(request, multipart);
        QObject::connect(reply, &QNetworkReply::finished, [reply](){
                if(reply->error() == QNetworkReply::NoError){
                        qDebug().noquote() << reply->readAll();
                }
                else{
                        qDebug() << reply->error() << reply->errorString();
                }
                reply->deleteLater();
                QCoreApplication::quit();
        });
        return a.exec();
}
