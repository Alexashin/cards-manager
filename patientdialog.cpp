#include "patientdialog.h"
#include "ui_patientdialog.h"

PatientDialog::PatientDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PatientDialog)
{
    ui->setupUi(this);
}

PatientDialog::~PatientDialog()
{
    delete ui;
}

void PatientDialog::setPatient(const Patient &patient) {
    ui->secNameLineEdit->setText(patient.getSurname());
    ui->firstNameLineEdit->setText(patient.getName());
    ui->patronymicLineEdit->setText(patient.getPatronymic());
    ui->birthYearSpinBox->setValue(patient.getBirthYear());
    ui->heightSpinBox->setValue(patient.getHeight());
    ui->weightSpinBox->setValue(patient.getWeight());
    ui->noteTextEdit->setPlainText(patient.getNotes());
}

Patient PatientDialog::getPatient() const {
    return Patient(
        ui->secNameLineEdit->text(),
        ui->firstNameLineEdit->text(),
        ui->patronymicLineEdit->text(),
        static_cast<unsigned short>(ui->birthYearSpinBox->value()),
        static_cast<unsigned short>(ui->heightSpinBox->value()),
        static_cast<unsigned short>(ui->weightSpinBox->value()),
        ui->noteTextEdit->toPlainText()
        );
}
