#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "myChannel.h"

#include <QMainWindow>
#include <QStandardItemModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setCity();
    void setAutoComplete(QJsonObject result);
    void searhInputChanged();

private:
    Ui::MainWindow *ui;
    myChannel * _myChannel;
    QStandardItemModel * _mItemModel;
};

#endif // MAINWINDOW_H
