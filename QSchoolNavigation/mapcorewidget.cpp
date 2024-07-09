#pragma execution_character_set("utf-8")
#include "mapcorewidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QFont>
#include <QApplication>
#include <QDebug>
#include <QFileDialog>
#include <QInputDialog>
using namespace std;
struct MapCorelines { int a, b; bool f = false; } temp1, line[101];//线，ab是两点p1，p2的下标，f是否是最短路径，如是则标红，否则保持蓝色。temp1是当前线，line数组存储所有线
QString MapCorePl[51];
class MapCoreStack//用于dfs，遍历时，“错误”路径时倒退
{
private:
    int a[51] = {};//存储点的下标
    int num = 0;//初始化点的个数
public:
    void push(int n) { a[++num] = n; }//压入栈
    void pop() { a[num--] = 0; }//出栈
    QString getstr()//右侧显示栏中点的标签展示，路径结果
    {
        QString str = "";
        for (int i = 1; i < num; i++)
            str += MapCorePl[a[i]] + "->";
        str += MapCorePl[a[num]];
        return str;
    }
    void showline()//将最短路径标红
    {
        for (int i = 1; i < num; i++)
        {
            for (int j = 1; line[j].a && j <= 100; j++)//在line[j]存在并且line数量在100以内循环
                if ((line[j].a == a[i] && line[j].b == a[i + 1]) || (line[j].b == a[i] && line[j].a == a[i + 1]))//如果线当中点的下标与最短路径栈中存储的点下标相同
                {
                    line[j].f = true;//标红
                    break;
                }
        }
    }
}stack, temp2;//temp2存储最短路径对应的栈

MapCoreWidget::MapCoreWidget(QWidget *parent) : QWidget(parent)
{
    dis = 0;
    min = 0;
}

void MapCoreWidget::DFS(int i, int j)//i为起点，j为终点
{
    reach[i] = true;//起点到达
    stack.push(i);//将起点压入栈内
    if (i == j)//判断已经到达终点
    {
        if (ways <= 200000) emit sendListAdd(stack.getstr() + "，长度为：" + QString::number(dis)), ways++;
        if (min == 0 || dis < min)//将最短路径值赋给min以及temp2
        {
            min = dis;
            temp2 = stack;
        }
    }
    else//未到达终点，遍历所有可行途径
        for (int t = 1; t <= num2; t++)
            if (matrix[i][t] && !reach[t])//matrix[i][t]存在，即该路径存在，并且m_Point[t]未达到
            {
                dis += matrix[i][t];//当前路径长度＋目前点到下一个点的距离
                DFS(t, j);//递归，t为新的起点
                dis -= matrix[i][t];//更换新路径，将此前路径长度减去
            }
    stack.pop();//将最新的点弹出
    reach[i] = false;//因为此点弹出，故未达到
}

void MapCoreWidget::clr()//清除右侧显示栏的显示信息
{
    emit sendStartPoint("");
    emit sendStopPoint("");
    emit sendListClear();
    for (int i = 1; i <= num1; i++)
        if (line[i].f) line[i].f = false;//红线变回蓝线
    update();//调用paintEvent函数
}

void MapCoreWidget::setAddNode()
{
    clr();
    if (m_type != 3){
        m_type = 3;
        emit sendLabelTip("请选择一个位置添加点");//转到case 1
    }
    else {
        m_type = 0;
        emit sendLabelTip(" ");//转到case 3
    }
}

void MapCoreWidget::setAddPath()
{
    clr();
    if (m_type != 1){
        m_type = 1;
        emit sendLabelTip("请选择第一个点");//转到case 1
    }
    else{
        m_type = 0;
        emit sendLabelTip(" ");//转到case 3
    }
}

void MapCoreWidget::setDeleteNode()
{
    clr();
    if (m_type != 4){
        m_type = 4;
        emit sendLabelTip("请选择一个位置删除点");//转到case 4
    }
    else{
        m_type = 0;
        emit sendLabelTip("");//跳出
    }
}

