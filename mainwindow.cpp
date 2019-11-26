#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <time.h>
#include <qinputdialog.h>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time_t(NULL));
    ui->lineEdit->setValidator(new QIntValidator(0,1000,this));
    ui->pushButtonFindGroup->setVisible(false);
    ui->pushButtonFindPrime->setVisible(false);
    ui->lineEdit->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buttonReset()
{
    ui->pushButtonFindGroup->setVisible(false);
    ui->pushButtonEditorOpen->setVisible(true);
    ui->pushButtonFindPrime->setVisible(false);
}



void MainWindow::on_pushButtonShowCluster_pressed()
{
    if(ui->lineEdit->text().toInt() > 3000){
        QMessageBox::critical(this,"UYARI","Lütfen daha küçük bir sayı girin!");
        return;
    }
    int module = ui->lineEdit->text().toInt();
    MyMath *mymath = new MyMath();
    QList <int> list;
    if(ui->comboBox->currentText() == "⊙"){
        try {
            list = mymath->multiplicativeZnGroup(module);
        } catch (const char* msg) {
            QMessageBox::critical(this,"ERROR",msg);
        }
    }

    if(ui->comboBox->currentText() == "⊕"){
        try {
            list = mymath->additiveZnGroup(module);
        } catch (const char* msg) {
            QMessageBox::critical(this,"ERROR",msg);
        }
    }

    if(!list.isEmpty()){
        QString cluster = "{ " + QString::number(list[0]);
        for(int i = 1; i < list.size(); i++){
            cluster += (", " + QString::number(list[i]));
        }
        cluster += " }";
        ui->plainTextEdit->setPlainText(cluster);

    }
}



void MainWindow::on_pushButtonShowGenerator_pressed()
{
    if(ui->lineEdit->text().toInt() > 3000){
        QMessageBox::critical(this,"UYARI","Lütfen daha küçük bir sayı girin!");
        return;
    }
    MyMath *mymath = new MyMath();
    QList <int> generatorList;

    if(ui->comboBox->currentText() == "⊙"){
        try {
            generatorList = mymath->FindMultiplicationGenerator(ui->lineEdit->text().toInt());
        } catch (const char* msg) {
            QMessageBox::critical(this,"ERROR",msg);
            return;
        }
    }

    if(ui->comboBox->currentText() == "⊕"){
        try {
            generatorList = mymath->findAdditiveGenerator(ui->lineEdit->text().toInt());
        } catch (const char* msg) {
            QMessageBox::critical(this,"ERROR",msg);
            return;
        }
    }

    if(!generatorList.isEmpty()){
        QString cluster = "<" + QString::number(generatorList[0]);
        for(int i = 1; i < generatorList.size(); i++){
            cluster += ("> = <" + QString::number(generatorList[i]));
        }
        cluster += ">\n\n\n" + QString::number(generatorList.size()) + " adet sonuç bulunmuştur.";
        ui->plainTextEdit->setPlainText(cluster);
    }
    else {
        ui->plainTextEdit->setPlainText("Üreteç bulunamamıştır.");
    }

}







void MainWindow::on_pushButtonShowSubGroups_pressed()
{
    if(ui->lineEdit->text().toInt() > 3000){
        QMessageBox::critical(this,"UYARI","Lütfen daha küçük bir sayı girin!");
        return;
    }

    MyMath *mymath = new MyMath();
    QList <QList <int>> subGroupsLists;
    if(ui->comboBox->currentText() == "⊙"){
        try {
           subGroupsLists = mymath->multiplicationSubGroups(ui->lineEdit->text().toInt());
        } catch (const char* msg) {
            QMessageBox::critical(this,"ERROR",msg);
            return;
        }
    }

    if(ui->comboBox->currentText() == "⊕"){
        try {
            subGroupsLists = mymath->additiveSubGroups(ui->lineEdit->text().toInt());
        } catch (const char* msg) {
            QMessageBox::critical(this,"ERROR",msg);
            return;
        }
    }

    QString clusters = "Alt Gruplar : \n\n";
    if(!subGroupsLists.isEmpty()){
        for (int i = 0; i < subGroupsLists.size(); i++) {
            clusters += ("\n" + QString::number(subGroupsLists[i].size()) + " mertebeli alt grup = { " +
                         QString::number(subGroupsLists[i][0]));
            for (int j = 1; j < subGroupsLists[i].size(); j++) {
                    clusters += ", " + QString::number(subGroupsLists[i][j]);
            }
            clusters += " }\n\n";
        }

        clusters += ("\n\n\n\n" + QString::number(subGroupsLists.size()) + " adet alt grup bulunmuştur...");

        ui->plainTextEdit->setPlainText(clusters);
    }
}











