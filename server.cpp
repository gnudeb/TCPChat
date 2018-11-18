#include "server.h"

Server::Server(QObject *parent) : QTcpServer(parent) {
    connect(this, &Server::newConnection, this, &Server::registerUser);
}

void Server::start(quint16 port) {
    if (!listen(QHostAddress::LocalHost, port)) {
        qDebug() << "Could not start a server on port" << port;
        return;
    }
    qDebug() << "Server is running on port" << port;
}

void Server::registerUser() {
    QTcpSocket *socket = nextPendingConnection();
    User *user = new User(socket, this);
    connect(user, &User::sentData, this, &Server::handleNewMessage);
    connect(this, &Server::broadcasting, user, &User::receiveMessage);
}

void Server::handleNewMessage(QByteArray message, User *user) {
    if (user == nullptr) {
        qDebug() << "Message from server" << ":" << message;
        emit broadcasting(sanitized(message), nullptr);
    } else if (!user->hasUsername()) {
        user->setUsername(sanitized(message));

        QString out = QString("User %1 has joined!").arg(QString(user->getUsername()));
        emit broadcasting(out.toUtf8(), nullptr);
    } else {
        qDebug() << "New message from" << user->getUsername() << ":" << message;
        emit broadcasting(sanitized(message), user);
    }
}

QByteArray sanitized(QByteArray data) {
    data.replace('\r', "");
    data.replace('\n', "");
    return data;
}
