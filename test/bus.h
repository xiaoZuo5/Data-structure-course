#ifndef BUS_H
#define BUS_H
#include<QString>
#include<QColor>
using namespace std;

struct platfrom
{
    int name;
    int x,y;
};

struct edge
{
    int to,next;
    int busNum;
    double m;
    double w;
    double wait_w;
};

struct Path
{
    int fa=0;
    int num=0;
};


class bus
{
public:
    int busNum;
    platfrom station[1001];
    int sNum=0;
    double cost;
    double time;
    double speed;
    static void add(int u,int v,double w,double m,int wait_w,int num);
    static double getdis(int x1,int y1,int x2,int y2);
    static void buildG(int cnt,bus Bus[],pair<int,int> Dnum[]);
    static void dijk(int sx,int sy,Path pre[],int op);
};
#endif
