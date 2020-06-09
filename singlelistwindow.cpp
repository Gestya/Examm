#include "singlelistwindow.h"
#include "ui_singlelistwindow.h"
#include "algorithms/rndtxt.h"

#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <iostream>

SingleListWindow::SingleListWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SingleListWindow)
{
    ui->setupUi(this);

    text_browser = findChild<QTextBrowser*>("textBrowser");

    org_edit = findChild<QLineEdit*>("orgEdit");
    proj_edit = findChild<QLineEdit*>("projEdit");
    component_edit = findChild<QLineEdit*>("componentEdit");
    class_edit = findChild<QLineEdit*>("classEdit");
    method_edit = findChild<QLineEdit*>("methodEdit");

    index_edit = findChild<QLineEdit*>("indexEdit");

    is_valid = text_browser
            && org_edit && proj_edit && component_edit && class_edit && method_edit
            && index_edit;

    connect(findChild<QPushButton*>("addButton"),
            &QPushButton::pressed, this, &SingleListWindow::onAdd);
    connect(findChild<QPushButton*>("randomButton"),
            &QPushButton::pressed, this, &SingleListWindow::onRandom);
    connect(findChild<QPushButton*>("eraseButton"),
            &QPushButton::pressed, this, &SingleListWindow::onErase);

    message_window = new ModalMessageWindow(this);
}

SingleListWindow::~SingleListWindow()
{
    delete ui;
}

void SingleListWindow::onAdd()
{
    if (!is_valid)
        return;

    CodeSample code_sample = {
        org_edit->text().toStdString(),
        proj_edit->text().toStdString(),
        component_edit->text().toStdString(),
        class_edit->text().toStdString(),
        method_edit->text().toStdString()
    };

    if (!code_sample.wholly_filled())
    {
        message_window->message("All fields mustn't be empty");
        message_window->exec();
    }
    else
    {
        list.add(code_sample);
        fill_text_browser();
    }
}

void SingleListWindow::onRandom()
{
    if (!is_valid)
        return;

    CodeSample code_sample = {
        randomText(10,15),
        randomText(5,10) + "_" + randomText(5,10) + "_" + randomText(5,10),
        randomText(10,20),
        randomText(10,20),
        randomText(5,10,0) + randomText(5,10) + randomText(5,10)
    };
    list.add(code_sample);

    fill_text_browser();
}

void SingleListWindow::onErase()
{
    if (!is_valid)
        return;

    int ndx = {-1};
    try
    {
        size_t err_pos = {0};
        std::string str = index_edit->text().toStdString();
        ndx = std::stoi(str, &err_pos);
        if (err_pos != str.length())
        {
            message_window->message("'Index' is not a number");
            message_window->exec();
            return;
        }
    } catch(...) {
        message_window->message("Can't convert value of 'Index' to a number");
        message_window->exec();
        return;
    }

    if (list.erase(ndx))
    {
        fill_text_browser();
    }
    else
    {
        const std::string msg("Elementh with index " + std::to_string(ndx) + " does not exist");
        message_window->message(msg.c_str());
        message_window->exec();
    }
}

void SingleListWindow::fill_text_browser()
{
    if (!is_valid)
        return;

    size_t index_len = 1;
    size_t sz = list.size();
    if (sz)
        sz -= 1;
    while (sz > 9)
    {
        sz /= sz;
        index_len++;
    }

    size_t org_len = {0};
    size_t proj_len = {0};
    size_t component_len = {0};
    size_t class_len = {0};
    size_t method_len = {0};
    for (size_t i = 0; i < list.size(); ++i)
    {
        try {
            const auto cs = list.get(i);
            org_len = std::max<size_t>(cs.organization.length(), org_len);
            proj_len = std::max<size_t>(cs.project.length(), proj_len);
            component_len = std::max<size_t>(cs.component.length(), component_len);
            class_len = std::max<size_t>(cs.class_name.length(), class_len);
            method_len = std::max<size_t>(cs.method_name.length(), method_len);
        } catch (...) {
            const std::string msg("Elementh with index " + std::to_string(i) + " does not exist");
            message_window->message(msg.c_str());
            message_window->exec();
            text_browser->setText("---ERROR---");
            return;
        }

    }

    org_len += 2;
    proj_len += 2;
    component_len += 2;
    class_len += 2;

    std::stringstream s;
    for (size_t i = 0; i < list.size(); ++i)
    {
        try {
            const auto cs = list.get(i);
            s << std::right << std::setw(index_len) << i << " : ";
            s << std::left;
            s << std::setw(org_len) << cs.organization;
            s << std::setw(proj_len) << cs.project;
            s << std::setw(component_len) << cs.component;
            s << std::setw(class_len) << cs.class_name;
            s << std::setw(method_len) << cs.method_name;
            s << std::endl;
        } catch (...) {
            const std::string msg("Elementh with index " + std::to_string(i) + " does not exist");
            message_window->message(msg.c_str());
            text_browser->setText("---ERROR---");
            return;
        }
    }

    text_browser->setText( QString( s.str().c_str() ) );
}
