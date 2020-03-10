#include "elasticservice.h"
#include <QtCore>


ElasticService::ElasticService()
{
}


ElasticService::~ElasticService()
{
}

void ElasticService::replyFinished(QNetworkReply *reply)
{
	m_JsonByte = reply->readAll();

	//std::cout << reply->readAll().toStdString();
}

void ElasticService::PostRequest(QString url, const QByteArray &data)
{

	QUrl qrl(url);
	QNetworkRequest request(qrl);

	QEventLoop loop;
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	manager = new QNetworkAccessManager(this);

	connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));

	connect(manager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
	manager->post(request, data);
	loop.exec();
}

QStringList ElasticService::GetCompleteData()
{
	m_JsonDoc = QJsonDocument::fromJson(m_JsonByte);

	QStringList cForAutocompl;
	QJsonArray jArray = m_JsonDoc.object().value("aggregations").toObject().value("autocomplete").toObject().value("buckets").toArray();
	for (int i = 0; i < jArray.size(); i++)
	{	
		cForAutocompl.push_back(jArray.at(i).toObject().value("key").toString());		
	}

	return cForAutocompl;
}

QStringList ElasticService::GetListData()
{
	m_JsonDoc = QJsonDocument::fromJson(m_JsonByte);

	QStringList cForListData;

	QJsonArray jArray = m_JsonDoc.object().value("hits").toObject().value("hits").toArray();

	for (int i = 0; i < jArray.size(); ++i)
	{
		QString str = QString("id : %1\tAutor : %2\nCreation date : %3\tCreation place : %4\nAnnotation : %5\nHighlight : %6");

		cForListData.push_back(str.
			arg(jArray.at(i).toObject().value("_source").toObject().value("id").toInt()).
			arg(jArray.at(i).toObject().value("_source").toObject().value("author").toString()).
			arg(jArray.at(i).toObject().value("_source").toObject().value("creation_date").toString()).
			arg(jArray.at(i).toObject().value("_source").toObject().value("creation_place").toString()).
			arg(jArray.at(i).toObject().value("_source").toObject().value("annotation").toString()).
			arg(jArray.at(i).toObject().value("highlight").toObject().value("annotation").toArray().at(0).toString()));

	}

	return cForListData;

}

