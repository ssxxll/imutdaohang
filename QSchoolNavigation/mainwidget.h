#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "navigationwidget.h"
#include "aboutwidget.h"
#include "campusprofilewidget.h"
#include "exhibitionwidget.h"
namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private slots:
    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWidget *ui;
    NavigationWidget    *m_NavigationWidget;
    AboutWidget         *m_AboutWidget;
    CampusProfileWidget *m_CampusProfileWidget;
    ExhibitionWidget    *m_ExhibitionWidget;
};

#endif // MAINWIDGET_H
