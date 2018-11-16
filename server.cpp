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
    connect(user, &User::sentData, this, &Server::broadcast);
    connect(this, &Server::broadcasting, user, &User::receiveMessage);
}

void Server::broadcast(QByteArray message) {
    emit broadcasting(message);
}
