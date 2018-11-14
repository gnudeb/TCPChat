#include "server.h"
#include <QTcpSocket>
#include <QHostAddress>
#include <thread.h>

Server::Server(QObject *parent) : QTcpServer(parent) {

}

void Server::start() {
    if (!listen(QHostAddress::LocalHost, 18998)) {
        qDebug() << "Could not start the server.";
    } else {
        qDebug() << "Server is running.";
    }
}

void Server::newMessage(qintptr socketDescriptor, QByteArray data) {
    qDebug()
        << "New message from "
        << socketDescriptor
        << ": "
        << data;

    // If client has no nickname, then treat their message as one
    if (clients.value(socketDescriptor).isEmpty()) {
        QString nickname = QString(data);
        clients.insert(socketDescriptor, nickname);
        qDebug() << "New member: " << nickname;
    } else {
        qDebug()
            << clients.value(socketDescriptor)
            << ": "
            << data;
        // TODO: Broadcast the message to all clients
    }
}

void Server::incomingConnection(qintptr socketDescriptor) {
    qDebug() << "New connection from " << socketDescriptor << ".";

    clients.insert(socketDescriptor, QString());

    Thread *thread = new Thread(static_cast<int>(socketDescriptor), this);
    connect(thread, &Thread::receivedData, this, &Server::newMessage, Qt::DirectConnection);
    connect(thread, &Thread::disconnected, this, &Server::clientDisconnected, Qt::DirectConnection);
    thread->start();
}

void Server::clientDisconnected(qintptr socketDescriptor) {
    clients.remove(socketDescriptor);
}

