#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include <QMap>

class Server : public QTcpServer {
    Q_OBJECT
public:
    Server(QObject *parent = Q_NULLPTR);
    void start();

private:
    QMap<qintptr, QString> clients;

private slots:
    void newMessage(qintptr socketDescriptor, QByteArray data);
    void clientDisconnected(qintptr socketDescriptor);

protected:
    void incomingConnection(qintptr socketDescriptor);
};

#endif // SERVER_H
