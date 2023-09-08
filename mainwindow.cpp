#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"
#include "QProcess"
#include "QtEvents"
#include "unistd.h"
#include "main.h"
#include <QKeyEvent>
#include <QMessageBox>

bool demo_status = false;
QMessageBox *msgBoxToastMessage;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qApp->installEventFilter(this);

    ui->setupUi(this);

    QCursor cursor(Qt::BlankCursor);
    QApplication::setOverrideCursor(cursor);
    QApplication::changeOverrideCursor(cursor);

    ui->pushButton_app->setStyleSheet("QPushButton {border: solid ; border-radius: 15;} QPushButton:focus { background-color: LightGrey; border: solid ; border-radius: 15;}");
    ui->pushButton_settings->setStyleSheet("QPushButton {border: solid ; border-radius: 15;} QPushButton:focus { background-color: LightGrey; border: solid ; border-radius: 15;}");
    ui->pushButton_hw_test->setStyleSheet("QPushButton {border: solid ; border-radius: 15;} QPushButton:focus { background-color: LightGrey; border: solid ; border-radius: 15;}");

    ui->pushButton_app->setFocus();

    process.setProcessChannelMode(QProcess::ForwardedChannels);

    QObject::connect( &process, SIGNAL(finished(int,QProcess::ExitStatus)),
                      this, SLOT(processFinished(int,QProcess::ExitStatus)));

    QObject::connect( &process, SIGNAL(error(QProcess::ProcessError)),
                      this, SLOT(processError(QProcess::ProcessError)));

    QObject::connect( &process, SIGNAL(started()), this, SLOT(processStarted()));

//    system("echo 200 > /sys/class/leds/lcd-backlight/brightness");
//    system("setkeycodes 0 1 1 30 2 48  3 46 4 32 5 18 8 33 9 34 a 35 b 23 c 36 d 37 10 38 11 50 12 49 13 24 14 25 15 16 18 19 19 31 1a 20 1b 22 1c 47 1d 17 20 69 21 45 22 21 23 44 24 57 25 28");
    system("setkeycodes 0 1 1 14 2 106 3 103 4 108 5 15 8 33 9 34 a 35 b 2 c 3 d 4 10 38 11 50 12 49 13 5 14 6 15 7 18 19 19 31 1a 20 1b 8 1c 9 1d 10 20 69 21 45 22 21 23 52 24 11 25 28");

    sleep(2);
    on_pushButton_app_clicked();
    showFullScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_app_clicked()
{
    //start app
    demo_status = true;
    process.start("/home/root/SC20_BALAJI_MILK_DPU", NULL);
    qDebug() << "starting app";

    msgBoxToastMessage = new QMessageBox(this);
    msgBoxToastMessage->setText("LAUNCHING\nDPU APPLICATION\n\nPLEASE WAIT...");
    msgBoxToastMessage->setStandardButtons(QMessageBox::NoButton);
    msgBoxToastMessage->setWindowFlags(Qt::WindowStaysOnTopHint);
    msgBoxToastMessage->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    msgBoxToastMessage->setStyleSheet("QMessageBox {border-style: solid;border-width: 3px;border-radius: 10px;font: bold 12pt Sans Serif rgb(209, 139, 0);color: rgb(209, 139, 0);background-color: rgb(255, 255, 255);}QMessageBox QLabel {font: bold 18px;text-align: center;padding: 5px 10px 5px 10px;}");
    msgBoxToastMessage->show();
}

void MainWindow::on_pushButton_settings_clicked()
{
    //start settings app
    demo_status = true;
    process.start("/home/root/SETTINGS", NULL);
    qDebug() << "starting settings app";

    msgBoxToastMessage = new QMessageBox(this);
    msgBoxToastMessage->setText("LAUNCHING\nSETTING APP\n\nPLEASE WAIT...");
    msgBoxToastMessage->setStandardButtons(QMessageBox::NoButton);
    msgBoxToastMessage->setWindowFlags(Qt::WindowStaysOnTopHint);
    msgBoxToastMessage->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    msgBoxToastMessage->setStyleSheet("QMessageBox {border-style: solid;border-width: 3px;border-radius: 10px;font: bold 12pt Sans Serif rgb(209, 139, 0);color: rgb(209, 139, 0);background-color: rgb(255, 255, 255);}QMessageBox QLabel {font: bold 18px;text-align: center;padding: 5px 10px 5px 10px;}");
    msgBoxToastMessage->show();
}


