#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QtNetwork>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Бот ЕГУ СПО");
    setWindowIcon(QIcon("ggfr.jpg"));

    manager=new QNetworkAccessManager;


    QLabel *l=new QLabel;
    l->setStyleSheet("QLabel{background-image: url(ggfr.jpg);}");

    setFixedSize(310,250);

    statusBar()->showMessage("Active...");

    setCentralWidget(l);

    getMessage();


    QTimer *t=new QTimer;
    t->start(20000);

    connect(t,SIGNAL(timeout()),this,SLOT(getMessage()));
    connect(this,SIGNAL(goWrite(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));





}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::replyFinished(QNetworkReply *reply)
{

    QString s;

    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray content= reply->readAll();
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        s=codec->toUnicode(content.data()) ;

        P(s);
    }
    else QMessageBox::critical(0,"Ошибка", reply->errorString());

    reply->deleteLater();
}

void MainWindow::getMessage()
{
    QString Vk="https://api.vk.com/method/messages.get?access_token="+token;

    QNetworkRequest vkk(Vk);

    vkk.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    reply=manager->post(vkk,QByteArray());

    connect(reply,&QNetworkReply::finished,[this](){emit goWrite(reply);});
}

void MainWindow::P(QString &s)
{

    QList<QPair<QString,QPair<QString,QString>> >list;

    QRegExp e("\"mid\":(\\d{1,}),\"date\":(\\d+),\"out\":(0|1),\"uid\":(\\d{3,9}),\"read_state\":(0|1),\"title\":\" ... \",\"body\":\"([!а-яА-ЯA-Za-z0-9 _]+)\"");

    int pos = 0;

    while ((pos = e.indexIn(s, pos)) != -1 )
    {
        list.push_back({e.cap(1),{e.cap(4),e.cap(6)}});

        pos += e.matchedLength();
    }

    if(!list.isEmpty())
    {
        QString Vk;

        for(const auto&x:list)
        {
            if(x.second.second=="!родителям")
            {
                Vk="https://api.vk.com/method/messages.send?user_id="+x.second.first+"&message=Родителям&attachment=photo439685153_456239017&access_token="+token;
            } else if (x.second.second=="!контакты")
            {
                Vk="https://api.vk.com/method/messages.send?user_id="+x.second.first+"&message=Контакты&attachment=photo439685153_456239018&access_token="+token;
            } else if(x.second.second=="!курсовая")
            {
                Vk="https://api.vk.com/method/messages.send?user_id="+x.second.first+"&message=Положение о курсовой&attachment=doc439685153_448198995&access_token="+token;
            }else if(x.second.second=="!специальности")
            {
                Vk="https://api.vk.com/method/messages.send?user_id="+x.second.first+"&message=Перечень специальностей&attachment=doc439685153_448199017&access_token="+token;
            }else if(x.second.second=="!места")
            {
                Vk="https://api.vk.com/method/messages.send?user_id="+x.second.first+"&message=Количество мест СПО&attachment=doc439685153_448199031&access_token="+token;
            }else if(x.second.second=="!документы")
            {
                Vk="https://api.vk.com/method/messages.send?user_id="+x.second.first+"&message=Перечень документов&attachment=doc439685153_448199047&access_token="+token;
            }else if(x.second.second=="!стоимость")
            {
                Vk="https://api.vk.com/method/messages.send?user_id="+x.second.first+"&message=Стоимость обучения&attachment=doc439685153_448199063&access_token="+token;
            }else if(x.second.second=="!сайтспо")
            {
                Vk="https://api.vk.com/method/messages.send?user_id="+x.second.first+"&message=http://spo.elsu.ru&access_token="+token;
            }else if(x.second.second=="!сайтегу")
            {
                Vk="https://api.vk.com/method/messages.send?user_id="+x.second.first+"&message=http://www.elsu.ru&access_token="+token;
            }else if(x.second.second=="!при")
            {
                Vk="https://api.vk.com/method/messages.send?user_id="+x.second.first+"&message=http://www.elsu.ru/pk/&access_token="+token;
            }
            else if(x.second.second=="!подслушано")
            {
                Vk="https://api.vk.com/method/messages.send?user_id="+x.second.first+"&message=https://vk.com/public79783762&access_token="+token;
            }else if(x.second.second=="!институты")
            {
                Vk="https://api.vk.com/method/messages.send?user_id="+x.second.first+"&message=http://www.elsu.ru/3578-instituty.html&access_token="+token;
            }else if(x.second.second=="!лучшиеспо")
            {
                Vk="https://api.vk.com/method/messages.send?user_id="+x.second.first+"&message=Лучшие обучающиеся центра СПО http://spo.elsu.ru/best.php&access_token="+token;
            }else if(x.second.second=="!титлреферат")
            {
                 Vk="https://api.vk.com/method/messages.send?user_id="+x.second.first+"&message=Образец титульногого листа реферата СПО&attachment=doc439685153_448200700&access_token="+token;
            } else
            {
                 Vk="https://api.vk.com/method/messages.send?user_id="+x.second.first+"&message=Неверная команда&access_token="+token;
            }

            QNetworkRequest vkk(Vk);

            vkk.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

            manager->post(vkk,QByteArray());

            vkk.setUrl("https://api.vk.com/method/messages.delete?message_ids="+x.first+"&access_token="+token);

            manager->post(vkk,QByteArray());
        }
    }
}
