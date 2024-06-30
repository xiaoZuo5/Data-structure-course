#ifndef DIJK_H
#define DIJK_H
#include<queue>
#include<algorithm>
#include<iostream>
#include "widget.h"
#include "bus.h"
#include <stack>
#define ll long long
#define min(x,y) (x)<(y)?(x):(y)
using namespace std;
const int MAX_N=1e3;
const int MAX_D=1e5;
int head[1001],k;
int dnum;
edge e[2001];
vector<pair<int,int>> stationBus[2001];
 void bus::add(int u,int v,double w,double m,int wait_w,int num)
{
    e[++k].to=v;
    e[k].busNum=num;
    e[k].w=w;
    e[k].m=m;
    e[k].wait_w=wait_w;
    e[k].next=head[u];
    head[u]=k;
}


 double bus::getdis(int x1,int y1,int x2,int y2)
{
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}


void bus::buildG(int cnt,bus Bus[],pair<int,int> Dnum[])
{
    for(int i=1;i<=cnt;i++)
    {
        for(int j=2;j<=Bus[i].sNum;j++)
        {
            double dis=bus::getdis(Bus[i].station[j-1].x,Bus[i].station[j-1].y,Bus[i].station[j].x,Bus[i].station[j].y);
            bus::add(Bus[i].station[j-1].name,Bus[i].station[j].name,dis/Bus[i].speed,Bus[i].cost,Bus[i].time,i);
        }
    }
    dnum=0;
    for(int i=1;!stationBus[i].empty();i++)dnum++;
}
double dis[MAX_N];
bool vis[MAX_N];
void bus::dijk(int sx,int sy,Path pre[],int op)
{
    for(int i=1;i<=2000;i++)pre[i].fa=0;
    fill(dis+1,dis+dnum+1,MAX_D);
    fill(vis+1,vis+dnum+1,0);
    priority_queue<pair<double,int>,vector< pair<double,int> >,greater<pair<double,int> > > q;
    dis[sx]=0;
    q.push({0,sx});
    while(q.size())
    {
        int now=q.top().second;
        q.pop();
        if(vis[now])continue;
        vis[now]=1;
        for(int i=head[now];i;i=e[i].next)
        {
            if(op==1)
            {
                if(dis[e[i].to]>dis[now]+e[i].w)
                {
                    dis[e[i].to]=dis[now]+e[i].w;       
                    pre[e[i].to].fa=now;
                    pre[e[i].to].num=e[i].busNum;
                }
            }
            if(op==2)
            {
                if(pre[now].num&&e[i].busNum==pre[now].num)
                {
                    dis[e[i].to]=dis[now];
                    pre[e[i].to].fa=now;
                    pre[e[i].to].num=e[i].busNum;

                }
                else if(dis[e[i].to]>dis[now]+e[i].m)
                {
                    dis[e[i].to]=dis[now]+e[i].m;
                    pre[e[i].to].fa=now;
                    pre[e[i].to].num=e[i].busNum;
                }
            }
            if(op==3)
            {
                if(pre[now].num&&e[i].busNum==pre[now].num)
                {
                    if(dis[e[i].to]>dis[now]+e[i].w)
                    {
                         dis[e[i].to]=dis[now]+e[i].w;
                         pre[e[i].to].fa=now;
                         pre[e[i].to].num=e[i].busNum;
                    }
                }
                else if(dis[e[i].to]>dis[now]+e[i].w+e[i].wait_w)
                {
                    dis[e[i].to]=dis[now]+e[i].w+e[i].wait_w;
                    pre[e[i].to].fa=now;
                    pre[e[i].to].num=e[i].busNum;
                }
            }
            q.push({dis[e[i].to],e[i].to});
        }
    }
    qDebug()<<dis[sy];
}
#endif
