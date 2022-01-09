#include <fstream>
#include <iostream>
#include "main.h"



int main() {
    QFile *file = new QFile(QString("C:/Users/riho8/Documents/School/Semester3/CSE201/Project/test.txt"));
    file_to_order(file);
    return 0;

}
