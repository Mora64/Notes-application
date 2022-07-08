#ifndef NOTEWINDOW_H
#define NOTEWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QPlainTextEdit>
#include "CustomColorPlaceholderLineEdit.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
namespace Ui {
class notewindow;
}

class notewindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit notewindow(QWidget *parent = nullptr);
    ~notewindow();
    void setTitle(QString title);
    void setContent(QString content);
    QString getTitle();
    QString getContent();


signals:
    void firstwindow();
    void applyClick(QString, QString);
    void cancelClick();
private slots:

    //void resizeTextEdit(const QSizeF& r);
    void applyClicked();
    void cancelClicked();


private:
    Ui::notewindow *ui;
    QPushButton* apply;
    QPushButton* cancel;

    CustomColorPlaceholderLineEdit* title;
    QPlainTextEdit* content;

    QVBoxLayout* textLayout;
    QHBoxLayout* buttons;

    QWidget *widget;
    QWidget *widget2;

    QHBoxLayout *mainLayout;
};

#endif // NOTEWINDOW_H
