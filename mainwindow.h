#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QWebView>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    void goWrite(QNetworkReply*);
public slots:
    void getMessage();
    void replyFinished(QNetworkReply*);
    void P(QString&);
private:
    const QString token="token";
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
