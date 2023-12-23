#include "widget.h"
#include "./ui_widget.h"
#include "QMessageBox"
#include "fifo.h"
#include "lru.h"
#include "opt.h"

#pragma execution_character_set("utf-8")

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
    bool sign_1, sign_2, sign_3;
    int size_random = ui->lineEdit->text().toInt(&sign_1);
    int page_size = ui->lineEdit_2->text().toInt(&sign_2);
    int memory_size = ui->lineEdit_3->text().toInt(&sign_3);

    if(sign_1 && sign_2 && sign_3){
        if (size_random <= 0 || size_random > 100) {
            QMessageBox::warning(this, "输入错误", "访问序列的范围为0~100");
            return;
        }
        if (page_size <= 1 || page_size > 50) {
            QMessageBox::warning(this, "输入错误", "页表长度的范围为2~50");
            return;
        }
        if(memory_size == 0 || memory_size > 25){
            QMessageBox::warning(this, "输入错误", "内存大小范围为1~25");
            return;
        }
        if(size_random < 2*page_size || page_size < 2*memory_size){
            QMessageBox::warning(this, "输入错误", "数据条件：sequence_length >= 2*page_table_length && page_table_length >= 2*memory_size");
            return;
        }
    } else {
        //转换失败
        QMessageBox::warning(this, "输入错误", "请输入有效整数");
        return;
    }


    int* randomArray;
    randomArray = (int*)malloc(sizeof(int) * size_random);
    QString inputText = ui->textEdit_4->toPlainText().trimmed();// 获取用户在 textEdit_4 中输入的文本
    if (inputText.isEmpty()) {
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
    } else {
        // 使用正则表达式检查输入是否为合法的数组（数字之间用逗号分隔）
        QRegExp regex("^[0-9]+(, [0-9]+)*$");
        if (!regex.exactMatch(inputText)) {
            // 如果不是合法的数组，弹出错误提示窗口
            QMessageBox::critical(this, "错误", "输入序列不合法");
            free(randomArray);
            return;
        }

        // 将输入的数组字符串分割成数字并添加到 QVector 中
        QStringList numbers = inputText.split(",");
        QVector<int> tempArray;
        for (const QString& number : numbers) {
            tempArray.append(number.toInt());
        }

        // 检测数组的长度和最大元素是否符合条件
        if (tempArray.size() != size_random || *std::max_element(tempArray.begin(), tempArray.end()) > (page_size - 1)) {
            // 如果不满足条件，弹出错误提示窗口
            QMessageBox::critical(this, "错误", "输入序列与输入信息不匹配");
            free(randomArray);
            return;
        } else {
            // 如果满足条件，将临时数组的数据复制到 randomArray 中
            free(randomArray);  // 删除原有的内存
            randomArray = (int*)malloc(sizeof(int) * size_random);
            copy(tempArray.begin(), tempArray.end(), randomArray);
        }
    }

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
    // 清空 lineEdit 的内容
    ui->lineEdit->clear();

    // 清空 lineEdit_1 的内容
    ui->lineEdit_2->clear();

    // 清空 lineEdit_2 的内容
    ui->lineEdit_3->clear();

    // 清空 textEdit_4 的内容
    ui->textEdit_4->clear();

    // 清空 textEdit 的内容
    ui->textEdit->clear();

    // 清空 textEdit_2 的内容
    ui->textEdit_2->clear();

    // 清空 textEdit_3 的内容
    ui->textEdit_3->clear();
}

