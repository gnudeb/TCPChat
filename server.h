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
    bool start(quint16 port);

signals:
    void broadcasting(QByteArray message, User *user);

public slots:
    void handleNewMessage(QByteArray message, User *user);
private slots:
    void registerUser();
    void handleDisconnect(User *user);
};

#endif // SERVER_H
