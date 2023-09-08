#ifndef APPLICATION_H
#define APPLICATION_H

#include <QProcess>
#include <QObject>

class application
{
public:
    application();
    void launch();
    QImage getImage() const;
    QString getCaption();

public slots:
    void processStarted();
    void processFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void processError(QProcess::ProcessError err);
signals:
    void demoStarted();
    void demoFinished();

private:
    QString imagePath;
    QString appCaption;
    QString executablePath;
    QStringList arguments;
    QProcess process;
};

#endif // APPLICATION_H
