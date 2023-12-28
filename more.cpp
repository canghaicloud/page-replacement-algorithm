#include "more.h"
#include "ui_more.h"

more::more(QWidget *parent, QString lfu_result, QString clock_result)
    : QWidget(parent)
    , ui(new Ui::more)
{
    ui->setupUi(this);
    ui->textEdit->setText(lfu_result);
    ui->textEdit_2->setText(clock_result);

}

more::~more()
{
    delete ui;
}
