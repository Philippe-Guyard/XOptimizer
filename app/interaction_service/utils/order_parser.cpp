#include "order_parser.h"
#include <QRegularExpression>

void Order::set_id(int id){
    this->id = id;
    qDebug()<< "set id";
}

void Order::set_location(QString location){
    this->location = location;
    qDebug()<<"set location";
}

void Order::set_other(QString header,QString value){
    // overloads the value if header already exists
    this->other_dict.insert(header,value);
    qDebug() << "set other to key,value:" << header << ", " << value;
}

void Order::set_latitude(double latitude) {
    geolocation.first = latitude;
}

void Order::set_longitude(double longitude) {
    geolocation.second = longitude;
}

//vector<string> headers
//split()
//split_line[i] corresponds to headers[i]

Order line_to_order(QString line, QVector<QString> header){
        QRegularExpression rx(", (?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)|,(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)| ,(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)");

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
                    order->set_location(cur_item);
				}
				else if(cur_header.toLower() == "longitude"){
                    order->set_longitude(cur_item.toDouble());
				}
				else if(cur_header.toLower() == "latitude"){
                    order->set_latitude(cur_item.toDouble());
				}
                else if (cur_header.toLower() == "type") {
                    order->is_inventory = cur_item == "1";
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
        QRegularExpression rx(", (?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)|,(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)| ,(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)");
		// This splits the string on ',' or ', ' or ' ,' that is followed by an even number of double quotes, sorry for the mess :(
		// also make sure there are no lone quotation marks otherwise it fucks up everything

		if(file->open(QIODevice::ReadOnly)){
				QString line = stream.readLine();
                QStringList header_list = line.split(rx); //QString::SkipEmpty parts is obsolete and should not be used in new code
				QVector<QString> headers = QVector<QString>::fromList(header_list);

				for (QString line = stream.readLine();
						 !line.isNull();
						 line = stream.readLine()){
						order_list.push_back(line_to_order(line,headers));
				}
				file->close();
		}
}

void orders_to_table(const QVector<Order>& orders, QVector<QVector<QString>>& out_table) {
    if (orders.size() == 0)
        return;
    //lat long adress id type
    out_table = QVector<QVector<QString>>(orders.size() + 1, QVector<QString>(5 + orders[0].other_dict.size()));
    out_table[0][0] = "id";
    out_table[0][1] = "adresse";
    out_table[0][2] = "latitude";
    out_table[0][3] = "longitude";
    out_table[0][4] = "type";
    int j = 5;
    for(auto it : orders[0].other_dict) {
        out_table[0][j++] = it;
    }
    for(int i = 0; i < orders.size(); ++i) {
        out_table[i + 1][0] = QString::number(orders[i].id);
        out_table[i + 1][1] = orders[i].location;
        out_table[i + 1][2] = QString::number(orders[i].geolocation.first);
        out_table[i + 1][3] = QString::number(orders[i].geolocation.second);
        out_table[i + 1][4] = orders[i].is_inventory ? "1" : "0";

        j = 5;
        for(auto it = orders[i].other_dict.begin(); it != orders[i].other_dict.end(); it++) {
            out_table[i + 1][j++] = it.key();
        }
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
