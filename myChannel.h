#ifndef __MYCHANNEL_H__
#define __MYCHANNEL_H__

#include <QWebChannel>
#include <QJsonObject>

class myChannel :public QObject 
{
	Q_OBJECT
public:
    explicit myChannel(QObject* parent=nullptr);

	void setCity(QString city);

public slots:

    void getAutocomplete(QJsonObject result);
	void cityChangeResult(QString result);

signals:
	void cityChanged(QString city);
	void inputChanged(QString input);

	void setCityLable(QString city);
    void sendAutocomplete(QJsonObject autocom);

};


#endif
