/********************************************************************************
** Form generated from reading UI file 'syssec.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYSSEC_H
#define UI_SYSSEC_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SysSec
{
public:
    QWidget *centralWidget;
    QLabel *img_label;
    QPushButton *Capture;
    QLineEdit *lineEdit;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SysSec)
    {
        if (SysSec->objectName().isEmpty())
            SysSec->setObjectName(QString::fromUtf8("SysSec"));
        SysSec->resize(479, 281);
        centralWidget = new QWidget(SysSec);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        img_label = new QLabel(centralWidget);
        img_label->setObjectName(QString::fromUtf8("img_label"));
        img_label->setGeometry(QRect(140, 70, 200, 200));
        Capture = new QPushButton(centralWidget);
        Capture->setObjectName(QString::fromUtf8("Capture"));
        Capture->setGeometry(QRect(240, 10, 200, 40));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(20, 15, 120, 30));
        lineEdit->setAlignment(Qt::AlignCenter);
        SysSec->setCentralWidget(centralWidget);
        lineEdit->raise();
        img_label->raise();
        Capture->raise();
        statusBar = new QStatusBar(SysSec);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        SysSec->setStatusBar(statusBar);

        retranslateUi(SysSec);

        QMetaObject::connectSlotsByName(SysSec);
    } // setupUi

    void retranslateUi(QMainWindow *SysSec)
    {
        SysSec->setWindowTitle(QApplication::translate("SysSec", "SysSec", 0, QApplication::UnicodeUTF8));
        img_label->setText(QString());
        Capture->setText(QApplication::translate("SysSec", "PushButton", 0, QApplication::UnicodeUTF8));
        lineEdit->setText(QApplication::translate("SysSec", "Software Security", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SysSec: public Ui_SysSec {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYSSEC_H
