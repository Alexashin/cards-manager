#include "patient.h"
#include <QStringList>

Patient::Patient(const QString &surname,
                 const QString &name,
                 const QString &patronymic,
                 unsigned short birthYear,
                 unsigned short height,
                 unsigned short weight,
                 const QString &notes)
    : surname(surname)
    , name(name)
    , patronymic(patronymic)
    , birthYear(birthYear)
    , height(height)
    , weight(weight)
    , notes(notes)
{}

// Getters
QString Patient::getSurname() const { return surname; }
QString Patient::getName() const { return name; }
QString Patient::getPatronymic() const { return patronymic; }
unsigned short Patient::getBirthYear() const { return birthYear; }
unsigned short Patient::getHeight() const { return height; }
unsigned short Patient::getWeight() const { return weight; }
QString Patient::getNotes() const { return notes; }

// Setters
void Patient::setSurname(const QString &surname) { this->surname = surname; }
void Patient::setName(const QString &name) { this->name = name; }
void Patient::setPatronymic(const QString &patronymic) { this->patronymic = patronymic; }
void Patient::setBirthYear(unsigned short year) { this->birthYear = year; }
void Patient::setHeight(unsigned short height) { this->height = height; }
void Patient::setWeight(unsigned short weight) { this->weight = weight; }
void Patient::setNotes(const QString &notes) { this->notes = notes; }

// Сериализация в строку CSV
QString Patient::toCSV() const
{
    return QString("%1,%2,%3,%4,%5,%6,%7")
        .arg(surname,
             name,
             patronymic,
             QString::number(birthYear),
             QString::number(height),
             QString::number(weight),
             notes);
}

// Десериализация из CSV строки
Patient Patient::fromCSV(const QString &csvLine)
{
    QStringList fields = csvLine.split(",");
    if (fields.size() == 7) {
        return Patient(fields[0],
                       fields[1],
                       fields[2],
                       fields[3].toUShort(),
                       fields[4].toUShort(),
                       fields[5].toUShort(),
                       fields[6]);
    }
    return Patient(); // Пустой объект в случае ошибки
}
