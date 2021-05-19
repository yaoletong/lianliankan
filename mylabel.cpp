#include "mylabel.h"

MyLabel::MyLabel(QWidget* parent) :QLabel(parent)
{

}
MyLabel::~MyLabel()
{

}
void MyLabel::enterEvent(QEvent *e)
{
    if(this->objectName()=="label_begin")
    {
        setPixmap(QPixmap(":/new/prefix1/pic/newbegin.png"));
    }
    if(this->objectName()=="label_choosedifficulties")
    {
        setPixmap(QPixmap(":/new/prefix1/pic/newchoosedifficulties.png"));
    }
    if(this->objectName()=="label_rule")
    {
        setPixmap(QPixmap(":/new/prefix1/pic/newrule.png"));
    }

}
void MyLabel::leaveEvent(QEvent *e)
{
    if(this->objectName()=="label_begin")
    {
        setPixmap(QPixmap(":/new/prefix1/pic/begin.png"));
    }
    if(this->objectName()=="label_choosedifficulties")
    {
        setPixmap(QPixmap(":/new/prefix1/pic/choosedifficulties.png"));
    }
    if(this->objectName()=="label_rule")
    {
        setPixmap(QPixmap(":/new/prefix1/pic/rule.png"));
    }
}
