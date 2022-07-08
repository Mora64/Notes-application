#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "notewindow.h"
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_newNotes_click();
public slots:
    void applyToEdit(QString title, QString content);
    void apply(QString title, QString content);
    void showNotes();
    void cancelEdit();

private:
    QPushButton* newNotes = new QPushButton;
    Ui::MainWindow *ui;
    notewindow* noteWindow;
    QVBoxLayout* allNotes;
    QHBoxLayout *mainLayout;
    QVBoxLayout *leftNotesLayout;
    QString temp_title;
    QString temp_content;
};
#endif // MAINWINDOW_H