void MapCoreWidget::setDeletePath()
{
    clr();
    if (m_type != 5) {
        m_type = 5;emit sendLabelTip("请选择要删除路径的第一个点");//转到case 5
    }
    else {
        m_type = 0; emit sendLabelTip("");//跳出
    }
}

void MapCoreWidget::setEditNode()
{
    clr();
    if (m_type != 7){
        m_type = 7;
        emit sendLabelTip("请选择要编辑标签的点");//转到case 7
    }
    else {
        m_type = 0;
        emit sendLabelTip(" ");//跳出
    }
}

void MapCoreWidget::setEditPathLen()
{
    clr();
    if (m_type != 10){
        m_type = 10;
        emit sendLabelTip("请选择要编辑路径长度的第一个点");//转到case 10
    }else{
        m_type = 0;
        emit sendLabelTip("");//跳出
    }
}

void MapCoreWidget::findAllPaths()
{
    clr();
    if (m_type != 8) {
        if (num1 == 0) { QMessageBox::warning(this, "警告", "无任何路径"); return; }//判断整个地图是否存在路径
        m_type = 8;
        emit sendLabelTip("请选择起点");//转到case 8
        emit sendStartPoint("起点：");
        emit sendListClear();
        emit sendStopPoint("");
        emit sendListAdd("搜索结果将会显示在这里");
    }
    else{
        m_type = 0;
        emit sendLabelTip("");//跳出
    }
}

void MapCoreWidget::findAllPaths(QString p_str1, QString p_str2)
{
    clr();
    int p_1 = 0;
    int p_2 = 0;
    for(int i = 0; i < 51;i++){
        if(p_str1 == MapCorePl[i]){
            p_1 = i;
        }
    }
    for(int i = 0; i < 51;i++){
        if(p_str2 == MapCorePl[i]){
            p_2 = i;
        }
    }

    temp1.a = p_1;//终点下标赋给temp1
    temp1.b = p_2;//终点下标赋给temp1
    emit sendListClear();
    ways = 0;
    min = 0;
    DFS(temp1.a, temp1.b);
    if (ways)//若有路
    {
        if (ways > 200000){
            emit sendListAdd("路径数过多，超过200000条，无法完全显示！最短路径为：" + temp2.getstr() + "，长度为：" + QString::number(min));
        }else{

            emit sendMinPath("其中最短路径为：" + temp2.getstr() + "，长度为：" + QString::number(min));
            emit sendListAdd("共" + QString::number(ways) + "条路径，其中最短路径为：" + temp2.getstr() + "，长度为：" + QString::number(min));
        }
        temp2.showline();//最短路径展示
        update();
    }
    else
        emit sendListAdd("找不到路径");
    m_type = 0;
    emit sendLabelTip(" ");

}

void MapCoreWidget::displayPathLen()
{
    if (!showlen){
        showlen = true;
    }
    else{
        showlen = false;
    }
    update();
}

void MapCoreWidget::clearMap()
{
    QMessageBox::StandardButton btn;
    btn = QMessageBox::question(this, "提示", "确认要清除地图吗？", QMessageBox::Yes | QMessageBox::No);
    if (btn == QMessageBox::Yes)//清除地图
    {
        pic = "";
        for (int i = 1; i <= num2; i++)
        {
            m_Point[i] = m_Point[0];
            MapCorePl[i] = MapCorePl[0];
            for (int j = 1; j <= num2; j++)
                matrix[i][j] = 0;
        }
        for (int i = 1; i <= num1; i++)
            line[i] = line[0];
        m_type = num2 = num1 = count = 0;
        clr();
        emit sendStopPoint("");
    }
}

