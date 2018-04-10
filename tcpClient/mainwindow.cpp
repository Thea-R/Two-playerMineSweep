#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <QPainter>
#include <QMessageBox>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QDir>
#include <queue>
using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);//初始化窗口
    move(200, 100);//设置左上角坐标
    setModel(30, 16, 99);//设置棋盘
    setWindowTitle("扫雷Client");//设置窗口标题
    setFixedSize(wid, het);//设置窗口大小
    ui->sLabel->hide();
    ui->cLabel->hide();
    ui->startBtn->hide();

    Connect=false;
    st=opt=0;//初始化数据
    cnts=flags=real_flags=0;
    cntc=flagc=real_flagc=0;
    cx=cy=0;
    rest=row*col;
    memset(mmp, 0, sizeof mmp);
    srand((unsigned int)time(0));
    for (int i = 1; i <= tot; )
    {
        int x = rand() % col, y = rand() % row;
        if (!mmp[x][y].is_mine) mmp[x][y].is_mine = true, i++;
    }
    int dd[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };
    for (int i = 0; i < col; i++)
        for (int j = 0; j < row; j++) if(!mmp[i][j].is_mine)
            for (int k = 0; k < 8; k++)
            {
                int x = i + dd[k][0], y = j + dd[k][1];
                if (x >= 0 && x < col && y >= 0 && y < row && mmp[x][y].is_mine)	++mmp[i][j].cnt;
            }
}

