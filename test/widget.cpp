#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <bus.h>
#include <QString>
#include <string.h>
#include "dijk.h"
#include "paint.h"
using namespace std;

bus Bus[1001];
int cnt;
typedef pair<int,int> P;
P Dnum[2001];
void Widget::openfile()
{
        connect(ui->pushButton,&QPushButton::clicked,[=](){

        QString path=QFileDialog::getOpenFileName(this,"打开文件","C:\\Users\\23960\\Desktop");
        ui->lineEdit->setText(path);

        QFile file(path);

        file.open(QIODevice::ReadOnly);

        QByteArray array;
        while(!file.atEnd())
        {
            array=file.readLine();
            if(!array.toInt())break;
            Bus[++cnt].busNum=array.toInt();
            qDebug()<<Bus[cnt].busNum;
            array=file.readLine();
            Bus[cnt].sNum=array.toInt();

            for(int i=1;i<=Bus[cnt].sNum;i++)
            {
                array=file.readLine();
                int name=array.toInt();
                Bus[cnt].station[i].name=name;
                stationBus[name].push_back({cnt,i});
                array=file.readLine();
                Bus[cnt].station[i].x=array.toInt();
                Dnum[name].first=array.toInt();
                array=file.readLine();
                Bus[cnt].station[i].y=array.toInt();
                Dnum[name].second=array.toInt();
            }

            array=file.readLine();
            Bus[cnt].cost=array.toInt();
            array=file.readLine();
            Bus[cnt].time=array.toInt();
            array=file.readLine();
            Bus[cnt].speed=array.toInt();
            array=file.readLine();
        }
    });
}
void Widget::getLine()
{
    ui->textEdit_3->clear();
    ui->textEdit_3->insertPlainText("一共有"+QString::number(cnt)+"个路线\n");
    for(int i=1;i<=cnt;i++)
    {
       ui->textEdit_3->insertPlainText(QString::number(i)+"号路线：\n");
       for(int j=1;j<=Bus[i].sNum;j++)
       {
           ui->textEdit_3->insertPlainText(QString::number(Bus[i].station[j].name)+"站台("+QString::number(Bus[i].station[j].x)+","+QString::number(Bus[i].station[j].y)+")");
           if(j!=Bus[i].sNum)ui->textEdit_3->insertPlainText("->");
           else ui->textEdit_3->insertPlainText(";\n");
       }
       ui->textEdit_3->insertPlainText("车票花费："+QString::number(Bus[i].cost)+"元\n");
       ui->textEdit_3->insertPlainText("平均等待时间："+QString::number(Bus[i].time)+"分钟\n");
       ui->textEdit_3->insertPlainText("车速："+QString::number(Bus[i].speed)+"单位距离/分钟\n\n");
    }
}
void Widget::getStation()
{
    ui->textEdit_4->clear();
    ui->textEdit_4->insertPlainText("一共有"+QString::number(dnum)+"个站台\n");
    for(int i=1;i<=dnum;i++)
    {
        ui->textEdit_4->insertPlainText(QString::number(i)+"站台("+QString::number(Dnum[i].first)+","+QString::number(Dnum[i].second)+"):\n");
        for(int j=0;j<stationBus[i].size();j++)
        {
            int busname=stationBus[i][j].first;
            ui->textEdit_4->insertPlainText("可以从"+QString::number(busname)+"号线路上车，平均等待"+QString::number(Bus[busname].time)+"分钟\n");
        }
        ui->textEdit_4->insertPlainText("\n");
    }
}
Widget::Widget(QWidget *parent): QWidget(parent),ui(new Ui::Widget)
{
    ui->setupUi(this);
    openfile();

}


Widget::~Widget()
{
    delete ui;
}

void Widget::dfs(int sx,int sy,Path pre[],vector<Path> &path)
{
    if(sy==sx)
        return;
    Widget::dfs(sx,pre[sy].fa,pre,path);
    path.push_back({sy,pre[sy].num});
}

