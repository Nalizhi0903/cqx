#ifndef TESTTHREAD_H
#define TESTTHREAD_H

#include <QObject>
#include <QThread>

class RecvThread : public QThread
{
    Q_OBJECT
public:
    explicit RecvThread(QObject *parent = nullptr);

private:
    //重写run方法
    void run();

signals:
    //定义信号
    void ShowDownloadProgress(int progress);

public slots:
};

#endif // TESTTHREAD_H
