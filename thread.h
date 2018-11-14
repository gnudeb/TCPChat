#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QByteArray>

class Thread : public QThread {
    Q_OBJECT

public:
    Thread(int socketDescriptor, QObject *parent);
    void run();

private:
    QTcpSocket *socket;
    int socketDescriptor;

signals:
    void error(QTcpSocket::SocketError socketError);
    void receivedData(qintptr socketDescriptor, QByteArray data);
    void disconnected(qintptr socketDescriptor);

public slots:
    void handleNewData();
    void handleDisconnection();
};

#endif // THREAD_H
