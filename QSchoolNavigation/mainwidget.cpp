#pragma execution_character_set("utf-8")
#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    m_NavigationWidget = new NavigationWidget();

    m_AboutWidget = new AboutWidget();
    m_CampusProfileWidget = new CampusProfileWidget();
    m_ExhibitionWidget = new ExhibitionWidget();

    ui->stackedWidget->addWidget(m_AboutWidget);
    ui->stackedWidget->addWidget(m_CampusProfileWidget);
    ui->stackedWidget->addWidget(m_ExhibitionWidget);
    ui->stackedWidget->addWidget(m_NavigationWidget);

    setWindowTitle("Qt内蒙古工业大学金川校区导航");

    ui->stackedWidget->setCurrentWidget(m_CampusProfileWidget);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_pushButton_1_clicked()
{
    ui->stackedWidget->setCurrentWidget(m_CampusProfileWidget);
}

void MainWidget::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(m_ExhibitionWidget);
}

void MainWidget::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentWidget(m_NavigationWidget);
}

void MainWidget::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentWidget(m_AboutWidget);
}