MainWindow::~MainWindow()
{
    if(Connect)
    {
        socket->disconnectFromHost();
        qDebug()<<"closed";
    }
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;
    QPixmap pix;

    if(st==0)
    {
        painter.setBrush(QBrush(QColor(R, G, B)));//绘制背景
        painter.drawRect(0, 0, wid, het);

        pen.setWidth(3);//绘制棋盘
        pen.setColor(QColor(232, 232, 232));
        painter.setPen(pen);
        for(int i=0; i<=col; i++)   painter.drawLine(QPointF(left+i*siz, up), QPointF(left+i*siz, up+row*siz));
        for(int j=0; j<=row; j++)   painter.drawLine(QPointF(left, up+j*siz), QPointF(left+col*siz, up+j*siz));

        pen.setWidth(2);
        pen.setColor(QColor(28, 28, 28));
        painter.setPen(pen);
        for(int i=0; i<=col; i++)   painter.drawLine(QPointF(left+i*siz, up), QPointF(left+i*siz, up+row*siz));
        for(int j=0; j<=row; j++)   painter.drawLine(QPointF(left, up+j*siz), QPointF(left+col*siz, up+j*siz));

        pix.load("../Resources/14.bmp");//绘制icon
        painter.drawPixmap((wid-ico_height)/2, bod, ico_height, ico_height, pix);
    }
    else
    {
        painter.setBrush(QBrush(QColor(R, G, B)));//绘制背景
        painter.drawRect(0, 0, wid, het);

        pen.setWidth(3);//绘制棋盘
        pen.setColor(QColor(232, 232, 232));
        painter.setPen(pen);
        for(int i=0; i<=col; i++)   painter.drawLine(QPointF(left+i*siz, up), QPointF(left+i*siz, up+row*siz));
        for(int j=0; j<=row; j++)   painter.drawLine(QPointF(left, up+j*siz), QPointF(left+col*siz, up+j*siz));

        pen.setWidth(2);
        pen.setColor(QColor(28, 28, 28));
        painter.setPen(pen);
        for(int i=0; i<=col; i++)   painter.drawLine(QPointF(left+i*siz, up), QPointF(left+i*siz, up+row*siz));
        for(int j=0; j<=row; j++)   painter.drawLine(QPointF(left, up+j*siz), QPointF(left+col*siz, up+j*siz));

        pix.load("../Resources/14.bmp");//绘制icon
        painter.drawPixmap((wid-ico_height)/2, bod, ico_height, ico_height, pix);

        if(st>=2)
        {
            for (int i = 0; i < col; i++)
                for (int j = 0; j < row; j++)
                {
                    cx=i, cy=j;
                    if(mmp[i][j].flag)
                    {
                        pix.load("../Resources/10.bmp");//标记旗帜
                        painter.drawPixmap(left + cx*siz + 2, up + cy*siz + 2, siz-3, siz-3, pix);
                        if(!mmp[i][j].is_mine)
                        {
                            pen.setWidth(2);//wrong
                            pen.setColor(QColor(205, 0, 0));
                            painter.setPen(pen);
                            painter.drawLine(cx*siz + left + 2, cy*siz + up+2, cx*siz + siz + left, cy*siz + siz + up);
                            painter.drawLine(cx*siz + siz + left, cy*siz + up + 2, cx*siz + left + 2, cy*siz + siz + up);
                        }
                    }
                    else if(mmp[i][j].is_mine)
                    {
                        pix.load("../Resources/11.bmp");//标记雷
                        painter.drawPixmap(cx*siz + left + 2, cy*siz + up + 2, siz-3, siz-3, pix);
                    }
                    else if(mmp[i][j].cnt)
                    {
                        switch(mmp[i][j].cnt)
                        {
                        case 1: pix.load("../Resources/1.bmp");//点开1～9数字
                                painter.drawPixmap(left + cx*siz + 2, up + cy*siz + 2, siz-3, siz-3, pix);
                            break;
                        case 2: pix.load("../Resources/2.bmp");//点开1～9数字
                                painter.drawPixmap(left + cx*siz + 2, up + cy*siz + 2, siz-3, siz-3, pix);
                            break;
                        case 3: pix.load("../Resources/3.bmp");//点开1～9数字
                                painter.drawPixmap(left + cx*siz + 2, up + cy*siz + 2, siz-3, siz-3, pix);
                            break;
                        case 4: pix.load("../Resources/4.bmp");//点开1～9数字
                                painter.drawPixmap(left + cx*siz + 2, up + cy*siz + 2, siz-3, siz-3, pix);
                            break;
                        case 5: pix.load("../Resources/5.bmp");//点开1～9数字
                                painter.drawPixmap(left + cx*siz + 2, up + cy*siz + 2, siz-3, siz-3, pix);
                            break;
                        case 6: pix.load("../Resources/6.bmp");//点开1～9数字
                                painter.drawPixmap(left + cx*siz + 2, up + cy*siz + 2, siz-3, siz-3, pix);
                            break;
                        case 7: pix.load("../Resources/7.bmp");//点开1～9数字
                                painter.drawPixmap(left + cx*siz + 2, up + cy*siz + 2, siz-3, siz-3, pix);
                            break;
                        case 8: pix.load("../Resources/8.bmp");//点开1～9数字
                                painter.drawPixmap(left + cx*siz + 2, up + cy*siz + 2, siz-3, siz-3, pix);
                            break;
                        case 9: pix.load("../Resources/9.bmp");//点开1～9数字
                                painter.drawPixmap(left + cx*siz + 2, up + cy*siz + 2, siz-3, siz-3, pix);
                            break;
                        }
                    }
                    else
                    {
                        pen.setWidth(1);
                        pen.setColor(QColor(232, 232, 232));
                        painter.setPen(pen);
                        painter.setBrush(QBrush(QColor(255, 255, 255)));//点开空白
                        painter.drawRect(cx*siz + left + 2, cy*siz + up + 2, siz-3, siz-3);
                    }
                }
            switch(opt)
            {
                case 12: pix.load("../Resources/13.bmp");//win
                         painter.drawPixmap((wid-ico_height)/2, bod, ico_height, ico_height, pix);
                    break;
                case 13: pix.load("../Resources/12.bmp");//failed
                         painter.drawPixmap((wid-ico_height)/2, bod, ico_height, ico_height, pix);
                    break;
                case 14: pix.load("../Resources/13.bmp");//tie
                         painter.drawPixmap((wid-ico_height)/2, bod, ico_height, ico_height, pix);
                    break;
            }
        }
        else
        {
            for (int i = 0; i < col; i++)
                for (int j = 0; j < row; j++) if(mmp[i][j].is_opened)
                {
                    cx=i, cy=j;
                    if(mmp[i][j].flag)
                    {
                        pix.load("../Resources/10.bmp");//标记旗帜
                        painter.drawPixmap(left + cx*siz + 2, up + cy*siz + 2, siz-3, siz-3, pix);
                    }
                    else if(mmp[i][j].is_mine)
                    {
                        pix.load("../Resources/11.bmp");//标记雷
                        painter.drawPixmap(cx*siz + left + 2, cy*siz + up + 2, siz-3, siz-3, pix);
                    }
                    else if(mmp[i][j].cnt)
                    {
                        switch(mmp[i][j].cnt)
                        {
                        case 1: pix.load("../Resources/1.bmp");//点开1～9数字
                                painter.drawPixmap(left + cx*siz + 2, up + cy*siz + 2, siz-3, siz-3, pix);
                            break;
                        case 2: pix.load("../Resources/2.bmp");//点开1～9数字
                                painter.drawPixmap(left + cx*siz + 2, up + cy*siz + 2, siz-3, siz-3, pix);
                            break;
                        case 3: pix.load("../Resources/3.bmp");//点开1～9数字
                                painter.drawPixmap(left + cx*siz + 2, up + cy*siz + 2, siz-3, siz-3, pix);
                            break;
                        case 4: pix.load("../Resources/4.bmp");//点开1～9数字
                                painter.drawPixmap(left + cx*siz + 2, up + cy*siz + 2, siz-3, siz-3, pix);
                            break;
                        case 5: pix.load("../Resources/5.bmp");//点开1～9数字
                                painter.drawPixmap(left + cx*siz + 2, up + cy*siz + 2, siz-3, siz-3, pix);
                            break;
                        case 6: pix.load("../Resources/6.bmp");//点开1～9数字
                                painter.drawPixmap(left + cx*siz + 2, up + cy*siz + 2, siz-3, siz-3, pix);
                            break;
                        case 7: pix.load("../Resources/7.bmp");//点开1～9数字
                                painter.drawPixmap(left + cx*siz + 2, up + cy*siz + 2, siz-3, siz-3, pix);
                            break;
                        case 8: pix.load("../Resources/8.bmp");//点开1～9数字
                                painter.drawPixmap(left + cx*siz + 2, up + cy*siz + 2, siz-3, siz-3, pix);
                            break;
                        case 9: pix.load("../Resources/9.bmp");//点开1～9数字
                                painter.drawPixmap(left + cx*siz + 2, up + cy*siz + 2, siz-3, siz-3, pix);
                            break;
                        }
                    }
                    else
                    {
                        pen.setWidth(1);
                        pen.setColor(QColor(232, 232, 232));
                        painter.setPen(pen);
                        painter.setBrush(QBrush(QColor(255, 255, 255)));//点开空白
                        painter.drawRect(cx*siz + left + 2, cy*siz + up + 2, siz-3, siz-3);
                    }
                }
        }
    }
    return ;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<cnts<<' '<<cntc<<endl;
    if(st!=1 || cnts!=cntc)    return ;

    int mx=event->x(), my=event->y();
    if(event->button() == Qt::LeftButton)
    {
        if (mx >= left && mx <= left + col * siz && my >= up && my <= up + row * siz)
        {
            bool flag=true;
            if(flag) for(int i=0; i<=col; i++) if(mx==left+i*siz || mx==left+i*siz+1)   flag=false;
            if(flag) for(int j=0; j<=row; j++) if(my==up+j*siz || my==up+j*siz+1)    flag=false;
            if(flag) getId(mx, my);
            if(flag && !mmp[cx][cy].is_opened)
            {
                openMine();
                lclick=true, rclick=false;;
                sendMessage();
                if(st>1)    endGame();
                cntc++;
                ui->cLabel->hide();
                ui->sLabel->show();
            }
        }
    }
    else if(event->button() == Qt::RightButton)
    {
        if (mx >= left && mx <= left + col * siz && my >= up && my <= up + row * siz)
        {
            bool flag=true;
            if(flag) for(int i=0; i<=col; i++) if(mx==left+i*siz || mx==left+i*siz+1)   flag=false;
            if(flag) for(int j=0; j<=row; j++) if(my==up+j*siz || my==up+j*siz+1)    flag=false;
            if(flag) getId(mx, my);
            if(flag && !mmp[cx][cy].is_opened)
            {
                showFlag();
                rclick=true, lclick=false;
                sendMessage();
                if(st>1)    endGame();
                cntc++;
                ui->cLabel->hide();
                ui->sLabel->show();
            }
        }
    }
    return ;
}

