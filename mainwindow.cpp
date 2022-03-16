#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCoreApplication>
#include <QByteArray>
#include <QString>
#include <QFile>
#include <QFileDialog>


 //Объявляем имя файла, который мы будем выбирать из button3

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::Compress (){
    QFileInfo fileNameInInfo(fileNameIn); //Берем информацию о выбранном файле, чтобы затем поменять его суффикс на нужный нам для выходного файла
    QString newFileName = fileNameInInfo.path() + "/" + fileNameInInfo.completeBaseName() + ".dat";

    QFile fileNameToCompress = fileNameIn; //Файл, который мы будем сжимать
    QFile fileNameOut = newFileName; //Файл, который мы получим на выходе

    fileNameToCompress.open(QIODevice::ReadOnly); //Открываем файлы
    fileNameOut.open(QIODevice::WriteOnly);

    QByteArray uncompressedData = fileNameToCompress.readAll(); //Читаем данные из файла и заносим их в переменную
    QByteArray compressedData = qCompress(uncompressedData,9); //Сжимаем в режиме 9, т.к. этот режим имеет самое медленное, но самое сильное сжатие, исходя из документации
    fileNameOut.write(compressedData); //Записываем сжатые данные в файл

    fileNameToCompress.close(); //Не забываем закрыть
    fileNameOut.close();
}

void MainWindow::Uncompress (){
    QFileInfo fileNameInInfo(fileNameIn); //Берем информацию о выбранном файле, чтобы затем поменять его суффикс на нужный нам для выходного файла
    QString newFileName = fileNameInInfo.path() + "/" + fileNameInInfo.completeBaseName() + ".txt"; //Меняем суфикс

    QFile fileNameToUncompress = fileNameIn; //Файл, который мы будем разжимать
    QFile fileNameOut = newFileName; //Файл, который мы получим на выходе

    fileNameToUncompress.open(QIODevice::ReadOnly);
    fileNameOut.open(QIODevice::WriteOnly);

    QByteArray uncompressedData = fileNameToUncompress.readAll(); //Считываем данные из бинарника
    QByteArray compressedData = qUncompress(uncompressedData); //Разжимаем их
    fileNameOut.write(compressedData);//Записываем в файл с суффиксом .txt

    fileNameToUncompress.close();
    fileNameOut.close();
}


void MainWindow::on_pushButton_3_clicked()
{    
    fileNameIn = QFileDialog::getOpenFileName(); //Верхняя кнопка, открывает диалоговое окно для выбора файла
    ui->label->setText(fileNameIn); //Перенесем в лейбл, чтобы пользователь видел какой файл он открыл
}


void MainWindow::on_pushButton_clicked()
{
    Compress();
}


void MainWindow::on_pushButton_2_clicked()
{
    Uncompress();
}

