#include <QCoreApplication>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QString>
#include <QByteArray>
#include <QFile>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSqlDatabase*db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    if(db) {
        db->setDatabaseName("data.db");
        if(db->open()) {
            //success
        }
        else {
            qDebug()<<"Error, open database fail";
        }
    }
    else {
        qDebug()<<"Error, create db fail";
    }


    QFile in1("staff.csv");
    if(in1.open(QIODevice::ReadOnly)) {

        while(!in1.atEnd()) {
            QString query1;
            query1="INSERT INTO `staff` (`name`,`age`,`address`,`uid`) values(?,?,?,?)";
            QSqlQuery q1(*db);
            q1.prepare(query1);
            QList<QByteArray>tmp=in1.readLine().split(';');
            q1.addBindValue(tmp.at(0));
            q1.addBindValue(tmp.at(1));
            q1.addBindValue(tmp.at(2));
            q1.addBindValue(tmp.at(3));
            if(q1.exec()) {
                qDebug()<<"Request success";
            }
            else {
                qDebug()<<"Request fail";
            }
        }
        in1.close();
    }

    QFile in2("info.csv");
    if(in2.open(QIODevice::ReadOnly)) {

        while(!in2.atEnd()) {
            QString query2;
            query2="INSERT INTO `info` (`uid`,`department`,`phone`,`office`) values(?,?,?,?)";
            QSqlQuery q2(*db);
            q2.prepare(query2);
            QList<QByteArray>tmp=in2.readLine().split(';');
            q2.addBindValue(tmp.at(0));
            q2.addBindValue(tmp.at(1));
            q2.addBindValue(tmp.at(2));
            q2.addBindValue(tmp.at(3));
            if(q2.exec()) {
                qDebug()<<"Request success";
            }
            else {
                qDebug()<<"Request fail";
            }

        }
        in2.close();
    }


    db->close();
    delete db;
    exit(0);
}
