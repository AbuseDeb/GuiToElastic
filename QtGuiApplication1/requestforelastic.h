#pragma once
#include <qstring.h>

class RequestForElastic
{

public:
	enum eRequestTypeBody
	{
		RequestBodySearchAll,
		RequestBodyComplete,
		RequestBodySearchAuthor,

	};


public:
	RequestForElastic();
	~RequestForElastic();


	QByteArray MakeRequest(eRequestTypeBody Requestype, const QString &arg);



};

