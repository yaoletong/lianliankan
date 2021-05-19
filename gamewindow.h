#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
#include <QTime>

#define MJWIDTH 82
#define MJLENGTH 128
#define BORDERWIDTHONE 550
#define BORDERHEIGHTONE 230
#define BORDERWIDTHFOUR 180
#define BORDERHEIGHTFOUR 200
#define MAXSIZE 10

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    GameWindow(int);
    ~GameWindow();
    void initGame(int);

    void setRow(int);
    void setColumn(int);
    bool horizon(int x1, int y1, int x2, int y2);
    bool vertical(int x1, int y1, int x2, int y2);
    bool turn_once(int x1, int y1, int x2, int y2);
    bool turn_twice(int x1, int y1, int x2, int y2);
    void remove(int x1, int y1, int x2, int y2);
    void upset(int *a, int size);

private:
    int ROW;
    int COLUMN;
    int patternType;
    int selectedQuantity;
    int init;

    QLabel *mahjongs[12][17];
    int patterns[12][17];
    int selectedMahjongs[2][2];

    Ui::GameWindow *ui;

protected:
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // GAMEWINDOW_H
