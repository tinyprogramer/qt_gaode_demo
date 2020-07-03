#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

#include <QWebEngineView>
#include <QWebChannel>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonArray>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qputenv("QTWEBENGINE_REMOTE_DEBUGGING", "7777");

    _myChannel = new myChannel(this);
    _mItemModel =new QStandardItemModel(this);

    QWebChannel* web_channel = new QWebChannel(this);
    web_channel->registerObject("qtChannel",_myChannel);
    ui->webengineview->page()->setWebChannel(web_channel);
    ui->webengineview->load(QUrl("qrc:/smap/mymap_ba.html"));
    ui->listView->setModel(_mItemModel);

    QObject::connect(ui->pushButton_setcity, &QPushButton::clicked, this, &MainWindow::setCity);
    QObject::connect(_myChannel, &myChannel::setCityLable, [this](QString city) {
        ui->label_city->setText(QString::fromLocal8Bit("city:") + city);
    });
    QObject::connect(_myChannel,&myChannel::sendAutocomplete,this,&MainWindow::setAutoComplete);
    QObject::connect(ui->lineEdit_search,&QLineEdit::textEdited,this,&MainWindow::searhInputChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setCity()
{
    QString city = ui->lineEdit_setcity->text().trimmed();
    if (city.size() == 0)
    {
        QMessageBox::warning(this,"Warning","please enter a city!");
        return;
    }
    _myChannel->setCity(city);
}

void MainWindow::setAutoComplete(QJsonObject result)
{
    std::cout<<"in setAuto"<<std::endl;
    _mItemModel->clear();
    if(!(result.contains("tips")&&result["tips"].isArray()))
    {
        return;
    }

    for(auto e:result["tips"].toArray())
    {
        QJsonObject d=e.toObject();
        if(d.contains("name"))
        {
            QString s=d["name"].toString();
            if(s.size()>0)
            {
                QStandardItem * item=new QStandardItem(s);
                _mItemModel->appendRow(item);
                std::cout<<s.toStdString()<<std::endl;
            }
        }
    }

}

void MainWindow::searhInputChanged()
{
    QString cont = ui->lineEdit_search->text().trimmed();
    _myChannel->inputChanged(cont);
}