void Widget::find(vector<Path> path,int sx,int sy)
{
    ui->textEdit_2->clear();
    ui->textEdit_2->insertPlainText("从起始站台"+QString::number(sx)+"开始\n");
    ui->textEdit_2->insertPlainText("线路"+QString::number(path[0].num)+":站台"+QString::number(sx));
    for(int i=0;i<path.size();i++)
    {
        if(i!=0&&path[i].num!=path[i-1].num)
            ui->textEdit_2->insertPlainText(";\n换乘线路"+QString::number(path[i].num)+":站台"+QString::number(path[i-1].fa)+"->站台"+QString::number(path[i].fa));
        else
            ui->textEdit_2->insertPlainText("->站台"+QString::number(path[i].fa));
    }
}
void Widget::on_pushButton_2_clicked()
{
    bus::buildG(cnt,Bus,Dnum);
    ui->graphicsView->print(cnt,Bus,Dnum,dnum);
    Widget::getLine();
    Widget::getStation();
}
void Widget::work(int op)
{
    Path pre[2001];

    for(int i=0;i<=2000;i++)pre[i].fa=0;
    int sx=ui->lineEdit_2->text().toInt();
    int sy=ui->lineEdit_3->text().toInt();

    bus::dijk(sx,sy,pre,op);
    if(dis[sy]>=1e4)
    {
        ui->textEdit_2->clear();
        ui->textEdit_2->insertPlainText("没有路线可以到达");
        return;
    }
    ui->textEdit->setText(QString::number(dis[sy]));
    vector<Path> path;
    Widget::dfs(sx,sy,pre,path);
    Widget::find(path,sx,sy);
    ui->graphicsView->print2(cnt,Bus,Dnum,dnum,sx,sy,path);
    if(op==1)ui->textEdit_2->insertPlainText("\n最短时间是"+QString::number(dis[sy])+"分钟");
    if(op==2)ui->textEdit_2->insertPlainText("\n最小花费是"+QString::number(dis[sy])+"元");
    if(op==3)ui->textEdit_2->insertPlainText("\n最短时间是"+QString::number(dis[sy])+"分钟");
}
void Widget::on_pushButton_3_clicked()
{
   Widget::work(1);
}
void Widget::on_pushButton_4_clicked()
{
   Widget::work(2);
}
void Widget::on_pushButton_5_clicked()
{
   Widget::work(3);
}
void Widget::on_getNewLine_clicked()
{
    qDebug()<<"xxxxxxx"<<dnum;
    Bus[++cnt].busNum=cnt;
    Bus[cnt].sNum=ui->newLineNum->text().toInt();
    QStringList text=ui->Station_xy->toPlainText().split("\n");
    for(int i=1;i<=Bus[cnt].sNum;i++)
    {
        int x=text[2*(i-1)].toInt();
        int y=text[2*(i-1)+1].toInt();
        if(x==0)
        {
            Bus[cnt].station[i].name=y;
            stationBus[Bus[cnt].station[i].name].push_back({cnt,i});
            Bus[cnt].station[i].x=Dnum[y].first;
            Bus[cnt].station[i].y=Dnum[y].second;
        }
        else
        {
            dnum++;
            Bus[cnt].station[i].name=dnum;
            stationBus[dnum].push_back({cnt,i});
            Bus[cnt].station[i].x=x;
            Dnum[dnum].first=x;
            Bus[cnt].station[i].y=y;
            Dnum[dnum].second=y;
        }
    }
    Bus[cnt].cost=ui->newLineCost->text().toDouble();
    Bus[cnt].time=ui->newLineWait->text().toDouble();
    Bus[cnt].speed=ui->newLineSpeed->text().toDouble();
    bus::buildG(cnt,Bus,Dnum);
    ui->graphicsView->print(cnt,Bus,Dnum,dnum);
    Widget::getLine();
    Widget::getStation();
}

