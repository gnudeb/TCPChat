#include "server.h"

Server::Server(QObject *parent) : QTcpServer(parent) {
    connect(this, &Server::newConnection, this, &Server::registerUser);
}

bool Server::start(quint16 port) {
    if (!listen(QHostAddress::LocalHost, port)) {
        qDebug() << "Could not start a server on port" << port;
        return false;
    }
    qDebug() << "Server is running on port" << port;
    return true;
}

void Server::registerUser() {
    QTcpSocket *socket = nextPendingConnection();
    User *user = new User(socket, this);
    connect(user, &User::sentData, this, &Server::handleNewMessage);
    connect(this, &Server::broadcasting, user, &User::receiveMessage);
    connect(user, &User::disconnected, this, &Server::handleDisconnect);
}

void Server::handleDisconnect(User *user) {
    disconnect(user, &User::sentData, this, &Server::handleNewMessage);
    disconnect(this, &Server::broadcasting, user, &User::receiveMessage);
    if (user->hasUsername()) {
        QString username = QString(user->getUsername());
        emit broadcasting(QString("User %1 disconnected.").arg(username).toUtf8(), nullptr);
    }
    user->deleteLater();
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
