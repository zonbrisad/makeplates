
#include <QMainWindow>
#include <QtWidgets>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QMenuBar>
#include <QComboBox>

#include "MainWindow.h"


MainWindow::MainWindow() {

	// Set window size.
    resize(MainWindow_XSIZE, MainWindow_YSIZE);

    // Set window title
	setWindowTitle(MainWindow_TITLE);

	QWidget *window = new QWidget;
	QTextEdit *textEdit = new QTextEdit(this);

	QHBoxLayout *hLayout  = new QHBoxLayout();
	hLayout->setSpacing(MainWindow_Spacing);
	hLayout->setContentsMargins(MainWindow_LeftMarigin, MainWindow_RightMarigin,
				                MainWindow_TopMarigin,  MainWindow_BottomMarigin);

	QVBoxLayout *vLayout  = new QVBoxLayout();
	vLayout->setSpacing(MainWindow_Spacing);
	vLayout->setContentsMargins(MainWindow_LeftMarigin, MainWindow_RightMarigin,
			                    MainWindow_TopMarigin,  MainWindow_BottomMarigin);
	
	QPushButton *button1  = new QPushButton("B1");
	connect(button1, SIGNAL (clicked()),this, SLOT (button1_clicked()));

	QPushButton *button2  = new QPushButton("B2");
	QPushButton *button3  = new QPushButton("B3");
	
	vLayout->addWidget(button1);
	vLayout->addWidget(button2);
	vLayout->addWidget(button3);
	

    QComboBox *combo1 = new QComboBox();
    combo1->addItem("Item a", 101);
    combo1->addItem("Item b", 102);
    combo1->addItem("Item c", 103);

    connect(combo1, SIGNAL (activated()),this, SLOT (combo1Handler()));
    //connect(combo1, SIGNAL (currentIndexChanged()),this, SLOT (combo1Handler()));

    vLayout->addWidget(combo1);


	// Spacer for left side panel
	vLayout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding));

	hLayout->addLayout(vLayout);
	hLayout->addWidget(textEdit);
	
	// Statusbar
    QStatusBar *statusbar = new QStatusBar();
    statusbar->setLayoutDirection(Qt::RightToLeft);
    setStatusBar(statusbar);

    // Menubar
    QMenuBar *menubar = new QMenuBar();
  //  menubar->setGeometry(new QRect(0, 0, 855, 25));
    setMenuBar(menubar);

	

	window->setLayout(hLayout);
	setCentralWidget(window);
	
}


void MainWindow::button1_clicked() {
	qDebug() << "Button 1 clicked\n";
}


void MainWindow::combo1Handler(int a) {
	qDebug() << "Combo 1handler\n";
}
