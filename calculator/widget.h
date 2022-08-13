#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QPushButton>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QGridLayout>
#include<QLineEdit>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    //数字
    QPushButton* num_button[10];
    //运算符
    QPushButton* add_button;
    QPushButton* sub_button;
    QPushButton* mul_button;
    QPushButton* div_button;
    //计算键
    QPushButton* cal_button;
    //删除键
    QPushButton* del_button;
    //布局
    QHBoxLayout* qhboxlayout;
    QVBoxLayout* qvboxlayout;
    QGridLayout* qgrilayout;
    QLineEdit* output;
    int data1;
    int data2;
    int sum = 0;
    bool judge = true;
    bool judge_op = true;
    QString op;
public slots:
    void cal_solt();
    void op_slot();
    void number_slot();
private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
