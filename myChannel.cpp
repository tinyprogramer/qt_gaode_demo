#include "myChannel.h"

myChannel::myChannel(QObject *parent)
    :QObject(parent)
{

}

void myChannel::cityChangeResult(QString result)
{
	emit setCityLable(result);
}


void myChannel::getAutocomplete(QJsonObject result)
{
    emit sendAutocomplete(result);
}

void myChannel::setCity(QString city)
{
	emit cityChanged(city);
}
