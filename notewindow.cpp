#include "notewindow.h"
#include "ui_notewindow.h"
#include "CustomColorPlaceholderLineEdit.h"
#include "CustomColorPlaceholderLineEdit.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QString>

notewindow::notewindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::notewindow)
{
    ui->setupUi(this);


    mainLayout = new QHBoxLayout;
    textLayout = new QVBoxLayout;
    buttons = new QHBoxLayout;
    widget = new QWidget();
    widget2 = new QWidget();
    title = new CustomColorPlaceholderLineEdit;
    content = new QPlainTextEdit;
    cancel = new QPushButton;
    apply = new QPushButton;

    connect(apply, SIGNAL(clicked()), this, SLOT(applyClicked()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(cancelClicked()));

    // make central widget
    widget->setLayout(mainLayout);
    setCentralWidget(widget);


    //widget 2
    //widget2->setMaximumWidth(1050);
    widget2->setLayout(textLayout);
    mainLayout->addWidget(widget2, Qt::AlignCenter);

    //title
    title->setCustomPlaceholderText("Write Title");
    title->setCustomPlaceholderColor(qRgba(120,120,120,0));

   //content
    content->setMinimumHeight(550);
    content->setPlaceholderText("Type text");
    content->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    content->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    //buttons
    buttons->addWidget(cancel);
    buttons->addWidget(apply);
    cancel->setText("Cancel");
    apply->setText("Apply");

    //textLayout
    textLayout->addStretch(3);
    textLayout->addWidget(title);
    textLayout->addWidget(content);
    textLayout->addStretch(10);
    textLayout->addLayout(buttons);
    textLayout->addStretch(1);

    \


    //styleSheets
    this->setStyleSheet("background-color:#323437;");
    title->setStyleSheet("font-size:25px;color:#A7A7A7;font-weight:bold;border-width: 1px; border-style: none;");
    content->setStyleSheet("font-size:20px;color:#A7A7A7;border-width: 1px; border-style: none; border-style: solid; border-color:#A7A7A7 #323437 #323437 #323437 ;");
    QString button_css = "QPushButton {"
                          "border-style:none;"
                          "color:white;"
                          "font-size:20px;"
                          "}"
                         "QPushButton:hover {"
                             "color:orange;"
                         "}";


    cancel->setStyleSheet(button_css);
    apply->setStyleSheet(button_css);

}

void notewindow::setTitle(QString title){
    this->title->setText(title);
}
void notewindow::setContent(QString content){
    this->content->document()->setPlainText(content);
}

QString notewindow::getTitle()
{
    return this->title->text();
}

QString notewindow::getContent()
{
    return this->content->toPlainText();
}
notewindow::~notewindow()
{
    delete ui;
}


void notewindow::applyClicked()
{
    if(title->text().isEmpty()){
        emit applyClick("Untilted", content->document()->toPlainText());
    } else{
        emit applyClick(title->text(), content->document()->toPlainText());
    }
    emit firstwindow();
    this->close();
}

void notewindow::cancelClicked()
{
    emit cancelClick();
    emit firstwindow();
    this->close();
}