void MapCoreWidget::saveMap()
{
    QString filename = QFileDialog::getSaveFileName(this, "保存文件", "", "地图文件(*.map2)");//文件扩展名为.map2
    if (filename != "")//判断地址是否输入成功
    {
        ofstream out(filename.toStdString());//转换为标准字符串进行保存
        if (out.is_open())
        {
            out << "map" << endl;
            out << num1 << ' ' << num2 << endl;
            for (int i = 1; i <= num2; i++)
                out << m_Point[i].x() << ' ' << m_Point[i].y() << ' ' << MapCorePl[i].toStdString() << endl;//空格隔开
            for (int i = 1; i <= num2; i++)
            {
                for (int j = 1; j <= num2; j++)
                    out << matrix[i][j] << ' ';
                out << endl;
            }
            for (int i = 1; i <= num1; i++)
                out << line[i].a << ' ' << line[i].b << endl;
            out << pic.toStdString() << endl;
            QMessageBox::information(this, "提示", "保存成功");
            out.close();//关闭文档
        }
        else QMessageBox::information(this, "提示", "保存失败");
    }
}

void MapCoreWidget::loadMap()
{
    QString filename = QFileDialog::getOpenFileName(this, "选择文件", "", "地图文件(*.map2)");
    if (filename != "")
    {
        ifstream in(filename.toStdString());
        if (in.is_open())
        {
            string c;
            in >> c;
            // QString::fromStdString(c));//转变为Qstring --标题
            in >> num1 >> num2;
            for (int i = 1; i <= num2; i++)
            {
                int a, b;
                in >> a >> b;
                m_Point[i].setX(a);
                m_Point[i].setY(b);
                in >> c;
                MapCorePl[i] = QString::fromStdString(c);//名称
            }
            for (int i = 1; i <= num2; i++)
                for (int j = 1; j <= num2; j++)
                    in >> matrix[i][j];
            for (int i = 1; i <= num1; i++)
                in >> line[i].a >> line[i].b;
            in >> c;
            pic = QString::fromStdString(c);//图片
            clr();
            QMessageBox::information(this, "提示", "读取成功");
            QStringList t_list;
            for(int i = 0 ; i < 51;i++){
                t_list.append(MapCorePl[i]);
            }
            emit sendMapCorePl(t_list);
            in.close();//关闭文件
        }
        else QMessageBox::information(this, "提示", "读取失败");
    }
}

void MapCoreWidget::loadMap(QString filename)
{
    if (filename != "")
    {
        ifstream in(filename.toStdString());
        if (in.is_open())
        {
            string c;
            in >> c;
            // QString::fromStdString(c));//转变为Qstring --标题
            in >> num1 >> num2;
            for (int i = 1; i <= num2; i++)
            {
                int a, b;
                in >> a >> b;
                m_Point[i].setX(a);
                m_Point[i].setY(b);
                in >> c;
                MapCorePl[i] = QString::fromStdString(c);//名称
            }
            for (int i = 1; i <= num2; i++)
                for (int j = 1; j <= num2; j++)
                    in >> matrix[i][j];
            for (int i = 1; i <= num1; i++)
                in >> line[i].a >> line[i].b;
            in >> c;
            pic = QString::fromStdString(c);//图片
            clr();
            QMessageBox msgBox;
            QTimer::singleShot(1500,&msgBox,SLOT(accept())); //也可将accept改为close
            msgBox.setWindowTitle("提示");
            msgBox.setText("读取成功.");
            msgBox.exec();
            QStringList t_list;
            for(int i = 0 ; i < 51;i++){
                t_list.append(MapCorePl[i]);
            }
            emit sendMapCorePl(t_list);
            in.close();//关闭文件
        }
        else{
            QMessageBox msgBox;
            QTimer::singleShot(1500,&msgBox,SLOT(accept())); //也可将accept改为close
            msgBox.setWindowTitle("提示");
            msgBox.setText("读取失败.");
            msgBox.exec();
        }
    }

}

void MapCoreWidget::loadImage()
{
    QString temp = QFileDialog::getOpenFileName(this, "选择文件", QApplication::applicationDirPath(), "图像文件(*.jpg *.jpeg *.bmg *.png *.gif)");
    if (temp != "") pic = temp;//传入图片存储路径
    update();
}

QStringList MapCoreWidget::getMapCorePl()
{
    QStringList t_list;
    for(int i = 0 ; i < 51;i++){
        t_list.append(MapCorePl[i]);
    }
    return t_list;
}

