#pragma execution_character_set("utf-8")
#include "campusprofilewidget.h"
#include "ui_campusprofilewidget.h"
//简介界面
CampusProfileWidget::CampusProfileWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CampusProfileWidget)
{
    ui->setupUi(this);
}

CampusProfileWidget::~CampusProfileWidget()
{
    delete ui;
}
