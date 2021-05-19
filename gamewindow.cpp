#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
}

GameWindow::GameWindow(int diff) :
    QMainWindow(),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    initGame(diff);
}

GameWindow::~GameWindow()
{
    delete ui;
}

void sleep(unsigned int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

bool GameWindow::horizon(int x1, int y1, int x2, int y2)
{
    if (x1 == x2 && y1 == y2)
        return false;

    if (x1 != x2)
        return false;

    int start_y = std::min(y1, y2);
    int end_y = std::max(y1, y2);

    for (int j = start_y+1; j < end_y; j++)
        if (patterns[x1][j])
            return false;

    qDebug() << "hor";
    return true;
}

bool GameWindow::vertical(int x1, int y1, int x2, int y2)
{
    if (x1 == x2 && y1 == y2)
        return false;

    if (y1 != y2)
        return false;

    int start_x = std::min(x1, x2);
    int end_x = std::max(x1, x2);

    for (int i = start_x+1; i < end_x; i++)
        if (patterns[i][y1])
            return false;

    qDebug() << "ver";
    return true;
}

bool GameWindow::turn_once(int x1, int y1, int x2, int y2)
{
    if (x1 == x2 && y1 == y2)
        return false;

    int c_x = x1, c_y = y2;
    int d_x = x2, d_y = y1;

    int ret = false;

    if (!patterns[c_x][c_y])
        ret |= horizon(x1, y1, c_x, c_y) && vertical(c_x, c_y, x2, y2);

    if (!patterns[d_x][d_y])
        ret |= horizon(x1, y1, d_x, d_y) && vertical(d_x, d_y, x2, y2);

    if (ret)
        return true;

    return false;
}

bool GameWindow::turn_twice(int x1, int y1, int x2, int y2)
{
    if (x1 == x2 && y1 == y2)
        return false;

    for (int i = 0; i <= ROW; i++)
    {
        for (int j = 0; j <= COLUMN; j++)
        {
            if (i != x1 && i != x2 && j != y1 && j != y2)
                continue;

            if ((i == x1 && j == y1) || (i == x2 && j == y2))
                continue;

            if (patterns[i][j])
                continue;

            if (turn_once(x1, y1, i, j) && (horizon(i, j, x2, y2) || vertical(i, j, x2, y2)))
                return true;
            if (turn_once(i, j, x2, y2) && (horizon(x1, y1, i, j) || vertical(x1, y1, i, j)))
                return true;
        }
    }

    return false;
}

void GameWindow::remove(int x1, int y1, int x2, int y2)
{
    int ret = false;

    qDebug() << x1 << "," << y1 << " " << x2 << "," << y2;
    ret = horizon(x1, y1, x2, y2);
    if (ret)
    {
        qDebug() << "horizon";
        mahjongs[x1][y1]->setVisible(false);
        patterns[x1][y1] = 0;
        mahjongs[x2][y2]->setVisible(false);
        patterns[x2][y2] = 0;
        return;
    }
    ret = vertical(x1, y1, x2, y2);
    if (ret)
    {
        qDebug() << "vertical";
        mahjongs[x1][y1]->setVisible(false);
        patterns[x1][y1] = 0;
        mahjongs[x2][y2]->setVisible(false);
        patterns[x2][y2] = 0;
        return;
    }
    ret = turn_once(x1, y1, x2, y2);
    if (ret)
    {
        qDebug() << "turn_once";
        mahjongs[x1][y1]->setVisible(false);
        patterns[x1][y1] = 0;
        mahjongs[x2][y2]->setVisible(false);
        patterns[x2][y2] = 0;
        return;
    }
    ret = turn_twice(x1, y1, x2, y2);
    if (ret)
    {
        qDebug() << "turn_twice";
        mahjongs[x1][y1]->setVisible(false);
        patterns[x1][y1] = 0;
        mahjongs[x2][y2]->setVisible(false);
        patterns[x2][y2] = 0;
        return;
    }
}

void GameWindow::upset(int *a, int size)
{
    int i, j, T=1000, tmp;
    srand(unsigned(time(NULL)));
    while(T--)
    {
        i = rand() % size;
        j = rand() % size;
        tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }

}

void GameWindow::initGame(int diff)
{
    switch(diff)
    {
    //入门级
    case 1:
    {
        ROW = 4;
        COLUMN = 6;
        int record[ROW*COLUMN/2];
        patternType = 6;
        selectedQuantity = 0;
        memset(patterns,0,sizeof(patterns));
        memset(selectedMahjongs,0,sizeof (selectedMahjongs));

        for(int i = 1; i <= ROW/2; i++)
        {
            for(int j = 1; j <= COLUMN; j++)
            {
                mahjongs[i][j] = new QLabel(this);
                //位置计算
                mahjongs[i][j]->setGeometry(BORDERWIDTHONE + MJWIDTH * (j-1),
                                            BORDERHEIGHTONE + MJLENGTH * (i-1),
                                            MJWIDTH, MJLENGTH);

                //TODO 随机生成初始连连看 ////////////////////
                /////////////////////////////////////////
                int type = rand() % patternType + 1;

                switch(type)
                {
                case 1:
                    mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/yibing.png"));
                    break;
                case 2:
                    mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/sanbing.png"));
                    break;
                case 3:
                    mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/liubing.png"));
                    break;
                case 4:
                    mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/jiubing.png"));
                    break;
                case 5:
                    mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/hongzhong.png"));
                    break;
                case 6:
                    mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/yaoji.png"));
                    break;
                }
                patterns[i][j] = type;
                record[(i-1)*COLUMN + j-1] = type;
                //////////////////////////////////////////


                mahjongs[i][j]->installEventFilter(this);
                mahjongs[i][j]->setAlignment(Qt::AlignCenter);
            }
        }

        upset(record, ROW*COLUMN/2);

        for(int i = ROW/2+1; i <= ROW; i++)
        {
            for(int j = 1; j <= COLUMN; j++)
            {
                mahjongs[i][j] = new QLabel(this);
                //位置计算
                mahjongs[i][j]->setGeometry(BORDERWIDTHONE + MJWIDTH * (j-1),
                                            BORDERHEIGHTONE + MJLENGTH * (i-1),
                                            MJWIDTH, MJLENGTH);

                switch(record[(i-ROW/2-1)*COLUMN + j-1])
                {
                case 1:
                    mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/yibing.png"));
                    break;
                case 2:
                    mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/sanbing.png"));
                    break;
                case 3:
                    mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/liubing.png"));
                    break;
                case 4:
                    mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/jiubing.png"));
                    break;
                case 5:
                    mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/hongzhong.png"));
                    break;
                case 6:
                    mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/yaoji.png"));
                    break;
                }
                patterns[i][j] = record[(i-ROW/2-1)*COLUMN + j-1];
                //////////////////////////////////////////


                mahjongs[i][j]->installEventFilter(this);
                mahjongs[i][j]->setAlignment(Qt::AlignCenter);
            }
        }
        break;
    }
        //低级
    case 2:
    {
        ROW = 6;
        COLUMN = 9;
        patternType =  9;

        memset(patterns,0,sizeof(patterns));
        memset(selectedMahjongs,0,sizeof (selectedMahjongs));


        break;
    }
        //中级
    case 3:
    {
        ROW = 8;
        COLUMN = 12;
        patternType = 18;

        memset(patterns,0,sizeof(patterns));
        memset(selectedMahjongs,0,sizeof (selectedMahjongs));


        break;
    }

        //高级
    case 4:
    {
        ROW = 10;
        COLUMN = 15;
        patternType = 6;

        memset(patterns,0,sizeof(patterns));
        memset(selectedMahjongs,0,sizeof(selectedMahjongs));


        break;
    }
    }
}

bool GameWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = reinterpret_cast<QMouseEvent*>(event);
        //int i = -1;
        if(mouseEvent->button() == Qt::LeftButton)
        {
            for(int i = 1; i <= ROW; i++)
            {
                for(int j = 1; j <= COLUMN; j++)
                {
                    if(obj == mahjongs[i][j])
                    {
                        selectedQuantity++;
                        mahjongs[i][j]->setStyleSheet("QLabel{border:4px solid rgb(255, 255, 9);}");
                        selectedMahjongs[selectedQuantity-1][0] = i;
                        selectedMahjongs[selectedQuantity-1][1] = j;

                        //TODO判断是否消除
                        //若消除 连线（UI）--> 与算法、路径有关
                        if(selectedQuantity == 2)
                        {
                            selectedQuantity = 0;
                            mahjongs[selectedMahjongs[0][0]][selectedMahjongs[0][1]]->setStyleSheet("");
                            mahjongs[selectedMahjongs[1][0]][selectedMahjongs[1][1]]->setStyleSheet("");
                            if(patterns[selectedMahjongs[1][0]][selectedMahjongs[1][1]] == patterns[selectedMahjongs[0][0]][selectedMahjongs[0][1]])
                            {
                                remove(selectedMahjongs[0][0],selectedMahjongs[0][1],selectedMahjongs[1][0],selectedMahjongs[1][1]);
                            }
                            memset(selectedMahjongs,0,sizeof(selectedMahjongs));
                        }
                        break;
                    }
                }
            }

            return true;
        }
    }
    return false;


}
