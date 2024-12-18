#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include "patientdialog.h"
#include "patient.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , isDataModified(false)
{
    ui->setupUi(this);

    ui->generalTable->setColumnCount(7);
    ui->generalTable->setHorizontalHeaderLabels({
        "Фамилия", "Имя", "Отчество", "Год рождения", "Рост", "Вес", "Заметки"
    });
    ui->generalTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->generalTable->setSortingEnabled(true);

    connect(ui->addPatientButton, &QPushButton::clicked, this, &MainWindow::handleAddPatient);
    connect(ui->editPatientButton, &QPushButton::clicked, this, &MainWindow::handleEditPatient);
    connect(ui->deletePatientButton, &QPushButton::clicked, this, &MainWindow::handleDeletePatient);
    connect(ui->openFileActionButton, &QAction::triggered, this, &MainWindow::openFile);
    connect(ui->openLastActionButton, &QAction::triggered, this, &MainWindow::openLastFile);
    connect(ui->saveActionButton, &QAction::triggered, this, &MainWindow::saveFile);
    connect(ui->saveAsActionButton, &QAction::triggered, this, &MainWindow::saveFileAs);
    connect(ui->exitActionButton, &QAction::triggered, this, &QApplication::quit);
    connect(ui->searchLineEdit, &QLineEdit::textChanged, this, &MainWindow::handleSearch);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if (isDataModified) {
        QMessageBox::StandardButton confirm = QMessageBox::question(
            this, "Выход из программы",
            "Есть несохранённые изменения. Вы уверены, что хотите выйти?",
            QMessageBox::Yes | QMessageBox::No);

        if (confirm == QMessageBox::No) {
            event->ignore();
            return;
        }
    }
    event->accept();
}

void MainWindow::handleAddPatient() {
    PatientDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {
        Patient newPatient = dialog.getPatient();
        int row = ui->generalTable->rowCount();
        ui->generalTable->insertRow(row);

        ui->generalTable->setItem(row, 0, new QTableWidgetItem(newPatient.getSurname()));
        ui->generalTable->setItem(row, 1, new QTableWidgetItem(newPatient.getName()));
        ui->generalTable->setItem(row, 2, new QTableWidgetItem(newPatient.getPatronymic()));
        ui->generalTable->setItem(row, 3, new QTableWidgetItem(QString::number(newPatient.getBirthYear())));
        ui->generalTable->setItem(row, 4, new QTableWidgetItem(QString::number(newPatient.getHeight())));
        ui->generalTable->setItem(row, 5, new QTableWidgetItem(QString::number(newPatient.getWeight())));
        ui->generalTable->setItem(row, 6, new QTableWidgetItem(newPatient.getNotes()));

        isDataModified = true;
    }
    handleSearch(ui->searchLineEdit->text());
}

void MainWindow::handleEditPatient() {
    int row = ui->generalTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Ошибка", "Выберите пациента для редактирования");
        return;
    }

    Patient patient(
        ui->generalTable->item(row, 0)->text(),
        ui->generalTable->item(row, 1)->text(),
        ui->generalTable->item(row, 2)->text(),
        ui->generalTable->item(row, 3)->text().toUShort(),
        ui->generalTable->item(row, 4)->text().toUShort(),
        ui->generalTable->item(row, 5)->text().toUShort(),
        ui->generalTable->item(row, 6)->text()
        );

    PatientDialog dialog(this);
    dialog.setPatient(patient);

    if (dialog.exec() == QDialog::Accepted) {
        Patient updatedPatient = dialog.getPatient();
        ui->generalTable->item(row, 0)->setText(updatedPatient.getSurname());
        ui->generalTable->item(row, 1)->setText(updatedPatient.getName());
        ui->generalTable->item(row, 2)->setText(updatedPatient.getPatronymic());
        ui->generalTable->item(row, 3)->setText(QString::number(updatedPatient.getBirthYear()));
        ui->generalTable->item(row, 4)->setText(QString::number(updatedPatient.getHeight()));
        ui->generalTable->item(row, 5)->setText(QString::number(updatedPatient.getWeight()));
        ui->generalTable->item(row, 6)->setText(updatedPatient.getNotes());

        isDataModified = true;
    }

    handleSearch(ui->searchLineEdit->text());
}

void MainWindow::handleDeletePatient() {
    int row = ui->generalTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Ошибка", "Выберите пациента для удаления");
        return;
    }

    QMessageBox::StandardButton confirm = QMessageBox::question(
        this, "Удаление пациента",
        "Вы уверены, что хотите удалить этого пациента?",
        QMessageBox::Yes | QMessageBox::No);

    if (confirm == QMessageBox::Yes) {
        ui->generalTable->removeRow(row);
        isDataModified = true;
    }
}

void MainWindow::openFile() {
    if (isDataModified) {
        QMessageBox::StandardButton confirm = QMessageBox::question(
            this, "Открытие файла",
            "Есть несохранённые изменения. Вы уверены, что хотите открыть новый файл?",
            QMessageBox::Yes | QMessageBox::No);

        if (confirm == QMessageBox::No) {
            return;
        }
    }

    QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл", "", "CSV files (*.csv)");
    if (fileName.isEmpty()) return;

    currentFile = fileName;
    loadFile(fileName);
    isDataModified = false;
}

void MainWindow::openLastFile() {
    if (currentFile.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Нет последнего открытого файла.");
        return;
    }
    loadFile(currentFile);
}

void MainWindow::saveFile() {
    if (currentFile.isEmpty()) {
        saveFileAs();
    } else {
        writeToFile(currentFile);
        isDataModified = false;
    }

}

void MainWindow::saveFileAs() {
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить файл как", "", "CSV files (*.csv)");
    if (fileName.isEmpty()) return;

    currentFile = fileName;
    writeToFile(fileName);
    isDataModified = false;
}

void MainWindow::writeToFile(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для записи.");
        return;
    }

    QTextStream out(&file);
    for (int row = 0; row < ui->generalTable->rowCount(); ++row) {
        QStringList rowData;
        for (int col = 0; col < ui->generalTable->columnCount(); ++col) {
            QTableWidgetItem *item = ui->generalTable->item(row, col);
            rowData << (item ? item->text() : "");
        }
        out << rowData.join(",") << "\n";
    }
    file.close();
}

void MainWindow::loadFile(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для чтения.");
        return;
    }

    ui->generalTable->setRowCount(0);
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");
        if (fields.size() != ui->generalTable->columnCount()) {
            QMessageBox::warning(this, "Ошибка", "Некорректный формат файла CSV.");
            return;
        }

        int row = ui->generalTable->rowCount();
        ui->generalTable->insertRow(row);
        for (int col = 0; col < fields.size(); ++col) {
            ui->generalTable->setItem(row, col, new QTableWidgetItem(fields[col]));
        }
    }
    file.close();
    QMessageBox::information(this, "Успех", "Файл успешно загружен.");
}

void MainWindow::handleSearch(const QString &query) {
    for (int row = 0; row < ui->generalTable->rowCount(); ++row) {
        bool match = false;
        for (int col = 0; col < ui->generalTable->columnCount(); ++col) {
            QTableWidgetItem *item = ui->generalTable->item(row, col);
            if (item && item->text().contains(query, Qt::CaseInsensitive)) {
                match = true;
                break;
            }
        }
        ui->generalTable->setRowHidden(row, !match); // Скрываем строки, не соответствующие запросу
    }
}
