/********************************************************************************
** Form generated from reading UI file 'patientdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PATIENTDIALOG_H
#define UI_PATIENTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_PatientDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *secNameLineEdit;
    QTextEdit *noteTextEdit;
    QLabel *secNameLabel;
    QLabel *firstNameLabel;
    QLineEdit *firstNameLineEdit;
    QLabel *patronymicLabel;
    QLineEdit *patronymicLineEdit;
    QSpinBox *birthYearSpinBox;
    QLabel *birthYearLabel;
    QSpinBox *heightSpinBox;
    QLabel *heightLabel;
    QSpinBox *weightSpinBox;
    QLabel *weightLabel;
    QLabel *noteLabel;

    void setupUi(QDialog *PatientDialog)
    {
        if (PatientDialog->objectName().isEmpty())
            PatientDialog->setObjectName("PatientDialog");
        PatientDialog->resize(413, 498);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PatientDialog->sizePolicy().hasHeightForWidth());
        PatientDialog->setSizePolicy(sizePolicy);
        buttonBox = new QDialogButtonBox(PatientDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(40, 440, 341, 32));
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        secNameLineEdit = new QLineEdit(PatientDialog);
        secNameLineEdit->setObjectName("secNameLineEdit");
        secNameLineEdit->setGeometry(QRect(40, 60, 181, 28));
        noteTextEdit = new QTextEdit(PatientDialog);
        noteTextEdit->setObjectName("noteTextEdit");
        noteTextEdit->setGeometry(QRect(40, 280, 331, 131));
        secNameLabel = new QLabel(PatientDialog);
        secNameLabel->setObjectName("secNameLabel");
        secNameLabel->setGeometry(QRect(40, 30, 111, 20));
        firstNameLabel = new QLabel(PatientDialog);
        firstNameLabel->setObjectName("firstNameLabel");
        firstNameLabel->setGeometry(QRect(40, 100, 111, 20));
        firstNameLineEdit = new QLineEdit(PatientDialog);
        firstNameLineEdit->setObjectName("firstNameLineEdit");
        firstNameLineEdit->setGeometry(QRect(40, 130, 181, 28));
        patronymicLabel = new QLabel(PatientDialog);
        patronymicLabel->setObjectName("patronymicLabel");
        patronymicLabel->setGeometry(QRect(40, 170, 111, 20));
        patronymicLineEdit = new QLineEdit(PatientDialog);
        patronymicLineEdit->setObjectName("patronymicLineEdit");
        patronymicLineEdit->setGeometry(QRect(40, 200, 181, 28));
        birthYearSpinBox = new QSpinBox(PatientDialog);
        birthYearSpinBox->setObjectName("birthYearSpinBox");
        birthYearSpinBox->setGeometry(QRect(260, 60, 111, 29));
        birthYearSpinBox->setMinimum(1900);
        birthYearSpinBox->setMaximum(2100);
        birthYearLabel = new QLabel(PatientDialog);
        birthYearLabel->setObjectName("birthYearLabel");
        birthYearLabel->setGeometry(QRect(260, 30, 111, 20));
        heightSpinBox = new QSpinBox(PatientDialog);
        heightSpinBox->setObjectName("heightSpinBox");
        heightSpinBox->setGeometry(QRect(260, 130, 111, 29));
        heightSpinBox->setMaximum(300);
        heightLabel = new QLabel(PatientDialog);
        heightLabel->setObjectName("heightLabel");
        heightLabel->setGeometry(QRect(260, 100, 111, 20));
        weightSpinBox = new QSpinBox(PatientDialog);
        weightSpinBox->setObjectName("weightSpinBox");
        weightSpinBox->setGeometry(QRect(260, 200, 111, 29));
        weightSpinBox->setMaximum(500);
        weightLabel = new QLabel(PatientDialog);
        weightLabel->setObjectName("weightLabel");
        weightLabel->setGeometry(QRect(260, 170, 111, 20));
        noteLabel = new QLabel(PatientDialog);
        noteLabel->setObjectName("noteLabel");
        noteLabel->setGeometry(QRect(40, 250, 71, 20));

        retranslateUi(PatientDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, PatientDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, PatientDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(PatientDialog);
    } // setupUi

    void retranslateUi(QDialog *PatientDialog)
    {
        PatientDialog->setWindowTitle(QCoreApplication::translate("PatientDialog", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214/\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\277\320\260\321\206\320\270\320\265\320\275\321\202\320\260", nullptr));
        secNameLabel->setText(QCoreApplication::translate("PatientDialog", "\320\244\320\260\320\274\320\270\320\273\320\270\321\217", nullptr));
        firstNameLabel->setText(QCoreApplication::translate("PatientDialog", "\320\230\320\274\321\217", nullptr));
        patronymicLabel->setText(QCoreApplication::translate("PatientDialog", "\320\236\321\202\321\207\320\265\321\201\321\202\320\262\320\276", nullptr));
        birthYearLabel->setText(QCoreApplication::translate("PatientDialog", "\320\223\320\276\320\264 \321\200\320\276\320\266\320\264\320\265\320\275\320\270\321\217", nullptr));
        heightLabel->setText(QCoreApplication::translate("PatientDialog", "\320\240\320\276\321\201\321\202", nullptr));
        weightLabel->setText(QCoreApplication::translate("PatientDialog", "\320\222\320\265\321\201", nullptr));
        noteLabel->setText(QCoreApplication::translate("PatientDialog", "\320\227\320\260\320\274\320\265\321\202\320\272\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PatientDialog: public Ui_PatientDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PATIENTDIALOG_H
