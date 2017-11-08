
// http://www.bogotobogo.com/Qt/Qt5_QStatusBar.php


#include <QMainWindow>
#include <QComboBox>

class QAction;
class QMenu;
class QPlainTextEdit;
class QSessionManager;


#define MainWindow_TITLE "Nisse"
#define MainWindow_XSIZE 500
#define MainWindow_YSIZE 400

#define MainWindow_Spacing       2

#define MainWindow_LeftMarigin   2
#define MainWindow_RightMarigin  2
#define MainWindow_TopMarigin    2
#define MainWindow_BottomMarigin 2



class MainWindow : public QMainWindow {

	 Q_OBJECT
		 
	public:
		 explicit MainWindow();

	private slots:
		 void button1_clicked();
	 void combo1Handler(int a);
	 void checkboxHandler(int state);
	 void sliderHandler(int a);
	private: 
		 QPlainTextEdit *textEdit;
	 	 QComboBox *combo1;
	 
};
