#include "widget.h"
#include "./ui_widget.h"
#include "QMessageBox"
#include "fifo.h"
#include "lru.h"
#include "opt.h"

//创建并初始化窗口
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    int size_random = ui->lineEdit->text().toInt();
    int page_size = ui->lineEdit_2->text().toInt();
    int memory_size = ui->lineEdit_3->text().toInt();
    int* randomArray;
    randomArray = (int*)malloc(sizeof(int) * size_random);
    for (int k = 0; k < size_random; k++) {
        int temp = rand() % page_size;
        randomArray[k] = temp;
    }

    QStringList stringList;
    for (int i = 0; i < size_random; ++i) {
        stringList << QString::number(randomArray[i]);
    }
    QString str = stringList.join(", ");

    ui->textEdit_4->setText(str);

    QString fifo_result = QString(QString::fromLocal8Bit(FIFO(page_size, size_random, memory_size, randomArray).c_str()));
    QString lru_result = QString(QString::fromLocal8Bit(lru(memory_size, size_random, randomArray).c_str()));
    QString opt_result = QString(QString::fromLocal8Bit(opt(memory_size, size_random, randomArray).c_str()));

    ui->textEdit->setText(fifo_result);
    ui->textEdit_2->setText(lru_result);
    ui->textEdit_3->setText(opt_result);

    free(randomArray);
}


void Widget::on_pushButton_2_clicked()
{
    close();
}

