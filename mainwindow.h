#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(
            QWidget *single_list_window,
            QWidget *splay_tree_window,
            QWidget *sort_demo_window,
            QWidget *parent = nullptr);
    ~MainWindow();

private:
    void onList();
    void onSplayTree();
    void onContainer();
    void onSet();
    void onSort();
    void onExit();

    QWidget *single_list_window = {nullptr};
    QWidget *splay_tree_window = {nullptr};
    QWidget *sort_demo_window = {nullptr};

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
