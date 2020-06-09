#include "splaytreewindow.h"
#include "ui_splaytreewindow.h"

#include <QPicture>
#include <QPainter>
#include <QLabel>

namespace
{
    static int canvas_X = 20;
    static int canvas_Y = 70;
    static int canvas_W = 910;
    static int canvas_H = 470;

    static int node_W = 30;
    static int node_H = 20;

    static int v_gape = 60;
}

SplayTreeWindow::SplayTreeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SplayTreeWindow)
{
    ui->setupUi(this);

    add_edit = findChild<QLineEdit*>("addField");
    search_edit = findChild<QLineEdit*>("searchField");
    erase_edit = findChild<QLineEdit*>("eraseField");
    is_valid = add_edit && search_edit && erase_edit;

    connect(findChild<QPushButton*>("addBtn"),
            &QPushButton::pressed, this, &SplayTreeWindow::onAdd);
    connect(findChild<QPushButton*>("searchBtn"),
            &QPushButton::pressed, this, &SplayTreeWindow::onSearch);
    connect(findChild<QPushButton*>("eraseBtn"),
            &QPushButton::pressed, this, &SplayTreeWindow::onErase);

    message_window = new ModalMessageWindow(this);
}

SplayTreeWindow::~SplayTreeWindow()
{
    delete ui;
}

bool SplayTreeWindow::getNum(QLineEdit* edit, int& num)
{
    try
    {
        size_t err_pos = {0};
        std::string str = edit->text().toStdString();
        num = std::stoi(str, &err_pos);
        if (err_pos != str.length())
        {
            message_window->message("'Value' is not a number");
            message_window->exec();
            return false;
        }
    } catch(...) {
        message_window->message("Can't convert value to a number");
        message_window->exec();
        return false;
    }

    return true;
}

void SplayTreeWindow::onAdd()
{
    if (!is_valid)
        return;

    int num = {-1};
    if (getNum(add_edit, num))
    {
        root = tree.insert(num, root);
        //tree.show(root);
        draw_tree();
    }
}

void SplayTreeWindow::onSearch()
{
    if (!is_valid)
        return;

    int num = {-1};
    if (getNum(search_edit, num))
    {
        std::cout << "Search: " << num << std::endl;
        T_Node* node = tree.search(num, root);
        if (!node)
        {
            message_window->message("There is no node with specified key");
            message_window->exec();
        }
        draw_tree(node);
    }
}

void SplayTreeWindow::onErase()
{
    if (!is_valid)
        return;

    int num = {-1};
    if (getNum(erase_edit, num))
    {
        std::cout << "Erase: " << num << std::endl;
        root = tree.erase(num, root);
        draw_tree();
    }
}

void SplayTreeWindow::draw_tree(T_Node* spec)
{
    // ------------------------------

    if (pic_label)
    {
        pic_label->setParent(nullptr);
        delete pic_label;
    }
    for (auto& key : keys)
    {
        key->setParent(nullptr);
        delete key;
    }
    keys.clear();

    // ------------------------------

    QPicture pic;
    QPainter* painter = new QPainter(&pic);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap));
    painter->drawLine(0, 0, canvas_W, 0);
    painter->drawLine(canvas_W, 0, canvas_W, canvas_H);
    painter->drawLine(canvas_W, canvas_H, 0, canvas_H);
    painter->drawLine(0, canvas_H, 0, 0);

    // ------------------------------

    draw_all_nodes(painter, root, 0, 1, spec);

    // ------------------------------

    painter->end();

    pic_label = new QLabel(this);
    pic_label->setPicture(pic);
    pic_label->move(canvas_X, canvas_Y);
    pic_label->resize(QSize(canvas_W, canvas_H));
    pic_label->show();
    pic_label->lower();
}

void SplayTreeWindow::draw_all_nodes(QPainter* painter, T_Node* node, int k, int h, T_Node* spec)
{
    static int magic_num = 20;
    if (node)
    {
        int q = canvas_W / (2 << (h-1)); // 2^(h-1);
        if (h > 1)
        {
            // line to parent node
            int p_k = k / 2;
            int p_h = h - 1;
            int p_q = canvas_W / (2 << (p_h-1)); // 2^(p_h-1);
            painter->drawLine(q + 2*q * k, h * v_gape - magic_num - node_H/2,
                              p_q + 2*p_q * p_k, p_h * v_gape - magic_num + node_H/2);
        }
        draw_node(painter, q + 2*q * k, h * v_gape - magic_num, node->number, (node == spec));
        draw_all_nodes(painter, node->left, k*2, h+1, spec);
        draw_all_nodes(painter, node->right, k*2+1, h+1, spec);
    }
}

void SplayTreeWindow::draw_node(QPainter* painter, int x, int y, int key, bool selected)
{
    if (selected)
        painter->setPen(QPen(Qt::black, 3, Qt::DotLine, Qt::RoundCap));

    QLabel* key_label = new QLabel(this);
    key_label->move(QPoint(canvas_X + x - node_W / 2,
                           canvas_Y + y - node_H / 2));
    key_label->setText(std::to_string(key).c_str());
    key_label->resize(QSize(node_W, node_H));
    key_label->setAlignment(Qt::AlignmentFlag::AlignHCenter |
                            Qt::AlignmentFlag::AlignVCenter);
    key_label->show();

    keys.push_back(key_label);

    painter->drawRect(QRect(QPoint(x - node_W / 2, y - node_H / 2),
                            QSize(node_W, node_H)));

    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap));
}
