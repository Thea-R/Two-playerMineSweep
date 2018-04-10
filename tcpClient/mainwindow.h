#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <ctime>

namespace Ui {
    class MainWindow;
}

struct Mine
{
    bool is_mine, is_opened, flag;//是否是雷、被打开、被插旗
    int cnt;//周围雷数
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

protected:
    int R, G, B;//画笔颜色
    int col, row, tot, rest, wid, het;//扫雷棋盘行列数、雷数、剩余区域数、尺寸
    int siz, bod, ico_width, ico_height;//每一格大小、边缘大小、icon尺寸
    int up, down, left, right;//棋盘边缘坐标
    int cnts, cntc;//服务器端、客户端操作数
    int flags, flagc, real_flags, real_flagc;//服务器端、客户端插旗数，服务器端、客户端真正插旗数
    int cx, cy, opt, st;//每次点击坐标、绘制类型、游戏状态(0未开始、1游戏中、2失败、3胜利、4扫完区域）
    bool lclick, rclick;//每次操作的情况
    Mine mmp[50][50];//每个雷的信息

    QTcpSocket* socket;
    bool Connect;

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void setModel(int _col, int _row, int _tot);
    void openMine();
    void getId(int x, int y);
    void endGame();
    void showFlag();
    void showMine();
    void showDigit();
    void showZero();
    void sendMessage();

private slots:
    void on_conBtn_clicked();
    void readMessage();
    void on_startBtn_clicked();
};

#endif // MAINWINDOW_H
