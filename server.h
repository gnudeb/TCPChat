#ifndef SERVER_H
#define SERVER_H

#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include "user.h"

class Server : public QTcpServer {
    Q_OBJECT

public:
    Server(QObject *parent=nullptr);
    void start(quint16 port);

signals:
    void broadcasting(QByteArray message);

private slots:
    void broadcast(QByteArray message);
    void registerUser();
};

#endif // SERVER_H
