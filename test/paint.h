#ifndef PAINT_H
#define PAINT_H
#include<QGraphicsView>
#include<QGraphicsLineItem>
#include"bus.h"
class paint:public QGraphicsView
{
public:
    explicit paint(QWidget *parent = nullptr);
public :
    void print(int cnt,bus Bus[],pair<int,int> Dnum[],int dunm);
    void print2(int cnt,bus Bus[],pair<int,int> Dnum[],int dunm,int sx,int sy,vector<Path> path);
};

#endif
