

#include <QApplication>
#include <QPushButton>
#include <QMainWindow>

#include "MainWindow.h"

int main( int argc, char **argv ) {
	MainWindow *window;
	
	
	QApplication app( argc, argv );
	app.setApplicationDisplayName("Kalle");
	
	QPushButton hello( "Hello world!", 0 );
	
	window = new MainWindow();
	window->show();
	return app.exec();
}
