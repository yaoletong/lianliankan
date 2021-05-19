#ifndef INITWINDOW_H
#define INITWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "gamewindow.h"
#include "choosewindow.h"
#include "rulewindow.h"

namespace Ui {
class initWindow;
}

class initWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit initWindow(QWidget *parent = nullptr);
    ~initWindow();

private:
    Ui::initWindow *ui;

protected:
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // INITWINDOW_H
