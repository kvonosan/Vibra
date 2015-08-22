#include <QtWidgets>

class QWebView;
QT_BEGIN_NAMESPACE
class QLineEdit;
QT_END_NAMESPACE

//! [1]
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const QUrl& url);
protected slots:
    void adjustTitle();
    void setProgress(int p);
    void finishLoading(bool);
private:
    QString jQuery;
    QWebView *view;
    QLineEdit *locationEdit;
    QAction *rotateAction;
    int progress;
//! [1]
};
