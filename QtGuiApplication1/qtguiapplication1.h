#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_qtguiapplication1.h"
#include <QtWidgets/qpushbutton.h>
#include <qdebug.h>
#include <qcompleter.h>
#include <qvector.h>
#include <qabstractitemmodel.h>
#include "requestforelastic.h"

class QtGuiApplication1 : public QMainWindow
{
	Q_OBJECT

public:
	QtGuiApplication1(QWidget *parent = Q_NULLPTR);


private slots:	

	void myButtonClicked();

	void lineEditCompliterChanged();


private:
	QAbstractItemModel *ModelFromVector(const QStringList &data);

	RequestForElastic m_pRequests;
	Ui::QtGuiApplication1Class ui;
	QString m_cCompleterRequest; 
	QString m_cSearchRequest;
	QCompleter *m_pCompleter;
};
