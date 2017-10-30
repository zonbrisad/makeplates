
#include <QMainWindow>

class QAction;
class QMenu;
class QPlainTextEdit;
class QSessionManager;
cd 

class MainWindow : public QMainWindow {
	    Q_OBJECT
		 
	public:
		 explicit MainWindow();

	private slots:	 
		 
	private: 
		 QPlainTextEdit *textEdit;
	 
};
