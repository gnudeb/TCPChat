#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QByteArray>
#include "server.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleBroadcast(QByteArray message, User *user);
    void performBroadcast();
    void toggleServer();

private:
    Ui::MainWindow *ui;
    Server *server;
};

#endif // MAINWINDOW_H
