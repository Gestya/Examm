#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPushButton"

MainWindow::MainWindow(
        QWidget *single_list_window,
        QWidget *splay_tree_window,
        QWidget *sort_demo_window,
        QWidget *parent)
    : QMainWindow(parent)
    , single_list_window(single_list_window)
    , splay_tree_window(splay_tree_window)
    , sort_demo_window(sort_demo_window)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
/*
    // Buttons
    QPushButton* list_button = findChild<QPushButton *>("listButton");
    connect(list_button, &QPushButton::pressed, this, &MainWindow::onList);
    QPushButton* splay_tree = findChild<QPushButton *>("splayTree");
    connect(splay_tree, &QPushButton::pressed, this, &MainWindow::onSplayTree);
    QPushButton* sort_button = findChild<QPushButton *>("sortButton");
    connect(sort_button, &QPushButton::pressed, this, &MainWindow::onSort);

    // Main menu
    QAction* actionList = findChild<QAction*>("actionList");
    connect(actionList, &QAction::triggered, this, &MainWindow::onList);
    QAction* actionSplayTree = findChild<QAction*>("actionSplayTree");
    connect(actionSplayTree, &QAction::triggered, this, &MainWindow::onSplayTree);
    QAction* actionSort = findChild<QAction*>("actionSort");
    connect(actionSort, &QAction::triggered, this, &MainWindow::onSort);
    QAction* actionExit = findChild<QAction*>("actionExit");
    connect(actionExit, &QAction::triggered, this, &MainWindow::onExit);
    */

    // Main menu
    connect(findChild<QAction*>("actionList"),
            &QAction::triggered, this, &MainWindow::onList);
    connect(findChild<QAction*>("actionSplayTree"),
            &QAction::triggered, this, &MainWindow::onSplayTree);
    connect(findChild<QAction*>("actionSort"),
            &QAction::triggered, this, &MainWindow::onSort);
    connect(findChild<QAction*>("actionExit"),
            &QAction::triggered, this, &MainWindow::onExit);

    // Buttons
    connect(findChild<QPushButton *>("listButton"),
            &QPushButton::pressed, this, &MainWindow::onList);
    connect(findChild<QPushButton *>("splayTree"),
            &QPushButton::pressed, this, &MainWindow::onSplayTree);
    connect(findChild<QPushButton *>("sortButton"),
            &QPushButton::pressed, this, &MainWindow::onSort);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onList()
{
    if (single_list_window)
        single_list_window->setVisible(true);
}

void MainWindow::onSplayTree()
{
    if (splay_tree_window)
        splay_tree_window->setVisible(true);
}

void MainWindow::onContainer()
{

}

void MainWindow::onSet()
{

}

void MainWindow::onSort()
{
    if (sort_demo_window)
        sort_demo_window->setVisible(true);
}

void MainWindow::onExit()
{
    exit(0);
}

