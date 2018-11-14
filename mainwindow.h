#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <server.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_submitButton_clicked();

    void on_toggleServerButton_clicked();

private:
    Ui::MainWindow *ui;
    Server *server;
};

#endif // MAINWINDOW_H