void MainWindow::on_pushButtonFindGroup_pressed()
{


    MyMath *mymath = new MyMath();

    bool ok;
    bool closed = false;
    bool unitElement = false;
    bool inverseElement = false;
    //buradan devam et
    int mod = QInputDialog::getInt(this, tr("Mod Belirleyin!"),
                                 tr("Değer :\t\t"), 1, 0, 10000, 1, &ok);

    QList <int> liste = mymath->getNumbers(form->readPlainText());
    if(!ok){
        return;
    }

    try {
        if(ui->comboBox->currentText() == "⊙"){
            if(mymath->IsMultiplyOff(liste,mod)){
                QMessageBox::information(this,"INFO","çarpımsal kapalı...");
                closed = true;
            }
            else {
                QMessageBox::critical(this,"INFO","çarpımsal kapalı değil");
            }
            if(mymath->multiplicativeUnit(liste,mod)){
                QMessageBox::information(this,"INFO","çarpımsal birimli");
                unitElement = true;
            }
            else {
                QMessageBox::critical(this,"INFO","çarpımsal birim yok");
            }
            if(mymath->multiplyInverse(liste,mod)){
                QMessageBox::information(this,"INFO","çarpımsal ters eleman var");
                inverseElement = true;
            }
            else {
                QMessageBox::critical(this,"INFO","çarpımsal ters yok");
            }
        }

            if(ui->comboBox->currentText() == "⊕"){
                if(mymath->IsAdditiveOff(liste,mod)){
                    QMessageBox::information(this,"INFO","toplamsal kapalı...");
                    closed = true;
                }
                else {
                    QMessageBox::critical(this,"INFO","toplamsal kapalı değil");
                }
                if(mymath->additiveUnit(liste,mod)){
                    QMessageBox::information(this,"INFO","toplamsal birimli");
                    unitElement = true;
                }
                else {
                    QMessageBox::critical(this,"INFO","toplamsal birim yok");
                }
                if(mymath->additiveInverse(liste,mod)){
                    QMessageBox::information(this,"INFO","toplamsal ters eleman var");
                    inverseElement = true;
                }
                else {
                    QMessageBox::critical(this,"INFO","toplamsal ters yok");
                }
            }
    } catch (const char* msg) {
        QMessageBox::critical(this,"ERROR",msg);
        return;
    }


        QList <int> set;
        for (int i = 0; i < liste.size(); i++) {
            if(!set.contains(liste[i] % mod)){
                set.push_back(liste[i] % mod);
            }

        }

        qSort(set);

    QString mytext = "Bulunan sayılar : \n\n";
    for (int i = 0; i < liste.size(); i++) {
        mytext += QString::number(liste[i]) + "  ";
    }
    mytext += "\n\n\nDenkleri : \n{ " + QString::number(set[0]);
    for (int i = 1; i < set.size(); i++) {
        mytext += (", " + QString::number(set[i]));
    }
    mytext += " } , (mod " + QString::number(mod) + ")";

    if(closed && unitElement && inverseElement){
        mytext += "\n\n( " + ui->comboBox->currentText() + " ) işlemine göre gruptur.";
    }
    else if (closed && unitElement) {
        mytext += "\n\n( " + ui->comboBox->currentText() + " ) işlemine göre monoiddir.";
    }
    else if (closed) {
        mytext += "\n\n( " + ui->comboBox->currentText() + " ) işlemine göre yarı gruptur.";
    }
    else {
        mytext += "\n\n ( " + ui->comboBox->currentText() + " ) işlemine göre cebirsel yapı belirtmez.";
    }
    ui->plainTextEdit->setPlainText(mytext);
}







void MainWindow::on_pushButtonEditorOpen_pressed()
{
    form = new Form(this);
    form->show();
    ui->pushButtonEditorOpen->setVisible(false);
    ui->pushButtonFindGroup->setVisible(true);
    ui->pushButtonFindPrime->setVisible(true);
}

void MainWindow::on_pushButtonIsPrime_pressed()
{
    if(ui->lineEdit->text() == ""){
        QMessageBox::critical(this,"ERROR","Invalid argument!");
        return;
    }

    MyMath math;

    if(math.isPrime(ui->lineEdit->text().toInt())){
        QMessageBox::information(this,"SONUÇ", ui->lineEdit->text() + " sayısı asaldır.");
    }
    else {
        QMessageBox::information(this,"SONUÇ", ui->lineEdit->text() + " sayısı asal değildir.");
    }
}

void MainWindow::on_pushButtonFindPrime_pressed()
{
    if(form->readPlainText() == ""){
        QMessageBox::critical(this,"ERROR","Invalid argument");
        return;
    }
    MyMath *mymath = new MyMath();
    int count = 0;
    QString text = "Bulunan asal sayılar : \n";
    QString testText = form->readPlainText();
    QList <int> list = mymath->getNumbers(form->readPlainText());

    if(testText.at(0) == "(" && testText.at(testText.length() - 1) == ")" && list.size() == 2){
        if(list[0] > list[1]){
            mymath->swap(&list[0],&list[1]);
        }
        for (int i = list[0]; i <= list[1]; i++) {
            if(mymath->isPrime(i)){
                text += QString::number(i) + "  ";
                count++;
            }
        }
        if(count > 0){
            text += "\n\n" + QString::number(count) + " adet sonuç bulunmuştur";
            ui->plainTextEdit->setPlainText(text);
        }
        else {
            QMessageBox::information(this,"INFO","Bu aralıkta asal sayı bulunamamıştır!");
            return;
        }
    }
    else {
        text = "Bulunan sayılar : \n\n";
        for (int i = 0; i < list.size(); i++) {
            text += QString::number(list[i]) + "  ";
        }
        text += "\n\n" + QString::number(list.size()) + " adet sayı bulunmuştur.\n\nBulunan asal sayılar : \n\n";
        for (int i = 0; i < list.size(); i++) {
            if(mymath->isPrime(list[i])){
                text += QString::number(list[i]) + "  ";
                count++;
            }
        }
            text += "\n\n" + QString::number(count) + " adet asal sayı bulunmuştur.";
            ui->plainTextEdit->setPlainText(text);
        if(count < 1) {
            QMessageBox::information(this,"INFO","Girilen sayıların içinde asal sayı bulunamamıştır!");
        }
    }

}


void MainWindow::on_pushButtonClear_pressed()
{
    ui->plainTextEdit->clear();
}
