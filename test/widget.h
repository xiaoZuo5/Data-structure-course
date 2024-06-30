#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "bus.h"
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void openfile();
    void dfs(int sx,int sy,Path pre[],vector<Path> &path);
    void find(vector<Path> path,int sx,int sy);
    void work(int op);
    void getLine();
    void getStation();
private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_getNewLine_clicked();

private:
    Ui::Widget *ui;
};
#endif
