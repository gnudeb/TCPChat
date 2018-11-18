#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostAddress>
#include <QByteArray>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    server = new Server(this);
    connect(server, &Server::broadcasting, this, &MainWindow::handleBroadcast);
    server->start(18998);

    ui->setupUi(this);

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
        out = QString("%1: %2")
            .arg(QString(user->getUsername()))
            .arg(QString(message));
    } else {
        out = QString(message);
    }
    ui->chatText->append(out);
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
