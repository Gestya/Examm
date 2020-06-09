#ifndef SPLAYTREEWINDOW_H
#define SPLAYTREEWINDOW_H

#include <QMainWindow>
#include <QSlider>
#include <QLineEdit>
#include <QLabel>
#include <QPainter>
#include <QPicture>

#include <vector>

#include "modalmessagewindow.h"

#include "data_scheme/SplayTree.h"

namespace Ui {
class SplayTreeWindow;
}

class SplayTreeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SplayTreeWindow(QWidget *parent = nullptr);
    ~SplayTreeWindow();

private:
    void onAdd();
    void onSearch();
    void onErase();

    bool getNum(QLineEdit* edit, int& num);

    void draw_tree(T_Node* spec = nullptr);
    void draw_all_nodes(QPainter* painter, T_Node* node, int k, int h, T_Node* spec = nullptr);
    void draw_node(QPainter* painter, int x, int y, int key, bool selected = false);

    QLineEdit* add_edit = {nullptr};
    QLineEdit* search_edit = {nullptr};
    QLineEdit* erase_edit = {nullptr};
    bool is_valid = {false};

    ModalMessageWindow* message_window = {nullptr};

    QLabel* pic_label = {nullptr};
    std::vector<QLabel*> keys;

    SplayTree tree;
    T_Node* root = {nullptr};

    Ui::SplayTreeWindow *ui;
};

#endif // SPLAYTREEWINDOW_H
