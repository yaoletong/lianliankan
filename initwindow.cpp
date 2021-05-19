#include "initwindow.h"
#include "ui_initwindow.h"


initWindow::initWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::initWindow)
{
    ui->setupUi(this);

    ui->label_begin->installEventFilter(this);
    ui->label_choosedifficulties->installEventFilter(this);
    ui->label_rule->installEventFilter(this);
}

initWindow::~initWindow()
{
    delete ui;
}

bool initWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->label_begin)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if(mouseEvent->button() == Qt::LeftButton)
            {
                //TODO 获取难度信息
                //switch语句

                GameWindow* g = new GameWindow(1);
                g->show();
                return true;
            }
        }
        else
        {
            return false;
        }

    }
    else if (obj == ui->label_choosedifficulties)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if(mouseEvent->button() == Qt::LeftButton)
            {
                ChooseWindow* c = new ChooseWindow();
                c->show();
                return true;
            }
        }
        else
        {
            return false;
        }

    }
    else if (obj == ui->label_rule)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if(mouseEvent->button() == Qt::LeftButton)
            {
                RuleWindow* r = new RuleWindow();
                r->show();
                return true;
            }
        }
        else
        {
            return false;
        }

    }
    //else
    //{
    // pass the event on to the parent class
    return QMainWindow::eventFilter(obj, event);
    //}
}