double MapCoreWidget::dist(QPoint a, QPoint b)//计算两点间距离的函数
{
    return sqrt((a.x() - b.x()) * (a.x() - b.x()) + (a.y() - b.y()) * (a.y() - b.y()));
}

bool MapCoreWidget::isin(QPoint x, QPoint y, int n)//判断鼠标光标是否点击成功（半径n的圆域范围内）
{
    if (dist(x, y) <= n) return true;
    else return false;
}

void MapCoreWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);//画笔，this为当前窗口
    painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap(pic));//载入背景图片并显示出来
    QFont font1("Microsoft YaHei", 9);//字体说明
    QFont font2("Microsoft YaHei", 12);
    painter.drawRect(0, 0, this->width()-1, this->height()-1);//矩形大小，窗口大小
    painter.setFont(font1);
    painter.setRenderHint(QPainter::Antialiasing, true);//使接下来的绘图光滑
    for (int i = 1; i <= num1; i++)
    {
        if (!line[i].f){
            painter.setPen(Qt::blue);//设置画笔颜色为蓝色
        }
        else{
            QPen pen;
            pen.setColor(Qt::red);
            pen.setWidth(6);
            painter.setPen(pen);
        }
        painter.drawLine(m_Point[line[i].a], m_Point[line[i].b]);//两点连线
    }
    painter.setPen(Qt::darkMagenta);
    if (showlen)//如果显示路径
    {
        for (int i = 1; i < num2; i++){
            for (int j = i + 1; j <= num2; j++){
                if (matrix[i][j])//若路径存在
                {
                    int x1, y1;
                    x1 = (m_Point[i].x() + m_Point[j].x()) / 2 - 10;//路径中央偏左
                    y1 = (m_Point[i].y() + m_Point[j].y()) / 2 + 4;//路径中央偏下
                    painter.drawText(QPoint(x1, y1), QString::number(matrix[i][j]));//路径长度显示在（x,y）位置处
                }
            }
        }
    }
    painter.setPen(Qt::black);
    painter.setBrush(Qt::yellow);
    painter.setFont(font2);
    for (int i = 1; i <= num2; i++)
    {
        painter.drawEllipse(m_Point[i], 10, 10);//把点画出来
        painter.drawText(QPoint(m_Point[i].x()-5 , m_Point[i].y() + 6), MapCorePl[i]);//画出点的标签，MapCorePl[i]为标签
    }
}

void MapCoreWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPoint temp = event->pos();//event->pos为当前点击位置
        switch (m_type)
        {
        case 1://选择第一个点
            if (num1 == 100) QMessageBox::warning(this, "警告", "路径数已达上限");
            else
                for (int i = 1; i <= num2; i++)
                    if (isin(temp, m_Point[i]))//选中
                    {
                        P1 = m_Point[i]; line[num1 + 1].a = i; m_type = 2;
                        emit sendLabelTip("请选择第二个点");
                        break;//将第一个点信息存入P1，line[num1+1]，并开始case2功能
                    } break;
        case 2://选择第二个点
            for (int i = 1; i <= num2; i++)
                if (m_Point[i] != P1 && isin(temp, m_Point[i]))//若选中了与第一个点不同的点
                {
                    int t = num1++;//线数量+1
                    P2 = m_Point[i]; line[num1].b = i; m_type = 1;//P2信息录入，完善line[num1]信息（num1已+1），tp回归1.
                    if (line[num1].a > line[num1].b)//保证线的第一个点下标比第二个小
                    {
                        int t1 = line[num1].a; line[num1].a = line[num1].b; line[num1].b = t1;
                    }
                    for (int j = 1; j < num1; j++)//判断是否路线已经存在
                    {
                        if (line[num1].a == line[j].a && line[num1].b == line[j].b)
                        {
                            line[num1--] = line[0];
                            QMessageBox::warning(this, "警告", "两条路径重合");
                            break;
                        }
                    }
                    if (t != num1)//将两点间的像素距离赋值给两点间的路径长度（默认）
                    {
                        matrix[line[num1].a][line[num1].b] = matrix[line[num1].b][line[num1].a] = dist(m_Point[line[num1].a], m_Point[line[num1].b]);
                    }
                    emit sendLabelTip("请选择第一个点");
                    break;
                }
            update(); break;
        case 3://添加点
            if (num2 < 50 && temp.x() >= 0 && temp.x() <= this->width() && temp.y()>0 && temp.y() <= this->height())//判断所加的点是否在窗口范围内
            {
                int t = num2++;
                for (int i = 1; i < num2; i++)
                    if (isin(temp, m_Point[i], 20))//判断两点是否太近，选中条件为“半径10的圆邻域”，故两点距离需要大于20
                    {
                        num2--; QMessageBox::warning(this, "警告", "两个点靠太近");
                    }
                if (t == num2) break;
                m_Point[num2] = event->pos();//当前位置赋给最新的P点
                MapCorePl[num2] = QString::number(++count);//创建默认标签
                update();
            }
            else if (num2 == 50) QMessageBox::warning(this, "警告", "点数已达上限");
            else QMessageBox::warning(this, "警告", "点超出边界");
            break;
        case 4://删除点
            if (num2 == 0) QMessageBox::warning(this, "警告", "无任何点");
            else
                for (int i = 1; i <= num2; i++)
                    if (isin(temp, m_Point[i]))//选中想要删除的点
                    {
                        for (int j = i; j < num2; j++)
                        {
                            m_Point[j] = m_Point[j + 1];//将删除的点后的点前移
                            MapCorePl[j] = MapCorePl[j + 1];//点的标签同理
                            for (int k = 1; k <= num2; k++)//此一系列对matrix的操作使该点下标对应的行列删除
                                matrix[j][k] = matrix[j + 1][k];
                        }
                        for (int j = i; j < num2; j++)
                            for (int k = 1; k <= num2; k++)
                                matrix[k][j] = matrix[k][j + 1];
                        for (int j = 1; j <= num2; j++)
                            matrix[j][num2] = matrix[num2][j] = 0;
                        MapCorePl[num2] = MapCorePl[0];//最后一个点标签消失
                        m_Point[num2--] = m_Point[0];//最后一个点消失
                        for (int j = 1; j <= num1; j++)
                        {
                            if (i == line[j].a || i == line[j].b)//将line数组一并前移
                            {
                                for (int k = j; k < num1; k++)
                                    line[k] = line[k + 1];
                                line[num1--] = line[0];//将最后一条线消除，同时线数量减一
                                j--;
                            }
                            else//下标原在被选中的点之后的点所在线的下标前移
                            {
                                if (line[j].a > i) line[j].a--;
                                if (line[j].b > i) line[j].b--;
                            }
                        }
                        update();
                        break;
                    }
            break;
        case 5://选择第一个点删除路径
            if (num1 == 0) QMessageBox::warning(this, "警告", "无任何路径");
            else
                for (int i = 1; i <= num2; i++)
                    if (isin(temp, m_Point[i]))//判断选中
                    {
                        P1 = m_Point[i]; temp1.a = i; m_type = 6;
                        emit sendLabelTip("请选择要删除路径的第二个点");
                    } break;
        case 6://选择第二个点删除路径
            for (int i = 1; i <= num2; i++)
            {
                if (m_Point[i] != P1 && isin(temp, m_Point[i]))//选中
                {
                    P2 = m_Point[i]; temp1.b = i; m_type = 5;//第二个点信息载入
                    if (temp1.a > temp1.b)//保证线的第二个点下标大于第一个
                    {
                        int t1 = temp1.a; temp1.a = temp1.b; temp1.b = t1;
                    }
                    int t3 = num1;
                    for (int j = 1; j <= num1; j++)
                    {
                        if (temp1.a == line[j].a && temp1.b == line[j].b)
                        {
                            matrix[line[j].a][line[j].b] = matrix[line[j].b][line[j].a] = 0;//点之间路径长度删除
                            {for (int k = j; k < num1; k++)
                                    line[k] = line[k + 1];//路径（线）下标前移
                                line[num1--] = line[0];
                                break; }
                        }
                    }
                    emit sendLabelTip("请选择要删除路径的第一个点");
                    if (num1 == t3) QMessageBox::warning(this, "警告", "找不到这条路径");
                    else break;
                }
            }
            update(); break;
        case 7://编辑点的标签
            if (num2 == 0) QMessageBox::warning(this, "警告", "无任何点");
            else
                for (int i = 1; i <= num2; i++)
                    if (isin(temp, m_Point[i]))
                    {
                        QString s0 = QInputDialog::getText(this, "编辑标签", "输入文本(最多13个字)");
                        if (s0 != "") MapCorePl[i] = s0.left(13);
                        break;
                    }
            break;
        case 8://选择起点
            for (int i = 1; i <= num2; i++)
                if (isin(temp, m_Point[i]))//判断点击到了那个P点
                {
                    P1 = m_Point[i];
                    qDebug()<<"P1=="<<P1;
                    qDebug()<<"i=="<<i;
                    m_type = 9;
                    emit sendLabelTip("请选择终点");
                    temp1.a = i;//起点下标赋给temp1
                    emit sendStartPoint("起点：" + MapCorePl[i]);
                    emit sendStopPoint("终点：");
                    break;
                } break;
        case 9://选择终点
            for (int i = 1; i <= num2; i++){
                if (m_Point[i] != P1 && isin(temp, m_Point[i]))//判断不与起点重合
                {
                    P2 = m_Point[i];
                    temp1.b = i;//终点下标赋给temp1
                    emit sendStopPoint("终点：" + MapCorePl[i]);
                    emit sendListClear();
                    ways = 0;
                    min = 0;
                    DFS(temp1.a, temp1.b);
                    if (ways)//若有路
                    {
                        if (ways > 200000){
                            emit sendListAdd("路径数过多，超过200000条，无法完全显示！最短路径为：" + temp2.getstr() + "，长度为：" + QString::number(min));
                        }else{

                            emit sendMinPath("其中最短路径为：" + temp2.getstr() + "，长度为：" + QString::number(min));
                            emit sendListAdd("共" + QString::number(ways) + "条路径，其中最短路径为：" + temp2.getstr() + "，长度为：" + QString::number(min));
                        }
                        temp2.showline();//最短路径展示
                        update();
                    }
                    else
                        emit sendListAdd("找不到路径");
                    m_type = 0;
                    emit sendLabelTip(" ");
                    break;
                }
            }
            break;
        case 10://编辑路径长度第一个点
            if (num1 == 0) QMessageBox::warning(this, "警告", "无任何路径");
            else
                for (int i = 1; i <= num2; i++)
                    if (isin(temp, m_Point[i]))//选中
                    {
                        P1 = m_Point[i]; m_type = 11;
                        emit sendLabelTip("请选择要编辑路径长度的第二个点");//转入下一个case
                        temp1.a = i;
                        break;
                    } break;
        case 11://编辑路径长度第二个点
            for (int i = 1; i <= num2; i++)
                if (m_Point[i] != P1 && isin(temp, m_Point[i]))//不与第一个点重合
                {
                    P2 = m_Point[i];
                    temp1.b = i;
                    m_type = 10;
                    if (temp1.a > temp1.b)//保证线的第二个点下标大于第一个
                    {
                        int t1 = temp1.a; temp1.a = temp1.b; temp1.b = t1;
                    }
                    bool f0 = false;
                    for (int j = 1; j <= num1; j++)
                    {
                        if (temp1.a == line[j].a && temp1.b == line[j].b)
                        {
                            double number = QInputDialog::getDouble(this, "编辑长度", "输入浮点数(0.0001~999999)", matrix[temp1.a][temp1.b], 0.0001, 999999, 4);
                            if (number) matrix[temp1.a][temp1.b] = matrix[temp1.b][temp1.a] = number;//若输入了数，则点之间长度更改
                            f0 = true;
                            break;
                        }
                    }
                    emit sendLabelTip("请选择要编辑路径长度的第一个点");
                    if (!f0) QMessageBox::warning(this, "警告", "找不到这条路径");
                    update();
                    break;
                }
            break;
        }
    }

}
