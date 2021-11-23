#include <QFile>
#include <QTextStream>
#include <stdio.h>
#include <QtDebug>
#include <QMap>
#include <QVector>
#include <iostream>

class Order{
	public:
		Order(){}
		void set_id(int id){
				this->id = id;
				qDebug()<< "set id";
		}
		void set_adresse(QString adresse){
				this->adresse = adresse;
		}
		void set_longitude(double longitude){
				this->longitude = longitude;
		}
		void set_latitude(double latitude){
				this->latitude = latitude;
		}
		void set_other(QString header,QString value){
				this->other_dict.insert(header,value);
		}

		double longitude;
		double latitude;
		int id;
		QString adresse;
		QMap<QString , QString> other_dict;
};

Order line_to_order(QString line, QVector<QString> header){
		QRegExp rx(", (?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)|,(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)| ,(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)");

		QStringList line_list = line.split(rx); //split line according to regex without skipping empty parts
		QListIterator<QString> line_it(line_list);
		QVectorIterator <QString> header_it(header);
		Order *order = new Order;
		while(line_it.hasNext() && header_it.hasNext()){
				QString cur_header = header_it.next();
				QString cur_item = line_it.next();
				cur_header.remove('"');
				cur_header.replace(" ", "");

				if (cur_header.toLower() == "id"){
						order->set_id(cur_item.toInt());
				}
				else if(cur_header.toLower() == "adresse"){
						order->set_adresse(cur_item);
				}
				else if(cur_header.toLower() == "longitude"){
						order->set_longitude(cur_item.toDouble());
				}
				else if(cur_header.toLower() == "latitude"){
						order->set_latitude(cur_item.toDouble());
				}
				else{ // if none of the other statements work just put the data into data dictionary
						order->set_other(cur_header,cur_item);
				}
		}
		return *order;
}

void file_to_order(QFile *file, QVector<Order>& order_list){
		/* It is important to note that the headers nor the lines in the csv can have spaces in them!!!
		 * Rewrite so that I use the LineToOrder function!!!
		 */
		QTextStream stream(file);  //read a line
		QRegExp rx(", (?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)|,(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)| ,(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)");
		// This splits the string on ',' or ', ' or ' ,' that is followed by an even number of double quotes, sorry for the mess :(
		// also make sure there are no lone quotation marks otherwise it fucks up everything

		if(file->open(QIODevice::ReadOnly)){
				QString line = stream.readLine();
				QStringList header_list = line.split(rx, QString::SkipEmptyParts);
				QVector<QString> headers = QVector<QString>::fromList(header_list);

				for (QString line = stream.readLine();
						 !line.isNull();
						 line = stream.readLine()){
						order_list.push_back(line_to_order(line,headers));
				}
				file->close();
		}
}

/*
int main(){
    QFile input("/Users/markdaychman/Desktop/out.csv");
    QVector<Order> list;
    file_to_order(&input, list);
    std::cout << "==============" << std::endl;
    std::cout << list.at(0).longitude << std::endl;
    std::cout << list.at(0).latitude << std::endl;
}
*/
