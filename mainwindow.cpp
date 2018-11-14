#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostAddress>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_submitButton_clicked() {
    ui->chatText->append(ui->userInputLineEdit->text());
}

void MainWindow::on_toggleServerButton_clicked() {
    server = new Server(this);
    server->listen(QHostAddress::LocalHost, 18998);
}
