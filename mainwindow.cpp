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

void MainWindow::handleBroadcast(QByteArray message) {
    ui->chatText->append(QString(message));
}

void MainWindow::performBroadcast() {
    QString message = ui->userInputLineEdit->text();

    if (message.isEmpty()) {
        return;
    }

    QByteArray data = message.toUtf8();
    server->broadcast(data);

    ui->userInputLineEdit->clear();
}
