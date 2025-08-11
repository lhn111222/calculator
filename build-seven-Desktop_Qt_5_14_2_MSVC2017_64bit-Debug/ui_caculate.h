/********************************************************************************
** Form generated from reading UI file 'caculate.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CACULATE_H
#define UI_CACULATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Caculate
{
public:

    void setupUi(QWidget *Caculate)
    {
        if (Caculate->objectName().isEmpty())
            Caculate->setObjectName(QString::fromUtf8("Caculate"));
        Caculate->resize(800, 600);

        retranslateUi(Caculate);

        QMetaObject::connectSlotsByName(Caculate);
    } // setupUi

    void retranslateUi(QWidget *Caculate)
    {
        Caculate->setWindowTitle(QCoreApplication::translate("Caculate", "Caculate", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Caculate: public Ui_Caculate {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CACULATE_H
