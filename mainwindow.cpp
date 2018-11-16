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

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::handleBroadcast(QByteArray message) {
    ui->chatText->append(QString(message));
}
