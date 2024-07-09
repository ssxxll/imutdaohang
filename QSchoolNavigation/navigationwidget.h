#ifndef NAVIGATIONWIDGET_H
#define NAVIGATIONWIDGET_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class NavigationWidget;
}

class NavigationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NavigationWidget(QWidget *parent = nullptr);
    ~NavigationWidget();

private slots:
    void on_pushButton_clicked();//查询
    void acceptListClear();//接收清除
    void acceptListAdd(QString);//接收结果
    void acceptMapCorePl(QStringList);//接收地图
    void acceptMinPath(QString);//最短路径


private:
    Ui::NavigationWidget *ui;

};

#endif // NAVIGATIONWIDGET_H
