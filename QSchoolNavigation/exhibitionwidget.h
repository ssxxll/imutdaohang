#ifndef EXHIBITIONWIDGET_H
#define EXHIBITIONWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QDebug>
#include <QMessageBox>
namespace Ui {
class ExhibitionWidget;
}
//展示
class ExhibitionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ExhibitionWidget(QWidget *parent = nullptr);
    ~ExhibitionWidget();
    QStringList findAllJsonFile(QString path);//查询jpg
     QStringList findAllTxtFile(QString path);//查询所以txt
    void loadImage();//加载图片和文本
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_pushButton_3_clicked();

private:
    Ui::ExhibitionWidget *ui;
    int m_num;
    QStringList m_filelist;//图片列表
    QStringList m_fileTxtlist;//txt列表
    QString filetxt;
};

#endif // EXHIBITIONWIDGET_H
