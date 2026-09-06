/********************************************************************************
** Form generated from reading UI file 'VolunteerDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VOLUNTEERDIALOG_H
#define UI_VOLUNTEERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VolunteerDialog
{
public:
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *nameTextBox;
    QPushButton *submitButton;
    QPushButton *cancelButton_2;

    void setupUi(QDialog *VolunteerDialog)
    {
        if (VolunteerDialog->objectName().isEmpty())
            VolunteerDialog->setObjectName("VolunteerDialog");
        VolunteerDialog->resize(403, 312);
        formLayoutWidget = new QWidget(VolunteerDialog);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(100, 30, 201, 171));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(formLayoutWidget);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label);

        nameTextBox = new QLineEdit(formLayoutWidget);
        nameTextBox->setObjectName("nameTextBox");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, nameTextBox);

        submitButton = new QPushButton(formLayoutWidget);
        submitButton->setObjectName("submitButton");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, submitButton);

        cancelButton_2 = new QPushButton(formLayoutWidget);
        cancelButton_2->setObjectName("cancelButton_2");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, cancelButton_2);


        retranslateUi(VolunteerDialog);

        QMetaObject::connectSlotsByName(VolunteerDialog);
    } // setupUi

    void retranslateUi(QDialog *VolunteerDialog)
    {
        VolunteerDialog->setWindowTitle(QCoreApplication::translate("VolunteerDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("VolunteerDialog", "Namel", nullptr));
        submitButton->setText(QCoreApplication::translate("VolunteerDialog", "Submit", nullptr));
        cancelButton_2->setText(QCoreApplication::translate("VolunteerDialog", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VolunteerDialog: public Ui_VolunteerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VOLUNTEERDIALOG_H
