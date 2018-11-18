#ifndef USER_H
#define USER_H

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>

class User : public QObject {
    Q_OBJECT

private:
    QTcpSocket *socket = nullptr;
    QByteArray *username = nullptr;

public:
    explicit User(QTcpSocket *socket, QObject *parent = nullptr);
    bool hasUsername();
    QByteArray getUsername();
    void setUsername(QByteArray username);

signals:
    void sentData(QByteArray data, User *user);

public slots:
    void relayIncomingData();
    void receiveMessage(QByteArray data, User *user);
};

#endif // USER_H
