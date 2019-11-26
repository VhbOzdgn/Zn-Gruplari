#include "form.h"
#include "ui_form.h"
#include "mainwindow.h"
#include <QTextStream>
#include <QFileDialog>

Form::Form(MainWindow *from,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    mainwindow = from;
}

Form::~Form()
{
    mainwindow->buttonReset();
    delete ui;
}

QString Form::readPlainText()
{
    return ui->plainTextEdit->toPlainText();
}

void Form::on_pushButtonClear_pressed()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Uyarı!", "Silmek istiyor musunuz ?",
                                  QMessageBox::Yes|QMessageBox::No);
    if(reply == QMessageBox::Yes){
        ui->plainTextEdit->clear();
    }

}

void Form::dragEnterEvent(QDragEnterEvent *event)
{
    event->accept();
}

void Form::dropEvent(QDropEvent *event)
{
    QList<QUrl> paths = event->mimeData()->urls();
    if(paths.isEmpty())
        return;

    path = paths.first().toLocalFile();
    readContent();
}

void Form::readContent()
{
    QFile file(path);
    if(file.open(QFile::ReadOnly)){
        QTextStream read(&file);
        QString reading = read.readAll();
        ui->plainTextEdit->setPlainText(reading);
        file.close();
    }
}

void Form::on_pushButtonChooseFile_pressed()
{
    path = QFileDialog::getOpenFileName(this,"Text Dosya Aç","");
    if(path.isEmpty())
        return;

    readContent();
}
