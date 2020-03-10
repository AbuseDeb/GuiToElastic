#include "qtguiapplication1.h"
#include <qdebug.h>
#include "elasticservice.h"
#include <qstandarditemmodel.h>


QtGuiApplication1::QtGuiApplication1(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	m_cCompleterRequest = QString("{"
		"\"suggest\": {"
		"\"song-suggest\" : {"
		"\"prefix\" : \"%1\","
		"\"completion\" : {"
		"\"field\" : \"category_suggest_autocomplit\","
		"\"skip_duplicates\" : true"
		"}"
		"}"
		"}"
		"}");

	m_cSearchRequest = QString("{"
		"\"query\": {"
		"\"match\" : {"
		"\"annotation\" : \"%1\""
		"}"
		"}"
		"}").toUtf8();




	m_pCompleter = new QCompleter(this);
	m_pCompleter->setCaseSensitivity(Qt::CaseInsensitive);
	connect(ui.pPushButtonSearch, &QPushButton::clicked, this, &QtGuiApplication1::myButtonClicked);

	connect(ui.lineEditCompliter, &QLineEdit::textChanged, this, &QtGuiApplication1::lineEditCompliterChanged);
	//connect(ui.pushButton, SIGNAL(clicked(QPushButton *)), this, SLOT(myButtonClicked(QPushButton *)));
}


void QtGuiApplication1::myButtonClicked()
{
	ui.pListWidgetRequest->clear();
	ElasticService pService;

	pService.PostRequest("http://localhost:9200/my_index_auto/_search?pretty=true", m_pRequests.MakeRequest(RequestForElastic::RequestBodySearchAll, ui.lineEditCompliter->text()));

	QStringList ListData = pService.GetListData();

	ui.pListWidgetRequest->addItems(ListData);	
}

void QtGuiApplication1::lineEditCompliterChanged()
{
	ui.lineEditCompliter->setCompleter(nullptr);
	if (ui.lineEditCompliter->text().size() > 1)
	{
	
		ElasticService pService;

		pService.PostRequest("http://localhost:9200/my_index_auto/_search?pretty=true", m_pRequests.MakeRequest(RequestForElastic::RequestBodyComplete, ui.lineEditCompliter->text().toLower()));

		QStringList CompleterItems = pService.GetCompleteData();

		if (CompleterItems.size() != 0)
		{		
			m_pCompleter->setModel(ModelFromVector(CompleterItems));

			ui.lineEditCompliter->setCompleter(m_pCompleter);

		}
		
	}

	
}



QAbstractItemModel *QtGuiApplication1::ModelFromVector(const QStringList &data)
{
	QStandardItemModel *m = new QStandardItemModel(data.count(), 1, m_pCompleter);

	for (int i = 0; i < data.size(); ++i)
	{
		QModelIndex WordIdx = m->index(i, 0);			
		m->setData(WordIdx, data.at(i));
	}
	return m;
}
