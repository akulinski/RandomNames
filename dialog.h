#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QVector>
#include <string>
#include <QStringList>
#include <QStringListModel>
#include <QStandardItemModel>

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
    QStandardItemModel* createModel(QObject* parent);
    QStandardItemModel* wylosowane(QObject* parent);
    int randomIndex(int i);


private slots:
    void on_nazwiska_clicked();

    void on_tematy_clicked();

    void on_wylosuj_clicked();

    void on_przypisz_clicked();

private:
    Ui::Dialog *ui;
    QStringListModel *model;
    QVector<QVector<std::string>> nazwiska;
    QVector<std::string> tematy;
};

#endif // DIALOG_H
