/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen_another_client;
    QAction *actionClose_this_client;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *messageLineEdit;
    QPushButton *sendMessageButton;
    QPushButton *privateMessageSendButton;
    QSplitter *splitter;
    QTextBrowser *commonChatBrowser;
    QTextBrowser *privateChatBrowser;
    QMenuBar *menubar;
    QMenu *menuMain_Menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(833, 717);
        actionOpen_another_client = new QAction(MainWindow);
        actionOpen_another_client->setObjectName(QString::fromUtf8("actionOpen_another_client"));
        actionClose_this_client = new QAction(MainWindow);
        actionClose_this_client->setObjectName(QString::fromUtf8("actionClose_this_client"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        messageLineEdit = new QLineEdit(centralwidget);
        messageLineEdit->setObjectName(QString::fromUtf8("messageLineEdit"));

        horizontalLayout->addWidget(messageLineEdit);

        sendMessageButton = new QPushButton(centralwidget);
        sendMessageButton->setObjectName(QString::fromUtf8("sendMessageButton"));

        horizontalLayout->addWidget(sendMessageButton);

        privateMessageSendButton = new QPushButton(centralwidget);
        privateMessageSendButton->setObjectName(QString::fromUtf8("privateMessageSendButton"));

        horizontalLayout->addWidget(privateMessageSendButton);


        verticalLayout->addLayout(horizontalLayout);

        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        commonChatBrowser = new QTextBrowser(splitter);
        commonChatBrowser->setObjectName(QString::fromUtf8("commonChatBrowser"));
        splitter->addWidget(commonChatBrowser);
        privateChatBrowser = new QTextBrowser(splitter);
        privateChatBrowser->setObjectName(QString::fromUtf8("privateChatBrowser"));
        splitter->addWidget(privateChatBrowser);

        verticalLayout->addWidget(splitter);

        verticalLayout->setStretch(1, 1);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 833, 32));
        menuMain_Menu = new QMenu(menubar);
        menuMain_Menu->setObjectName(QString::fromUtf8("menuMain_Menu"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuMain_Menu->menuAction());
        menuMain_Menu->addAction(actionOpen_another_client);
        menuMain_Menu->addSeparator();
        menuMain_Menu->addAction(actionClose_this_client);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionOpen_another_client->setText(QApplication::translate("MainWindow", "Open another client", nullptr));
        actionClose_this_client->setText(QApplication::translate("MainWindow", "Close this client", nullptr));
        label->setText(QApplication::translate("MainWindow", "Your Message:", nullptr));
        sendMessageButton->setText(QApplication::translate("MainWindow", "Send to All", nullptr));
        privateMessageSendButton->setText(QApplication::translate("MainWindow", "Send Private", nullptr));
        menuMain_Menu->setTitle(QApplication::translate("MainWindow", "Main Menu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
