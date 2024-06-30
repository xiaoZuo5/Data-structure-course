#include "paint.h"
using namespace std;
paint::paint(QWidget *parent) : QGraphicsView(parent)
{

}
void paint::print(int cnt,bus Bus[],pair<int,int> Dnum[],int dnum)
{
      QGraphicsScene *mm = new QGraphicsScene;
      QPen pen;

      pen.setWidth(5);
      for(int i=1;i<=cnt;i++)
      {
          pen.setColor(QColor(rand() % 256, rand() % 256, rand() % 256));
          for(int j=2;j<=Bus[i].sNum;j++)
          {
              pen.setWidth(2);
              int u=Bus[i].station[j-1].name;
              int v=Bus[i].station[j].name;
              QGraphicsLineItem *line = new QGraphicsLineItem(Dnum[u].first*5, Dnum[u].second*5,Dnum[v].first*5, Dnum[v].second*5);
              line->setPen(pen);
              line->setToolTip("线路 " + QString::number(Bus[i].busNum));
              mm->addItem(line);
          }
      }

      pen.setColor(QColor(rand()%256, rand()%256, rand()%256));
      pen.setWidth(15);
      for(int i=1;i<=dnum;i++)
      {
          QGraphicsEllipseItem *cir = new QGraphicsEllipseItem(Dnum[i].first*5, Dnum[i].second*5, 15, 15);
          cir->setPen(pen);
          QString tip = "站点：" + QString::number(i);
          cir->setToolTip(tip);
          mm->addItem(cir);

          QGraphicsTextItem *text = new QGraphicsTextItem(QString::number(i));
          text->setPos(Dnum[i].first*5,Dnum[i].second*5);
          mm->addItem(text);
      }
      setScene(mm);
}

void paint::print2(int cnt,bus Bus[],pair<int,int> Dnum[],int dnum,int sx,int sy,vector<Path> path)
{
    QGraphicsScene *mm = new QGraphicsScene;
    QPen pen;
    pen.setWidth(3);
    pen.setStyle(Qt::DotLine);
     for(int i=1;i<=cnt;i++)
      {
          pen.setColor(QColor(rand() % 256, rand() % 256, rand() % 256));
          for(int j=2;j<=Bus[i].sNum;j++)
          {
              int u=Bus[i].station[j-1].name;
              int v=Bus[i].station[j].name;
              QGraphicsLineItem *line = new QGraphicsLineItem(Dnum[u].first*5, Dnum[u].second*5,Dnum[v].first*5, Dnum[v].second*5);
              line->setPen(pen);
              line->setToolTip("线路 " + QString::number(Bus[i].busNum));
              mm->addItem(line);
          }
      }


      pen.setColor(QColor(rand() % 256, rand() % 256, rand() % 256));
      pen.setWidth(5);
      pen.setStyle(Qt::SolidLine);
      QGraphicsLineItem *line =new QGraphicsLineItem(Dnum[sx].first*5,Dnum[sx].second*5,Dnum[path[0].fa].first*5,Dnum[path[0].fa].second*5);
      line->setPen(pen);
      mm->addItem(line);
      for(int i=1;i<path.size();i++)
      {
          if(path[i].num!=path[i-1].num)
          {
              pen.setColor(QColor(rand() % 256, rand() % 256, rand() % 256));
              pen.setWidth(4);
              pen.setStyle(Qt::SolidLine);
              QGraphicsLineItem *line =new QGraphicsLineItem(Dnum[path[i-1].fa].first*5,Dnum[path[i-1].fa].second*5,Dnum[path[i].fa].first*5,Dnum[path[i].fa].second*5);
              line->setPen(pen);
              mm->addItem(line);
          }
          else
          {
              QGraphicsLineItem *line =new QGraphicsLineItem(Dnum[path[i-1].fa].first*5,Dnum[path[i-1].fa].second*5,Dnum[path[i].fa].first*5,Dnum[path[i].fa].second*5);
              line->setPen(pen);
              mm->addItem(line);
          }
      }

      pen.setColor(QColor(rand()%256, rand()%256, rand()%256));
      pen.setWidth(15);
      for(int i=1;i<=dnum;i++)
      {
          QGraphicsEllipseItem *cir = new QGraphicsEllipseItem(Dnum[i].first*5, Dnum[i].second*5, 15, 15);
          cir->setPen(pen);
          QString tip = "站点：" + QString::number(i);
          cir->setToolTip(tip);
          mm->addItem(cir);

          QGraphicsTextItem *text = new QGraphicsTextItem(QString::number(i));
          text->setPos(Dnum[i].first*5,Dnum[i].second*5);
          mm->addItem(text);
      }

      setScene(mm);
}


