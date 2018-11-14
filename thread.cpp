#include "thread.h"
#include <QDebug>

Thread::Thread(int socketDescriptor, QObject *parent) : QThread(parent) {
    this->socketDescriptor = socketDescriptor;
}

void Thread::run() {
    qDebug() << "Starting thread for socket " << socketDescriptor << "...";

    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));

    socket = new QTcpSocket();
    if (!socket->setSocketDescriptor(socketDescriptor)) {
        emit error(socket->error());
        return;
    }

    connect(socket, SIGNAL(readyRead()), this, SLOT(handleNewData()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(handleDisconnection()), Qt::DirectConnection);

    qDebug() << "Thread started for socket" << socketDescriptor << ".";

    exec();
}

void Thread::handleNewData() {
    qintptr socketDescriptor = socket->socketDescriptor();
    QByteArray data = socket->readAll();
    emit receivedData(socketDescriptor, data);
}

void Thread::handleDisconnection() {
    qDebug() << "Socket " << socketDescriptor << " disconnected.";
    emit disconnected(socketDescriptor);
    socket->deleteLater();
    exit(0);
}
