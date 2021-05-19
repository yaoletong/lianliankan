#include "rulewindow.h"
#include "ui_rulewindow.h"

RuleWindow::RuleWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RuleWindow)
{
    ui->setupUi(this);
}

RuleWindow::~RuleWindow()
{
    delete ui;
}
