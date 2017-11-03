
#include <QMainWindow>

class QAction;
class QMenu;
class QPlainTextEdit;
class QSessionManager;


class MainWindow : public QMainWindow {
	    Q_OBJECT
		 
	public:
		 explicit MainWindow();

	private slots:	 
		 
	private: 
		 QPlainTextEdit *textEdit;
	 
};
