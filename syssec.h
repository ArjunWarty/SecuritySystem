#ifndef SYSSEC_H
#define SYSSEC_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class SysSec;
}

class SysSec : public QMainWindow
{
    Q_OBJECT

public:
    explicit SysSec(QWidget *parent = nullptr);
    ~SysSec();

private slots:
    void on_Capture_clicked();

private:
    Ui::SysSec *ui;
};

#endif // SYSSEC_H
