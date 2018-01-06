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
    const QString token="7a37323501cf4c7ecd2c82bc46a6f83fc17dd44ed9544e320cd67890b2adfa612864f6726fc721e181fdf";
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
