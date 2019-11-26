#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mymath.h"
#include <QMessageBox>
#include "form.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void buttonReset();



private slots:

    void on_pushButtonShowCluster_pressed();

    void on_pushButtonShowGenerator_pressed();

    void on_pushButtonShowSubGroups_pressed();

    void on_pushButtonFindGroup_pressed();

    void on_pushButtonEditorOpen_pressed();

    void on_pushButtonIsPrime_pressed();

    void on_pushButtonFindPrime_pressed();



    void on_pushButtonClear_pressed();

private:
    Ui::MainWindow *ui;
    Form *form = nullptr;

};

#endif // MAINWINDOW_H
