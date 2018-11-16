#ifndef SERVER_H
#define SERVER_H

#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include "user.h"

QByteArray sanitized(QByteArray data);

class Server : public QTcpServer {
    Q_OBJECT

public:
    Server(QObject *parent=nullptr);
    void start(quint16 port);

signals:
    void broadcasting(QByteArray message);

public slots:
    void broadcast(QByteArray message);
private slots:
    void registerUser();
};

#endif // SERVER_H
