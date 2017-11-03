
#include <QMainWindow>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

#include "MainWindow.h"


MainWindow::MainWindow() {
	setWindowTitle("Kallexxx");
	
	QWidget *window = new QWidget;
	
	QTextEdit *textEdit = new QTextEdit(this);
	//setCentralWidget(textEdit);
	QHBoxLayout *hLayout = new QHBoxLayout();
	QVBoxLayout *vLayout = new QVBoxLayout();
	
	QPushButton *button1 = new QPushButton("B1");
	QPushButton *button2 = new QPushButton("B2");
	QPushButton *button3 = new QPushButton("B3");
	
	vLayout->addWidget(button1);
	vLayout->addWidget(button2);
	vLayout->addWidget(button3);
	
	hLayout->addLayout(vLayout);
	hLayout->addWidget(textEdit);
	
	window->setLayout(hLayout);
	
	//setLayout(hLayout);
	setCentralWidget(window);
	
}
