#include "dialog.h"
#include "ui_dialog.h"
#include <QFile>
#include <QTextStream>
#include <QString>
#include <string>
#include <QStringList>
#include <QStringListModel>
#include <QTableView>
#include <QStandardItem>
#include <QModelIndex>
#include <QDebug>
#include <QVariant>
#include <QModelIndex>
#include <QtGui>
#include <random>
#include <cstdlib>




Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    model=new QStringListModel(this);
    ui->listView->setModel(model);


}

Dialog::~Dialog()
{
    delete ui;
}

QVector<std::string> Dialog::split(std::string s,char c)
{
       QVector<std::string> v;
       //ustawienie pozycji na początek napisu i znalezienie litery
       std::string::size_type i = 0;
       std::string::size_type j = s.find(c);
        //poki przedni wskaznik nie jest nposem
       while (j != std::string::npos) {
          v.push_back(s.substr(i, j-i));
          //zamiana miejsca i na miejce j +1
          i = ++j;
          j = s.find(c, j);

          if (j == std::string::npos)
             v.push_back(s.substr(i, s.length()));
       }
      return v;
}
void Dialog::on_nazwiska_clicked()
{
    model->setStringList(QStringList {});
    ui->listView->setModel(model);

    QFile plk("C:\\Users\\Albert\\Documents\\view\\nazwiska.txt");

    if(plk.open(QIODevice::ReadOnly)){
        QTextStream in(&plk);
        while(!in.atEnd()){
            QString tmp= in.readLine();
            std::string line =tmp.toUtf8().constData();
             nazwiska.push_back(split(line,' '));

        }
    }
    else{
        qDebug()<<"error";

    }
    plk.close();
    QStringList list;
    for(int i=0;i<nazwiska.size();i++){
        //jeden wiersz nazwisk
        QString rowOfNames;
        std::string strRowOfNames;

        for(int m=0;m<nazwiska[i].size();m++){
            //pojedyncze naziwsko do QStringList nie da sie dodac zwyklego stringa
         QString tmpstr=QString::fromStdString(nazwiska[i][m]);
         std::string strvar=tmpstr.toUtf8().constData();
         strRowOfNames+=strvar+' ';
         rowOfNames=QString::fromStdString(strRowOfNames);
        }
        //zapisanie do listy QStringow i wyzerowanie
        list<<rowOfNames;
        strRowOfNames="";

    }

    model->setStringList(list);
    ui->listView->setModel(model);

}

void Dialog::on_tematy_clicked()
{
    model->setStringList(QStringList {});
    ui->listView->setModel(model);

    QFile plk("C:\\Users\\Albert\\Documents\\view\\tematy.txt");

    if(plk.open(QIODevice::ReadOnly)){
        QTextStream in(&plk);
        while(!in.atEnd()){
            QString tmp= in.readLine();
            std::string line =tmp.toUtf8().constData();
            tematy.push_back(line);
        }
    }
    else{
        qDebug()<<"error";

    }
    plk.close();

    QStringList listaTematow;

    for(int i=0;i<tematy.size();i++){
        QString tmpStr=QString::fromStdString(tematy[i]);
        listaTematow<<tmpStr;
    }
    model->setStringList(listaTematow);
    ui->listView->setModel(model);

}

void Dialog::on_wylosuj_clicked()
{
    QTableView* view2 =new QTableView;
    view2->setModel(wylosowane(view2));
    view2->show();

}

QStandardItemModel* Dialog::wylosowane(QObject *parent){
    QStandardItemModel* model = new QStandardItemModel(10,10);
    for(int row=0;row<tematy.size();row++){
        for(int column=0;column<2;column++){
            if(column==0){
                QString text = QString::fromStdString(tematy[row]);
                QStandardItem* item = new QStandardItem(text);
                model->setItem(row, column, item);}
            else{
                QString text = QString::fromStdString(nazwiska[row][column]);
                QStandardItem* item =new QStandardItem(text);
                model->setItem(row,column,item);

            }
        }
    }
}

int Dialog::randomIndex(int i){
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0,i);
    int dice_roll = distribution(generator);

    return dice_roll;
}

QStandardItemModel* Dialog:: createModel(QObject* parent)
{
     int numRows = 10;
     int numColumns = tematy.size();

    QStandardItemModel* model = new QStandardItemModel(numRows, numColumns);
    for (int row = 0; row < tematy.size(); ++row)
    {
        for (int column = 0; column < nazwiska[row].size(); ++column)
        {
            if(column==0){
            QString text = QString::fromStdString(tematy[row]);
            QStandardItem* item = new QStandardItem(text);
            model->setItem(row, column, item);}
            else{
                QString text=QString::number(column)+' '+QString::fromStdString(nazwiska[row][column]) ;
                QStandardItem* item=new QStandardItem(text);
                model->setItem(row,column,item);
            }
        }

     }

    return model;
}

void Dialog::on_przypisz_clicked()
{
    QTableView *view = new QTableView;

       view->setModel(createModel(view));
       view->show();
}
