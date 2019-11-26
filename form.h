#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

class MainWindow;


namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(MainWindow* from,QWidget *parent = nullptr);
    ~Form();
    QString readPlainText();

private slots:
    void on_pushButtonClear_pressed();

    void on_pushButtonChooseFile_pressed();

private:
    Ui::Form *ui;
    MainWindow *mainwindow;
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void readContent();
    QString path = "";
};

#endif // FORM_H