void MainWindow::on_pushButton_hw_test_clicked()
{
    demo_status = true;
    process.start("/home/root/HW_TEST", NULL);
    qDebug() << "starting hs_test";

    msgBoxToastMessage = new QMessageBox(this);
    msgBoxToastMessage->setText("LAUNCHING\nHWTEST APP\n\nPLEASE WAIT...");
    msgBoxToastMessage->setStandardButtons(QMessageBox::NoButton);
    msgBoxToastMessage->setWindowFlags(Qt::WindowStaysOnTopHint);
    msgBoxToastMessage->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    msgBoxToastMessage->setStyleSheet("QMessageBox {border-style: solid;border-width: 3px;border-radius: 10px;font: bold 12pt Sans Serif rgb(209, 139, 0);color: rgb(209, 139, 0);background-color: rgb(255, 255, 255);}QMessageBox QLabel {font: bold 18px;text-align: center;padding: 5px 10px 5px 10px;}");
    msgBoxToastMessage->show();
}


void MainWindow::processStarted()
{
    demo_status = true;
    for(int i = 0; i < 1000;i++)
    {
        usleep(100);
        QApplication::processEvents();
    }
    msgBoxToastMessage->accept();
    process.waitForFinished(-1);
//    ui->pushButton_settings->setFocus();
}

void MainWindow::processFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
//    QObject::disconnect(this, SIGNAL(demoStarted()), 0, 0);
//    QObject::disconnect(this, SIGNAL(demoFinished()), 0, 0);

    system("setkeycodes 0 1 1 14 2 106 3 103 4 108 5 15 8 33 9 34 a 35 b 2 c 3 d 4 10 38 11 50 12 49 13 5 14 6 15 7 18 19 19 31 1a 20 1b 8 1c 9 1d 10 20 69 21 45 22 21 23 52 24 11 25 28");    
    raise();
    activateWindow();
    for(int i = 0; i < 1000;i++)
    {
        usleep(100);
        QApplication::processEvents();
    }
    demo_status = false;
    system("killall wpa_supplicant");
    system("rm /var/run/wpa_supplicant/wlan0");
    system("sync");
}

void MainWindow::processError(QProcess::ProcessError err)
{
    if(err == QProcess::Crashed){       
        qApp->processEvents();
        system("setkeycodes 0 1 1 14 2 106 3 103 4 108 5 15 8 33 9 34 a 35 b 2 c 3 d 4 10 38 11 50 12 49 13 5 14 6 15 7 18 19 19 31 1a 20 1b 8 1c 9 1d 10 20 69 21 45 22 21 23 52 24 11 25 28");
        raise();
        activateWindow();
        for(int i = 0; i < 1000;i++)
        {
            usleep(100);
            QApplication::processEvents();
        }
        demo_status = false;
        system("killall wpa_supplicant");
        system("rm /var/run/wpa_supplicant/wlan0");
        system("sync");
    }
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if((event->type() == QEvent::KeyRelease || event->type() == QEvent::KeyPress) && stopped == 1)
    {
        event->accept();
        return true;
    }
    if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease)
    {
        QKeyEvent *keyEvent1 = static_cast<QKeyEvent *>(event);
//        qDebug() << "KEY : " << keyEvent1->key() << "demo_status" << demo_status << event->type() << event->spontaneous();
        return demo_status == true ? true : QObject::eventFilter(watched, event);
    }
    else {
        return QObject::eventFilter(watched, event);
    }
}
