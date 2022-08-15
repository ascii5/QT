#include "widget.h"
#include "./ui_widget.h"
#include<QFileDialog>
#include<QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("文件加密工具");
    this->setWindowIcon(QIcon(":/iconfont.png"));
}

Widget::~Widget()
{
    delete ui;
}




void Widget::on_encode_clicked()
{
    if(filename.compare("0") == 0)
        QMessageBox::information(this,"","未选择文件!");
    else
    {
         QFile f(filename);
         f.open(QIODevice::ReadWrite);
         QByteArray buf = f.readAll();
         ui->progressBar->setRange(0,buf.length() - 1);
         for(int i = 0; i < buf.length();i++)
         {
             buf[i] = ~buf[i];
             ui->progressBar->setValue(i);

         }
         f.seek(0);
         f.write(buf);
         f.close();
    }
}


void Widget::on_unencode_clicked()
{
    if(filename.compare("0") == 0)
        QMessageBox::information(this,"","未选择文件!");
    else
    {
         QFile f(filename);
         f.open(QIODevice::ReadWrite);
         QByteArray buf = f.readAll();
         ui->progressBar->setRange(0,buf.length() - 1);
         for(int i = 0; i < buf.length();i++)
         {
             buf[i] = ~buf[i];
             ui->progressBar->setValue(i);

         }
         f.seek(0);
         f.write(buf);
         f.close();
    }
}


void Widget::on_view_clicked()
{
    filename = QFileDialog::getOpenFileName();
    ui->lineEdit->setText(filename);
}