void MainWindow::on_conBtn_clicked()
{
    socket = new QTcpSocket();
    socket->connectToHost(ui->ipLine->text(), ui->portLine->text().toInt());
    if(!socket->waitForConnected(30000))
    {
        qDebug() << "Connection failed!";
        QMessageBox::information(this, QString::fromLocal8Bit("Connect Failed!"),QString::fromLocal8Bit("Connect Failed!"));
        close();
        return;
    }
    Connect=true;
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::readMessage);

    ui->ipLabel->hide();
    ui->ipLine->hide();
    ui->portLabel->hide();
    ui->portLine->hide();
    ui->conBtn->hide();
    ui->cLabel->show();

    ui->startBtn->show();
    return ;
}

void MainWindow::sendMessage()
{
    string dat;
    if(st==0)
    {
        dat="p";
        for (int i = 0; i < col; i++)
            for (int j = 0; j < row; j++)
            {
                char c=(int)mmp[i][j].is_mine+'0';
                dat+=c;
            }
    }
    else
    {
        if(lclick)  dat="l,";
        else dat="r,";

        for(int tx=cx; tx; tx/=10)
        {
            char c=tx%10+'0';
            dat+=c;
        }
        if(!cx) dat+="0";

        dat+=",";
        for(int ty=cy; ty; ty/=10)
        {
            char c=ty%10+'0';
            dat+=c;
        }
        if(!cy) dat+="0";
    }

    QString s=QString::fromStdString(dat);
    socket->write(s.toLatin1());
    socket->flush();

    qDebug()<<"send: "<<s<<" cx="<<cx<<" cy="<<cy;
    return ;
}

