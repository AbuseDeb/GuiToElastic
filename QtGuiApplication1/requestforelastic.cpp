#include "requestforelastic.h"



RequestForElastic::RequestForElastic()
{
}


RequestForElastic::~RequestForElastic()
{
}


QByteArray RequestForElastic::MakeRequest(eRequestTypeBody Requestype, const QString &arg)
{
	QByteArray cRequest;

	switch (Requestype)
	{
		case RequestForElastic::RequestBodySearchAll:
		{
			QString cReqSearchAll = QString(
				"{"
					"\"size\": 40,"
					"\"query\": {"
						"\"multi_match\" : {"
							"\"query\" : \"%1\","
							"\"type\": \"phrase\","
							"\"fields\" : [\"creation_place\", \"author\", \"annotation\"]"
						"}"
					"},"
					"\"highlight\": {"
					"\"type\" : \"unified\","
						"\"number_of_fragments\" : 10,"
						"\"fields\" : {"
							"\"annotation\": {}"
						"}"
					"}"
				"}"
			);

			return cRequest = cReqSearchAll.arg(arg).toUtf8();
		}
		break;
		case RequestForElastic::RequestBodyComplete:
		{
			QString cReqComplete = QString(
				"{"
					"\"size\": 0,"
					"\"aggs\" : {"
						"\"autocomplete\": {"
							"\"terms\": {"
								"\"field\": \"autocomplete\","
								"\"order\" : {	\"_count\": \"desc\" },"
								"\"size\" : 50,"
								"\"include\" : \"%1.*\""
							"}"
						"}"
					"},"
					"\"query\": {"
						"\"prefix\": {"
							"\"autocomplete\": {"
								"\"value\": \"%1\""
							"}"
						"}"
					"}"
				"}"
			);

			return cRequest = cReqComplete.arg(arg).toUtf8();
		}
		break;
		case RequestForElastic::RequestBodySearchAuthor:
		{
			QString cReqSearchAuthor = QString("{"
				"\"query\": {"
				"\"match\": {"
				"\"author\": \"%1\""
				"}"
				"}"
				"}");

			return cRequest = cReqSearchAuthor.arg(arg).toUtf8();
		}
		break;
	}


	return cRequest;
}
