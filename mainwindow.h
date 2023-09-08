#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<qprocess.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_app_clicked();
    void on_pushButton_settings_clicked();

    void on_pushButton_hw_test_clicked();

public slots:
    void processStarted();
    void processFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void processError(QProcess::ProcessError err);

private:
    Ui::MainWindow *ui;
    bool eventFilter(QObject *watched, QEvent *event);

private:
    QProcess process;

};

#endif // MAINWINDOW_H
