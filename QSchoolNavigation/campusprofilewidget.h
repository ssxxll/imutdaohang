#ifndef CampusProfileWidget_H
#define CampusProfileWidget_H

#include <QWidget>

namespace Ui {
class CampusProfileWidget;
}
//简介界面
class CampusProfileWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CampusProfileWidget(QWidget *parent = nullptr);
    ~CampusProfileWidget();

private:
    Ui::CampusProfileWidget *ui;
};

#endif // CampusProfileWidget
