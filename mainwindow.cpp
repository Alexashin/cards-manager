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
{
    ui->setupUi(this);

    ui->generalTable->setColumnCount(7); // Устанавливаем количество колонок
    ui->generalTable->setHorizontalHeaderLabels({
        "Фамилия", "Имя", "Отчество", "Год рождения", "Рост", "Вес", "Заметки"
    });

    // Дополнительно можно задать растяжение колонок
    ui->generalTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(ui->addPatientButton, &QPushButton::clicked, this, &MainWindow::on_addPatientButton_clicked);
    connect(ui->editPatientButton, &QPushButton::clicked, this, &MainWindow::on_editPatientButton_clicked);
    connect(ui->deletePatientButton, &QPushButton::clicked, this, &MainWindow::on_deletePatientButton_clicked);

    connect(ui->openFileActionButton, &QAction::triggered, this, &MainWindow::openFile);
    connect(ui->openLastActionButton, &QAction::triggered, this, &MainWindow::openLastFile);
    connect(ui->saveActionButton, &QAction::triggered, this, &MainWindow::saveFile);
    connect(ui->saveAsActionButton, &QAction::triggered, this, &MainWindow::saveFileAs);
    connect(ui->exitActionButton, &QAction::triggered, this, &QApplication::quit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addPatientButton_clicked() {
    PatientDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {
        Patient newPatient = dialog.getPatient();
        int row = ui->generalTable->rowCount();
        ui->generalTable->insertRow(row);

        // Заполняем строку таблицы
        ui->generalTable->setItem(row, 0, new QTableWidgetItem(newPatient.getSurname()));
        ui->generalTable->setItem(row, 1, new QTableWidgetItem(newPatient.getName()));
        ui->generalTable->setItem(row, 2, new QTableWidgetItem(newPatient.getPatronymic()));
        ui->generalTable->setItem(row, 3, new QTableWidgetItem(QString::number(newPatient.getBirthYear())));
        ui->generalTable->setItem(row, 4, new QTableWidgetItem(QString::number(newPatient.getHeight())));
        ui->generalTable->setItem(row, 5, new QTableWidgetItem(QString::number(newPatient.getWeight())));
        ui->generalTable->setItem(row, 6, new QTableWidgetItem(newPatient.getNotes()));
    }
}

void MainWindow::on_editPatientButton_clicked() {
    int row = ui->generalTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Ошибка", "Выберите пациента для редактирования");
        return;
    }

    // Извлекаем данные из строки таблицы
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
    }
}

void MainWindow::on_deletePatientButton_clicked() {
    int row = ui->generalTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Ошибка", "Выберите пациента для удаления");
        return;
    }

    ui->generalTable->removeRow(row);
}


void MainWindow::openFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл", "", "CSV files (*.csv)");
    if (fileName.isEmpty()) return;

    currentFile = fileName; // Сохраняем путь к текущему файлу
    loadFile(fileName);
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
        QStringList fields = in.readLine().split(",");
        if (fields.size() == ui->generalTable->columnCount()) {
            int row = ui->generalTable->rowCount();
            ui->generalTable->insertRow(row);
            for (int col = 0; col < fields.size(); ++col) {
                ui->generalTable->setItem(row, col, new QTableWidgetItem(fields[col]));
            }
        }
    }
    file.close();
    QMessageBox::information(this, "Успех", "Файл успешно загружен.");
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
    }
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
    QMessageBox::information(this, "Успех", "Файл успешно сохранён.");
}

void MainWindow::saveFileAs() {
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить файл как", "", "CSV files (*.csv)");
    if (fileName.isEmpty()) return;

    currentFile = fileName; // Сохраняем путь к новому файлу
    writeToFile(fileName);
}

void MainWindow::exitApplication() {
    QApplication::quit();
}
