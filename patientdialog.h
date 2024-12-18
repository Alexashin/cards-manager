#ifndef PATIENTDIALOG_H
#define PATIENTDIALOG_H

#include <QDialog>
#include "patient.h"

namespace Ui {
class PatientDialog;
}

class PatientDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PatientDialog(QWidget *parent = nullptr);
    ~PatientDialog();

    void setPatient(const Patient &patient);
    Patient getPatient() const;

private:
    Ui::PatientDialog *ui;
};

#endif // PATIENTDIALOG_H
