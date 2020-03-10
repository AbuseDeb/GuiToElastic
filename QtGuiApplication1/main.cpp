#include "qtguiapplication1.h"
#include <QtWidgets/QApplication>
#include <qdebug.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtGuiApplication1 w;



	w.show();
	qDebug() << "asd pressed";
	//w.centralWidget.
	return a.exec();
}
