#include <QFile>
#include <QTextStream>
#include <stdio.h>
#include <QtDebug>
#include <QMap>


class Order{
  public:
    Order(){}
    void set_id(int id){
        this->id = id;
        qDebug()<< "set id";
    }
    void set_location(QString location){
        this->location = location;
        qDebug()<<"set location";
    }
    void set_geolocation(QString geo){
        this->geolocation = geo;
        qDebug() << "setGeolocation";
    }
    void set_other(QString header,QString value){
        // overloads the value if header already exists
        this->other_dict.insert(header,value);
        qDebug() << "set other to key,value:" << header << ", " << value;
    }
  private:
    int id; //order ID
    QString location; //order geolocation
    QString geolocation;
    QMap<QString , QString> other_dict;
};

//vector<string> headers
//split()
//split_line[i] corresponds to headers[i]


Order line_to_order(QString line, QStringList header){
    QRegExp rx(", (?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)|,(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)| ,(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)");// match a comma or a space for delimitation

    QStringList line_list = line.split(rx); //split line according to regex without skipping empty parts
    QListIterator<QString> line_it(line_list);  //create two iterators, one for the line and one for the headers
    QListIterator<QString> header_it(header);
    Order *order = new Order; //create the order to be returned
    while(line_it.hasNext() && header_it.hasNext()){ //check if the header matches any of the following [id,location,geolocation]
                                                     // if not save it to the data dictionary of the order object
        QString cur_header = header_it.next();
        QString cur_item = line_it.next();
        cur_header.remove('"');//remove quotations in headers
        cur_header.replace(" ", ""); // remove spaces
        qDebug() << cur_header;
        if (cur_header.toLower() == "id"){
            order->set_id(cur_item.toInt());
        }
        else if(cur_header.toLower() == "location"){
            order->set_location(cur_item);
        }
        else if(cur_header.toLower() == "geolocation"){
            order->set_geolocation(cur_item);
        }
        else{ // if none of the other statements work just put the data into data dictionary
            order->set_other(cur_header,cur_item);
        }
    }
    return *order;
}

QList<Order> file_to_order(QFile *file){
    /* It is important to note that the headers nor the lines in the csv can have spaces in them!!!
     * Rewrite so that I use the LineToOrder function!!!
     *
     */
    QList<Order> order_list;    // list of orders to return
    QTextStream stream(file);  //read a line
    QRegExp rx(", (?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)|,(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)| ,(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)");
    // This splits the string on ',' or ', ' or ' ,' that is followed by an even number of double quotes, sorry for the mess :(
    // also make sure there are no lone quotation marks otherwise it fucks up everything

    if(file->open(QIODevice::ReadOnly)){ //open file in read only mode
        // parse header
        QString line = stream.readLine(); //read the first line
        QStringList headers = line.split(rx, QString::SkipEmptyParts);
        //qDebug() << headers;
        // prase rest of file
        for (QString line = stream.readLine();      // for line in file
             !line.isNull();
             line = stream.readLine()){
            // basically iterate through the headers list and at each header save it to
            qDebug() << "start";
            order_list.append(line_to_order(line,headers));
            qDebug() << "done";
        }
        file->close();
    }
    return order_list;
}

