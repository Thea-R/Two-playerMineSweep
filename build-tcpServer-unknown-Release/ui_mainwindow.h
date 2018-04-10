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
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *pLabel;
    QPushButton *pBtn;
    QLineEdit *pLine;
    QLabel *sLabel;
    QLabel *cLabel;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(761, 470);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setEnabled(true);
        pLabel = new QLabel(centralWidget);
        pLabel->setObjectName(QStringLiteral("pLabel"));
        pLabel->setGeometry(QRect(110, 60, 60, 21));
        QFont font;
        font.setPointSize(18);
        pLabel->setFont(font);
        pLabel->setTabletTracking(false);
        pLabel->setStyleSheet(QStringLiteral("color:black"));
        pBtn = new QPushButton(centralWidget);
        pBtn->setObjectName(QStringLiteral("pBtn"));
        pBtn->setGeometry(QRect(250, 55, 81, 41));
        QFont font1;
        font1.setPointSize(16);
        pBtn->setFont(font1);
        pBtn->setStyleSheet(QStringLiteral("color:balck"));
        pLine = new QLineEdit(centralWidget);
        pLine->setObjectName(QStringLiteral("pLine"));
        pLine->setGeometry(QRect(160, 60, 75, 24));
        pLine->setTabletTracking(true);
        pLine->setInputMethodHints(Qt::ImhDigitsOnly);
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
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setEnabled(false);
        menuBar->setGeometry(QRect(0, 0, 761, 25));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        pLabel->setText(QApplication::translate("MainWindow", "Port", nullptr));
        pBtn->setText(QApplication::translate("MainWindow", "listen", nullptr));
        sLabel->setText(QApplication::translate("MainWindow", "Server", nullptr));
        cLabel->setText(QApplication::translate("MainWindow", "Client", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
