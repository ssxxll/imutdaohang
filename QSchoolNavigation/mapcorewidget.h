#ifndef MAPCOREWIDGET_H
#define MAPCOREWIDGET_H

#include <QWidget>
#include <cmath>
#include <QTimer>
#include <QMainWindow>
#include <fstream>

class MapCoreWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MapCoreWidget(QWidget *parent = nullptr);

    void DFS(int P1, int P2);//算法
    bool isin(QPoint x, QPoint y, int n = 10);//判断是否点击到
    double dist(QPoint a, QPoint b);//距离
    void clr();//清除


    void setAddNode();//添加节点
    void setAddPath();//添加路径
    void setDeleteNode();//删除节点
    void setDeletePath();//删除路径
    void setEditNode();//编辑节点
    void setEditPathLen();//编辑路径长

    void findAllPaths();//查询所有
    void findAllPaths(QString,QString);//查询所有
    void displayPathLen();//显示路径长

    void clearMap();//清除地图
    void saveMap();//保存地图
    void loadMap();//加载地图
    void loadMap(QString);//加载地图
    void loadImage();//加载图片
    QStringList getMapCorePl();

protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent* event);
signals:
    void sendMapCorePl(QStringList);//发送地图信号
    void sendLabelTip(QString);//提示信息
    void sendStartPoint(QString);//开始点
    void sendStopPoint(QString);//结束点
    void sendListClear();//清除列表
    void sendListAdd(QString);//添加列表
    void sendMinPath(QString);//最短路径
public slots:

public:
    int m_type = 0;//类型
    int num1 = 0, num2 = 0;
    double matrix[51][51] = {};//矩阵
    bool reach[51] = {};

    QPoint P1, P2;//两个临时点
    QPoint m_Point[51];//点数组，防越界   点位置
    QString  pic;//每个点的标签，pic为当前背景图片的存储路径
    int ways;//右侧显示栏路径的数量
    double dis, min;//dis是搜索路径时路径长度当前值，min是路径长度最小值
    bool showlen = false;//是否显示当前路径长度
    int count = 0;//添加的点的默认下标

};

#endif // MAPCOREWIDGET_H
