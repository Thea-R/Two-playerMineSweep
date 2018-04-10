/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *ipLabel;
    QLabel *portLabel;
    QLineEdit *ipLine;
    QLineEdit *portLine;
    QPushButton *conBtn;
    QLabel *sLabel;
    QLabel *cLabel;
    QPushButton *startBtn;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(822, 458);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ipLabel = new QLabel(centralWidget);
        ipLabel->setObjectName(QStringLiteral("ipLabel"));
        ipLabel->setGeometry(QRect(510, 30, 60, 41));
        QFont font;
        font.setPointSize(18);
        ipLabel->setFont(font);
        ipLabel->setStyleSheet(QStringLiteral("color:black"));
        portLabel = new QLabel(centralWidget);
        portLabel->setObjectName(QStringLiteral("portLabel"));
        portLabel->setGeometry(QRect(510, 65, 60, 31));
        portLabel->setFont(font);
        portLabel->setStyleSheet(QStringLiteral("color:black"));
        ipLine = new QLineEdit(centralWidget);
        ipLine->setObjectName(QStringLiteral("ipLine"));
        ipLine->setGeometry(QRect(560, 40, 113, 24));
        ipLine->setInputMethodHints(Qt::ImhUrlCharactersOnly);
        portLine = new QLineEdit(centralWidget);
        portLine->setObjectName(QStringLiteral("portLine"));
        portLine->setGeometry(QRect(560, 70, 113, 24));
        portLine->setInputMethodHints(Qt::ImhDigitsOnly);
        conBtn = new QPushButton(centralWidget);
        conBtn->setObjectName(QStringLiteral("conBtn"));
        conBtn->setGeometry(QRect(690, 60, 81, 41));
        QFont font1;
        font1.setPointSize(16);
        conBtn->setFont(font1);
        conBtn->setStyleSheet(QStringLiteral("color:black"));
        sLabel = new QLabel(centralWidget);
        sLabel->setObjectName(QStringLiteral("sLabel"));
        sLabel->setGeometry(QRect(160, 60, 60, 21));
        sLabel->setFont(font);
        sLabel->setTabletTracking(false);
        sLabel->setStyleSheet(QStringLiteral("color:black"));
        cLabel = new QLabel(centralWidget);
        cLabel->setObjectName(QStringLiteral("cLabel"));
        cLabel->setGeometry(QRect(600, 60, 60, 21));
        cLabel->setFont(font);
        cLabel->setTabletTracking(false);
        cLabel->setStyleSheet(QStringLiteral("color:black"));
        startBtn = new QPushButton(centralWidget);
        startBtn->setObjectName(QStringLiteral("startBtn"));
        startBtn->setGeometry(QRect(580, 60, 81, 41));
        startBtn->setFont(font1);
        startBtn->setStyleSheet(QStringLiteral("color:black"));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        ipLabel->setText(QApplication::translate("MainWindow", "IP", nullptr));
        portLabel->setText(QApplication::translate("MainWindow", "Port", nullptr));
        conBtn->setText(QApplication::translate("MainWindow", "send", nullptr));
        sLabel->setText(QApplication::translate("MainWindow", "Server", nullptr));
        cLabel->setText(QApplication::translate("MainWindow", "Client", nullptr));
        startBtn->setText(QApplication::translate("MainWindow", "start", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