void MainWindow::readMessage()
{
    qDebug()<<"into read";
    QByteArray buffer=socket->readAll();
    char *s=buffer.data();
    qDebug()<<"s=<"<<s<<">";

    int i=0, len=strlen(s), x=0, y=0, tmp=1;
    while(i>=len || s[i]<'0' || s[i]>'9')   i++;
    while(i<len && s[i]>='0'&&s[i]<='9')   x=x+(s[i++]-'0')*tmp, tmp*=10;

    tmp=1;
    while(i>=len || s[i]<'0' || s[i]>'9')   i++;
    while(i<len && s[i]>='0'&&s[i]<='9')   y=y+(s[i++]-'0')*tmp, tmp*=10;
    qDebug()<<"x="<<x<<' '<<"y="<<y;

    cx=x, cy=y;
    if(s[0]=='l') openMine();
    else showFlag();

    if(st>1)    endGame();

    cnts++;

    ui->cLabel->show();
    ui->sLabel->hide();

    qDebug()<<"read: "<<cx<<' '<<cy;
    return ;
}

void MainWindow::setModel(int _col, int _row, int _tot)
{
    R = 112, G = 128, B = 180;
    col = _col, row = _row, tot = _tot, siz = 25;
    bod = 40, ico_width = 110, ico_height = 55;

    up = bod + ico_height + bod, down = left = right = bod;
    wid = left + col*siz + right, het = up + row*siz + down;
    return ;
}

void MainWindow::getId(int x, int y)
{
    cx = (x - left) / siz;
    cy = (y - up) / siz;
    return ;
}

void MainWindow::showMine()
{
    qDebug()<<"showMine "<<cx<<' '<<cy;
    if(cnts==cntc)  st=2;
    else st=3;
    mmp[cx][cy].is_opened=true;
    update();
    return ;
}

void MainWindow::showDigit()
{
    qDebug()<<"showDigit "<<cx<<' '<<cy;
    --rest;
    mmp[cx][cy].is_opened=true;
    if(!rest)   st=4;
    update();
    return ;
}

void MainWindow::showZero()
{
    qDebug()<<"showZero "<<cx<<' '<<cy;
    --rest;
    mmp[cx][cy].is_opened = true;

    int tx, ty, dd[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    queue<pair<int, int>> q;
    q.push(make_pair(cx, cy));
    while (!q.empty())
    {
        int x = q.front().first, y = q.front().second;
        q.pop();

        for (int k = 0; k < 8; k++)
        {
            tx = x + dd[k][0], ty = y + dd[k][1];
            if (tx < 0 || tx >= col || ty < 0 || ty >= row)	continue;
            if (mmp[tx][ty].is_opened || mmp[tx][ty].is_mine || mmp[tx][ty].flag)	continue;

            if (mmp[tx][ty].cnt)
            {
                --rest;
                mmp[tx][ty].is_opened=true;
            }
            else
            {
                --rest;
                mmp[tx][ty].is_opened=true;
                q.push(make_pair(tx, ty));
            }
        }
    }

    if(!rest)   st=4;
    update();
    return ;
}

void MainWindow::showFlag()
{
    qDebug()<<"showFlag "<<cx<<' '<<cy;
    --rest;
    mmp[cx][cy].is_opened=mmp[cx][cy].flag=true;
    if(!rest)   st=4;
    update();
    return ;
}

void MainWindow::openMine()
{
    if (mmp[cx][cy].is_mine)    showMine();
    else if (mmp[cx][cy].cnt)   showDigit();
    else showZero();
    return ;
}

void MainWindow::endGame()
{
    if(st==4)
    {
        if(real_flags>real_flagc)   st=3;
        else if(real_flags<real_flagc)  st=2;
        else if(flags-real_flags>flagc-real_flagc)  st=3;
        else if(flags-real_flags<flagc-real_flagc)  st=2;
        else
        {
            opt=14;
            update();
            QMessageBox::information(this, QString::fromLocal8Bit("Tie Match!"),QString::fromLocal8Bit("Tie Match!"));
            close();
        }
    }
    if(st==2)
    {
        opt=13;
        update();
        QMessageBox::information(this, QString::fromLocal8Bit("You Lost!"),QString::fromLocal8Bit("You Lost!"));
        close();
    }
    if(st==3)
    {
        opt=12;
        update();
        QMessageBox::information(this, QString::fromLocal8Bit("You Win!"),QString::fromLocal8Bit("You Win!"));
        close();
    }
    return ;
}

void MainWindow::on_startBtn_clicked()
{
    sendMessage();
    st=1;
    ui->startBtn->hide();
    return ;
}
