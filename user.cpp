#include "user.h"

User::User(QTcpSocket *socket, QObject *parent) : QObject(parent), socket(socket) {
    connect(socket, &QTcpSocket::readyRead, this, &User::relayIncomingData);
}

void User::relayIncomingData() {
    while (!socket->atEnd()) {
        emit sentData(socket->readLine());
    }
}

void User::receiveMessage(QByteArray data) {
    socket->write(data.append('\n'));
    socket->flush();
}