void Widget::on_pushButton_3_clicked()
{
    bool sign_1, sign_2, sign_3;
    int size_random = ui->lineEdit->text().toInt(&sign_1);
    int page_size = ui->lineEdit_2->text().toInt(&sign_2);
    int memory_size = ui->lineEdit_3->text().toInt(&sign_3);

    if(sign_1 && sign_2 && sign_3){
        if (size_random <= 0 || size_random > 100) {
            QMessageBox::warning(this, "输入错误", "访问序列的范围为0~100");
            return;
        }
        if (page_size <= 1 || page_size > 50) {
            QMessageBox::warning(this, "输入错误", "页表长度的范围为2~50");
            return;
        }
        if(memory_size == 0 || memory_size > 25){
            QMessageBox::warning(this, "输入错误", "内存大小范围为1~25");
            return;
        }
        if(size_random < 2*page_size || page_size < 2*memory_size){
            QMessageBox::warning(this, "输入错误", "数据条件：sequence_length >= 2*page_table_length && page_table_length >= 2*memory_size");
            return;
        }
    } else {
        //转换失败
        QMessageBox::warning(this, "输入错误", "请输入有效整数");
        return;
    }


    int* randomArray;
    randomArray = (int*)malloc(sizeof(int) * size_random);
    QString inputText = ui->textEdit_4->toPlainText().trimmed();// 获取用户在 textEdit_4 中输入的文本
    if (inputText.isEmpty()) {
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
    } else {
        // 使用正则表达式检查输入是否为合法的数组（数字之间用逗号分隔）
        QRegExp regex("^[0-9]+(, [0-9]+)*$");
        if (!regex.exactMatch(inputText)) {
            // 如果不是合法的数组，弹出错误提示窗口
            QMessageBox::critical(this, "错误", "输入序列不合法");
            free(randomArray);
            return;
        }

        // 将输入的数组字符串分割成数字并添加到 QVector 中
        QStringList numbers = inputText.split(",");
        QVector<int> tempArray;
        for (const QString& number : numbers) {
            tempArray.append(number.toInt());
        }

        // 检测数组的长度和最大元素是否符合条件
        if (tempArray.size() != size_random || *std::max_element(tempArray.begin(), tempArray.end()) > (page_size - 1)) {
            // 如果不满足条件，弹出错误提示窗口
            QMessageBox::critical(this, "错误", "输入序列与输入信息不匹配");
            free(randomArray);
            return;
        } else {
            // 如果满足条件，将临时数组的数据复制到 randomArray 中
            free(randomArray);  // 删除原有的内存
            randomArray = (int*)malloc(sizeof(int) * size_random);
            copy(tempArray.begin(), tempArray.end(), randomArray);
        }
    }

    QString fifo_result = QString(QString::fromLocal8Bit(FIFO(page_size, size_random, memory_size, randomArray).c_str()));

    ui->textEdit->setText(fifo_result);

    free(randomArray);
}


void Widget::on_pushButton_4_clicked()
{
    bool sign_1, sign_2, sign_3;
    int size_random = ui->lineEdit->text().toInt(&sign_1);
    int page_size = ui->lineEdit_2->text().toInt(&sign_2);
    int memory_size = ui->lineEdit_3->text().toInt(&sign_3);

    if(sign_1 && sign_2 && sign_3){
        if (size_random <= 0 || size_random > 100) {
            QMessageBox::warning(this, "输入错误", "访问序列的范围为0~100");
            return;
        }
        if (page_size <= 1 || page_size > 50) {
            QMessageBox::warning(this, "输入错误", "页表长度的范围为2~50");
            return;
        }
        if(memory_size == 0 || memory_size > 25){
            QMessageBox::warning(this, "输入错误", "内存大小范围为1~25");
            return;
        }
        if(size_random < 2*page_size || page_size < 2*memory_size){
            QMessageBox::warning(this, "输入错误", "数据条件：sequence_length >= 2*page_table_length && page_table_length >= 2*memory_size");
            return;
        }
    } else {
        //转换失败
        QMessageBox::warning(this, "输入错误", "请输入有效整数");
        return;
    }


    int* randomArray;
    randomArray = (int*)malloc(sizeof(int) * size_random);
    QString inputText = ui->textEdit_4->toPlainText().trimmed();// 获取用户在 textEdit_4 中输入的文本
    if (inputText.isEmpty()) {
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
    } else {
        // 使用正则表达式检查输入是否为合法的数组（数字之间用逗号分隔）
        QRegExp regex("^[0-9]+(, [0-9]+)*$");
        if (!regex.exactMatch(inputText)) {
            // 如果不是合法的数组，弹出错误提示窗口
            QMessageBox::critical(this, "错误", "输入序列不合法");
            free(randomArray);
            return;
        }

        // 将输入的数组字符串分割成数字并添加到 QVector 中
        QStringList numbers = inputText.split(",");
        QVector<int> tempArray;
        for (const QString& number : numbers) {
            tempArray.append(number.toInt());
        }

        // 检测数组的长度和最大元素是否符合条件
        if (tempArray.size() != size_random || *std::max_element(tempArray.begin(), tempArray.end()) > (page_size - 1)) {
            // 如果不满足条件，弹出错误提示窗口
            QMessageBox::critical(this, "错误", "输入序列与输入信息不匹配");
            free(randomArray);
            return;
        } else {
            // 如果满足条件，将临时数组的数据复制到 randomArray 中
            free(randomArray);  // 删除原有的内存
            randomArray = (int*)malloc(sizeof(int) * size_random);
            copy(tempArray.begin(), tempArray.end(), randomArray);
        }
    }

    QString lru_result = QString(QString::fromLocal8Bit(lru(memory_size, size_random, randomArray).c_str()));

    ui->textEdit_2->setText(lru_result);

    free(randomArray);
}


