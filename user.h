#ifndef USER_H
#define USER_H

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>

class User : public QObject {
    Q_OBJECT

private:
    QTcpSocket *socket = nullptr;

public:
    explicit User(QTcpSocket *socket, QObject *parent = nullptr);

signals:
    void sentData(QByteArray data);

public slots:
    void relayIncomingData();
    void receiveMessage(QByteArray data);
};

#endif // USER_H
