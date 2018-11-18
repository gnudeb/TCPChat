#include "user.h"

User::User(QTcpSocket *socket, QObject *parent) : QObject(parent), socket(socket) {
    connect(socket, &QTcpSocket::readyRead, this, &User::relayIncomingData);
}

bool User::hasUsername() {
    return username != nullptr;
}

QByteArray User::getUsername() {
    return *username;
}

void User::setUsername(QByteArray username) {
    this->username = new QByteArray(username);
}

void User::relayIncomingData() {
    while (!socket->atEnd()) {
        emit sentData(socket->readLine(), this);
    }
}

void User::receiveMessage(QByteArray data, User *user) {
    if (user != nullptr) {
        socket->write(user->getUsername());
        socket->write(": ");
    }
    socket->write(data);
    socket->write("\n");
    socket->flush();
}
