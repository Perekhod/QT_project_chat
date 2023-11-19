/********************************************************************************
** Form generated from reading UI file 'startscreen.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTSCREEN_H
#define UI_STARTSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QStackedWidget>
#include "loginform.h"
#include "registrationform.h"

QT_BEGIN_NAMESPACE

class Ui_StartScreen
{
public:
    QStackedWidget *stackedWidget;
    LoginForm *loginWidget;
    RegistrationForm *registerWidget;

    void setupUi(QDialog *StartScreen)
    {
        if (StartScreen->objectName().isEmpty())
            StartScreen->setObjectName(QString::fromUtf8("StartScreen"));
        StartScreen->resize(815, 629);
        stackedWidget = new QStackedWidget(StartScreen);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(210, 160, 351, 301));
        loginWidget = new LoginForm();
        loginWidget->setObjectName(QString::fromUtf8("loginWidget"));
        stackedWidget->addWidget(loginWidget);
        registerWidget = new RegistrationForm();
        registerWidget->setObjectName(QString::fromUtf8("registerWidget"));
        stackedWidget->addWidget(registerWidget);

        retranslateUi(StartScreen);

        QMetaObject::connectSlotsByName(StartScreen);
    } // setupUi

    void retranslateUi(QDialog *StartScreen)
    {
        StartScreen->setWindowTitle(QApplication::translate("StartScreen", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StartScreen: public Ui_StartScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTSCREEN_H
