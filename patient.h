#ifndef PATIENT_H
#define PATIENT_H

#include <QString>

class Patient
{
public:
    Patient(const QString &surname = "", const QString &name = "",
            const QString &patronymic = "", unsigned short birthYear = 0,
            unsigned short height = 0, unsigned short weight = 0, const QString &notes = "");

    // Getters
    QString getSurname() const;
    QString getName() const;
    QString getPatronymic() const;
    unsigned short getBirthYear() const;
    unsigned short getHeight() const;
    unsigned short getWeight() const;
    QString getNotes() const;

    // Setters
    void setSurname(const QString &surname);
    void setName(const QString &name);
    void setPatronymic(const QString &patronymic);
    void setBirthYear(unsigned short year);
    void setHeight(unsigned short height);
    void setWeight(unsigned short weight);
    void setNotes(const QString &notes);

    // Saving
    QString toCSV() const;

    // Reading
    static Patient fromCSV(const QString &csvLine);

private:
    QString surname;
    QString name;
    QString patronymic;
    unsigned short birthYear;
    unsigned short height;
    unsigned short weight;
    QString notes;
};

#endif // PATIENT_H
