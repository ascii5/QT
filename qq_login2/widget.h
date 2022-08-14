#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QLabel>
#include<QLineEdit>
#include<QPushButton>
#include<QCheckBox>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QPainter>
#include<QPaintEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    //控件
    QLabel* username;
    QLabel* password;
    QPushButton* login;
    QPushButton* exit;
    QCheckBox* show_password;
    QLineEdit* line_user;
    QLineEdit* line_password;
    QHBoxLayout* hbox1 ;
    QHBoxLayout* hbox2 ;
    QHBoxLayout* hbox3;
    QVBoxLayout* vbox;
    void paintEvent(QPaintEvent*);



    void login_slot();
    void exit_slot();
    void password_slot(bool x);
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
