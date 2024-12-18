#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void on_addPatientButton_clicked();
    void on_editPatientButton_clicked();
    void on_deletePatientButton_clicked();

private slots:
    void openFile();
    void openLastFile();
    void saveFile();
    void saveFileAs();
    void exitApplication();

private:
    Ui::MainWindow *ui;
    QString currentFile; // Для хранения пути к последнему открытому/сохранённому файлу

    void loadFile(const QString &fileName);
    void writeToFile(const QString &fileName);
};
#endif // MAINWINDOW_H
