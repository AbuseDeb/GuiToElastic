#pragma once
#include <qstring.h>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <qjsondocument.h>

class ElasticService : public QObject
{
public:
	ElasticService();
	~ElasticService();

	Q_OBJECT
		QNetworkAccessManager *manager;

public:
	void PostRequest(QString url, const QByteArray &data);
	
	QStringList GetCompleteData();
	QStringList GetListData();


private:
	QByteArray m_JsonByte;
	QJsonDocument m_JsonDoc;

private slots:
	void replyFinished(QNetworkReply *);
};

