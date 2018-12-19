#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostAddress>
#include <QByteArray>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    server = new Server(this);

    ui->setupUi(this);

    connect(
        ui->toggleServerButton, &QPushButton::clicked,
        this, &MainWindow::toggleServer);

    connect(
        ui->userInputLineEdit, &QLineEdit::editingFinished,
        this, &MainWindow::performBroadcast);
    connect(
        ui->submitButton, &QPushButton::clicked,
        this, &MainWindow::performBroadcast);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::handleBroadcast(QByteArray message, User *user) {
    QString out;
    if (user != nullptr) {
        out = QString("<b>%1:</b> %2")
            .arg(QString(user->getUsername()))
            .arg(QString(message));
    } else {
        out = QString(message);
    }
    dumpInfo(out);
}

void MainWindow::performBroadcast() {
    QString message = ui->userInputLineEdit->text();

    if (message.isEmpty()) {
        return;
    }

    QByteArray data = message.toUtf8();
    server->handleNewMessage(data, nullptr);

    ui->userInputLineEdit->clear();
}

void MainWindow::toggleServer() {
    if (!server->isListening()) {
        quint16 port = ui->portLineEdit->text().toUShort();
        if (!server->start(port)) {
            dumpInfo(QString("Failed to start a server on port %1").arg(port));
            return;
        }

        connect(server, &Server::broadcasting, this, &MainWindow::handleBroadcast);

        dumpInfo(QString("Server is running on port %1").arg(port));
        ui->serverPanelFrame->setEnabled(true);
        ui->chatText->setEnabled(true);
    }
}

void MainWindow::dumpInfo(QString info) {
    QString time = QTime::currentTime().toString("hh:mm:ss");
    ui->chatText->append(QString("<b>%1</b> %2").arg(time).arg(info));
    qDebug() << info;
}
