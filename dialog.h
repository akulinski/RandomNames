#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QVector>
#include <string>
#include <QStringList>
#include <QStringListModel>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    QVector<std::string> split(std::string s, char c);


private slots:
    void on_nazwiska_clicked();

private:
    Ui::Dialog *ui;
    QStringListModel *model;
    QVector<QVector<std::string>> nazwiska;
    QVector<std::string> tematy;
};

#endif // DIALOG_H
