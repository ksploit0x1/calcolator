#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "history.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    History<QString> history;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void set_line_edite_value(const QString value);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_actionCopy_triggered();

    void on_actionPast_triggered();

    void on_actionQuit_triggered();

    void on_actionAbout_triggered();

private:
    void calculate(QString expression);
    void undo();
    void redo();
    void clear();
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
