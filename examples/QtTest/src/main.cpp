/**
 *---------------------------------------------------------------------------
 * @brief
 *
 * @file     main.cpp
 * @author   Peter Malmberg <peter.malmberg@gmail.com>
 * @date     2017-11-03
 * @license  MIT
 *
 *---------------------------------------------------------------------------
 *
 *
 */


// Includes -----------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>

#include "main.h"

#include "MainWindow.h"

// Macros -------------------------------------------------------------------

// Variables ----------------------------------------------------------------


// Prototypes ---------------------------------------------------------------


// Code ---------------------------------------------------------------------

int main(int argc, char *argv[]) {
	MainWindow *window;
	
  QApplication app(argc, argv);
  QCoreApplication::setOrganizationName(APP_ORG);
  QCoreApplication::setApplicationName(APP_NAME);
  QCoreApplication::setApplicationVersion(APP_VERSION);

  app.setApplicationDisplayName("sssKalle");
  QPushButton hello( "Hello world!", 0 );

	window = new MainWindow();
	window->show();
	return app.exec();
}

