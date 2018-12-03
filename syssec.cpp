#include "syssec.h"
#include "ui_syssec.h"

SysSec::SysSec(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SysSec)
{
    ui->setupUi(this);

}

SysSec::~SysSec()
{
    delete ui;
}

void SysSec::on_Capture_clicked()
{
    QPixmap img = QPixmap("C:/Users/arjun/Desktop/QT/ProjectFinal/image.png");
    ui->img_label->setPixmap(img);
}
