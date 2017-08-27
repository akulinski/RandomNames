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
    QFile plk("nazwiska.txt");

    if(plk.open(QIODevice::ReadOnly)){
        QTextStream in(&plk);
        while(!in.atEnd()){
            QString tmp= in.readLine();
            std::string line =tmp.toUtf8().constData();
             nazwiska.push_back(split(line,' '));

        }
    }
    plk.close();
  QStringList tmp;
    for(int i=0;i<nazwiska.size();i++){

        for(int m=0;m<nazwiska.at(i).size();m++){
         QString tmpstr=QString::fromStdString(nazwiska[i][m]);
         tmp.append(tmpstr);

        }

    }
    model->setStringList(tmp);
    ui->listView->setModel(model);

}
