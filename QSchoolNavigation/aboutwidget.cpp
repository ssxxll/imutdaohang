#pragma execution_character_set("utf-8")
#include "aboutwidget.h"
#include "ui_aboutwidget.h"

AboutWidget::AboutWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutWidget)
{
    ui->setupUi(this);
}

AboutWidget::~AboutWidget()
{
    delete ui;
}
