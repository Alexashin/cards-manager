#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>

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

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void handleAddPatient();
    void handleEditPatient();
    void handleDeletePatient();
    void openFile();
    void openLastFile();
    void saveFile();
    void saveFileAs();
    void handleSearch(const QString &query);

private:
    Ui::MainWindow *ui;
    QString currentFile;
    bool isDataModified;
    void loadFile(const QString &fileName);
    void writeToFile(const QString &fileName);
};

#endif // MAINWINDOW_H
