#include "notewindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <vector>
#include <QString>
#include <map>
#include<QScrollArea>
using namespace std;
map<QPushButton*, notewindow*> map1;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    noteWindow = new notewindow();
    //connects
    connect(noteWindow, &notewindow::firstwindow, this, &MainWindow::show);
    connect(noteWindow,&notewindow::applyClick, this, &MainWindow::apply);
    connect(newNotes, SIGNAL(clicked()), SLOT(on_newNotes_click()));


    //Layouts inicalization
    mainLayout = new QHBoxLayout;
    leftNotesLayout = new QVBoxLayout;
    allNotes = new QVBoxLayout;
    QVBoxLayout *rightAddNotesLayout = new QVBoxLayout;

    // make central widget
    QWidget *widget = new QWidget();
    widget->setLayout(mainLayout);
    setCentralWidget(widget);


    // add layout to main layout
    mainLayout->addLayout(leftNotesLayout);
    mainLayout->addLayout(rightAddNotesLayout);
    //left layout

    QLabel* yourNotes = new QLabel;
    yourNotes->setText("Your Notes: ");
    leftNotesLayout->addWidget(yourNotes);
    leftNotesLayout->addLayout(allNotes);
    leftNotesLayout->addStretch(1);

    //right layout

    newNotes->setFixedSize(60,60);
    newNotes->setText("+");

    rightAddNotesLayout->addStretch(1);
    rightAddNotesLayout->addWidget(newNotes);
    //style sheets
    yourNotes->setStyleSheet("font-size:25px; font-weight:bold; color:white;");
    newNotes->setStyleSheet("background-color:orange;color:white; border-radius:30px; font-size:30px");
    this->setStyleSheet("background-color:#323437;");
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_newNotes_click(){
    noteWindow->setTitle("");
    noteWindow->setContent("");
    noteWindow->show();
    this->close();
}

void MainWindow::apply(QString title, QString content)
{
    notewindow* ourNotes = new notewindow;
    ourNotes->setTitle(title);
    ourNotes->setContent(content);
    temp_title = ourNotes->getTitle();
    temp_content = ourNotes->getContent();
    QPushButton* ourButton = new QPushButton;
    ourButton->setText(title);
    ourButton->setStyleSheet("background:transparent; Text-align:left; font-size:20px; font-weight:bold; color:white;");
    map1.insert(make_pair(ourButton,ourNotes));
    connect(ourNotes, &notewindow::firstwindow, this, &MainWindow::show);
    connect(ourNotes,&notewindow::applyClick, this, &MainWindow::applyToEdit);
    connect(ourNotes,&notewindow::cancelClick, this, &MainWindow::cancelEdit);
    connect(ourButton, SIGNAL(clicked()), this, SLOT(showNotes()));
    allNotes->addWidget(ourButton,0);

}

void MainWindow::applyToEdit(QString title, QString content)
{
    notewindow* sen = qobject_cast<notewindow*> (sender());
    sen->setTitle(title);
    sen->setContent(content);
    temp_title = sen->getTitle();
    temp_content = sen->getContent();
    for(auto it = map1.begin(); it != map1.end(); ++it) {
            if(it->second == sen){
                it->first->setText(title);
                break;
            }
    }
}

void MainWindow::showNotes(){
    QPushButton *sen = qobject_cast<QPushButton*> (sender());
    auto it = map1.find(sen);
    it->second->show();

}

void MainWindow::cancelEdit()
{
    notewindow* sen = qobject_cast<notewindow*> (sender());
    sen->setTitle(temp_title);
    sen->setContent(temp_content);
}

