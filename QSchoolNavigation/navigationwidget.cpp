#pragma execution_character_set("utf-8")
#include "navigationwidget.h"
#include "ui_navigationwidget.h"
#include <QMessageBox>
#include <QApplication>
NavigationWidget::NavigationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NavigationWidget)
{
    ui->setupUi(this);
    connect(ui->widget,SIGNAL(sendListClear()),this,SLOT(acceptListClear()));
    connect(ui->widget,SIGNAL(sendListAdd(QString)),this,SLOT(acceptListAdd(QString)));
    connect(ui->widget,SIGNAL(sendMinPath(QString)),this,SLOT(acceptMinPath(QString)));

    connect(ui->widget,SIGNAL(sendMapCorePl(QStringList)),this,SLOT(acceptMapCorePl(QStringList)));

    ui->widget->loadMap(QApplication::applicationDirPath()+"/neimeng.map2");
}

NavigationWidget::~NavigationWidget()
{
    delete ui;
}

void NavigationWidget::on_pushButton_clicked()
{
    if( ui->comboBox_1->currentText()!= ui->comboBox_2->currentText()){
        ui->widget->findAllPaths(ui->comboBox_1->currentText(),ui->comboBox_2->currentText());
    }else{
        QMessageBox::information(this, "提示", "查询失败，起点和终点相同");
    }
}

void NavigationWidget::acceptListClear()
{
    ui->listWidget->clear();
}

void NavigationWidget::acceptListAdd(QString str)
{
    ui->listWidget->addItem(str);
}

void NavigationWidget::acceptMapCorePl(QStringList p_list)
{
    ui->comboBox_1->clear();
    ui->comboBox_1->clear();

    for(int i = 0 ; i < p_list.size();i++){
        if(p_list.at(i).size() >=1){
            ui->comboBox_1->addItem(p_list.at(i));
            ui->comboBox_2->addItem(p_list.at(i));
        }
    }
}

void NavigationWidget::acceptMinPath(QString str)
{
    qDebug()<<"acceptMinPath==="<<str;
    ui->textEdit->clear();
    ui->textEdit->append(str);
}


