#pragma execution_character_set("utf-8")
#include <QApplication>
#include "exhibitionwidget.h"
#include "ui_exhibitionwidget.h"
#include <QDir>
#include <QImage>

ExhibitionWidget::ExhibitionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExhibitionWidget)
{
    ui->setupUi(this);
    m_filelist = findAllJsonFile(QApplication::applicationDirPath()+"/image");
    m_fileTxtlist = findAllTxtFile(QApplication::applicationDirPath()+"/image");
    QStringList t_fileTxtlist;
    for(int i = 0 ; i < m_fileTxtlist.size();i++){
        QFileInfo t_info(QApplication::applicationDirPath()+"/image/"+m_fileTxtlist.at(i));
        ui->comboBox->addItem(t_info.baseName());
        t_fileTxtlist.append(t_info.baseName());
    }
    m_fileTxtlist =  t_fileTxtlist;
    m_num = 0;
    loadImage();
}
//遍历所有的json文件
QStringList ExhibitionWidget::findAllJsonFile(QString path)
{
    QStringList retList;
    QDir dir(path);
    QStringList nameFilters;
    nameFilters << "*.jpg";
    QStringList nameFileListTs = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
    retList.append(nameFileListTs);
    return retList;
}
//遍历所有的txt文件
QStringList ExhibitionWidget::findAllTxtFile(QString path)
{
    QStringList retList;
    QDir dir(path);
    QStringList nameFilters;
    nameFilters << "*.txt";
    QStringList nameFileListTs = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
    retList.append(nameFileListTs);
    return retList;
}

void ExhibitionWidget::loadImage()
{
    qDebug()<<"filetxt"<<filetxt;

    QImage t_iamge;
    t_iamge.load(QApplication::applicationDirPath()+"/image/"+filetxt+".jpg");
    t_iamge = t_iamge.scaled(ui->label->width(),ui->label->height());
    ui->label->setPixmap(QPixmap::fromImage(t_iamge));
    QFile t_file(QApplication::applicationDirPath()+"/image/"+filetxt+".txt");
    if (!t_file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    ui->textEdit->clear();
    ui->textEdit->append(t_file.readAll());
}

ExhibitionWidget::~ExhibitionWidget()
{
    delete ui;
}

void ExhibitionWidget::on_pushButton_clicked()
{
    m_num--;
    if(m_num < 0){
        m_num = 0;
    }
    filetxt = m_fileTxtlist.at(m_num);
    loadImage();
}

void ExhibitionWidget::on_pushButton_2_clicked()
{
    m_num++;
    if(m_num >= m_fileTxtlist.size()){
        m_num= m_fileTxtlist.size()-1;
    }
    filetxt = m_fileTxtlist.at(m_num);
    loadImage();
}

void ExhibitionWidget::on_comboBox_currentIndexChanged(const QString &arg1)
{
    m_num = ui->comboBox->currentIndex();
    filetxt = arg1;
    loadImage();
}

void ExhibitionWidget::on_pushButton_3_clicked()
{
    bool state = false;
    for(int i = 0;i < m_fileTxtlist.size();i++){
        m_num = i;
        if(ui->lineEdit->text() == m_fileTxtlist.at(i)){
            state = true;
            filetxt = ui->lineEdit->text();
            loadImage();
        }
    }
    if(state == false){
        QMessageBox msgBox;
        QTimer::singleShot(1000,&msgBox,SLOT(accept())); //也可将accept改为close
        msgBox.setWindowTitle("提示");
        msgBox.setText("查询失败.");
        msgBox.exec();
    }
}