void Widget::on_pushButton_5_clicked()
{
    bool sign_1, sign_2, sign_3;
    int size_random = ui->lineEdit->text().toInt(&sign_1);
    int page_size = ui->lineEdit_2->text().toInt(&sign_2);
    int memory_size = ui->lineEdit_3->text().toInt(&sign_3);

    if(sign_1 && sign_2 && sign_3){
        if (size_random <= 0 || size_random > 100) {
            QMessageBox::warning(this, "输入错误", "访问序列的范围为0~100");
            return;
        }
        if (page_size <= 1 || page_size > 50) {
            QMessageBox::warning(this, "输入错误", "页表长度的范围为2~50");
            return;
        }
        if(memory_size == 0 || memory_size > 25){
            QMessageBox::warning(this, "输入错误", "内存大小范围为1~25");
            return;
        }
        if(size_random < 2*page_size || page_size < 2*memory_size){
            QMessageBox::warning(this, "输入错误", "数据条件：sequence_length >= 2*page_table_length && page_table_length >= 2*memory_size");
            return;
        }
    } else {
        //转换失败
        QMessageBox::warning(this, "输入错误", "请输入有效整数");
        return;
    }


    int* randomArray;
    randomArray = (int*)malloc(sizeof(int) * size_random);
    QString inputText = ui->textEdit_4->toPlainText().trimmed();// 获取用户在 textEdit_4 中输入的文本
    if (inputText.isEmpty()) {
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
    } else {
        // 使用正则表达式检查输入是否为合法的数组（数字之间用逗号分隔）
        QRegExp regex("^[0-9]+(, [0-9]+)*$");
        if (!regex.exactMatch(inputText)) {
            // 如果不是合法的数组，弹出错误提示窗口
            QMessageBox::critical(this, "错误", "输入序列不合法");
            free(randomArray);
            return;
        }

        // 将输入的数组字符串分割成数字并添加到 QVector 中
        QStringList numbers = inputText.split(",");
        QVector<int> tempArray;
        for (const QString& number : numbers) {
            tempArray.append(number.toInt());
        }

        // 检测数组的长度和最大元素是否符合条件
        if (tempArray.size() != size_random || *std::max_element(tempArray.begin(), tempArray.end()) > (page_size - 1)) {
            // 如果不满足条件，弹出错误提示窗口
            QMessageBox::critical(this, "错误", "输入序列与输入信息不匹配");
            free(randomArray);
            return;
        } else {
            // 如果满足条件，将临时数组的数据复制到 randomArray 中
            free(randomArray);  // 删除原有的内存
            randomArray = (int*)malloc(sizeof(int) * size_random);
            copy(tempArray.begin(), tempArray.end(), randomArray);
        }
    }

    QString opt_result = QString(QString::fromLocal8Bit(opt(memory_size, size_random, randomArray).c_str()));

    ui->textEdit_3->setText(opt_result);

    free(randomArray);
}

