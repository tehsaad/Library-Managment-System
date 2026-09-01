/********************************************************************************
** Form generated from reading UI file 'issue_books.ui'
**
** Created by: Qt User Interface Compiler version 6.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ISSUE_BOOKS_H
#define UI_ISSUE_BOOKS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>

QT_BEGIN_NAMESPACE

class Ui_add_Books
{
public:
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *add_Books)
    {
        if (add_Books->objectName().isEmpty())
            add_Books->setObjectName("add_Books");
        add_Books->resize(400, 300);
        buttonBox = new QDialogButtonBox(add_Books);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        retranslateUi(add_Books);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, add_Books, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, add_Books, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(add_Books);
    } // setupUi

    void retranslateUi(QDialog *add_Books)
    {
        add_Books->setWindowTitle(QCoreApplication::translate("add_Books", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class add_Books: public Ui_add_Books {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ISSUE_BOOKS_H
