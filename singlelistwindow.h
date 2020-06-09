#ifndef SINGLELISTWINDOW_H
#define SINGLELISTWINDOW_H

#include <QDialog>
#include <QTextBrowser>
#include <QLineEdit>
//#include <QPushButton>

#include "modalmessagewindow.h"
#include "data_scheme/CodeSample.h"
#include "data_scheme/SingleLinkedList.h"

namespace Ui {
class SingleListWindow;
}

class SingleListWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SingleListWindow(QWidget *parent = nullptr);
    ~SingleListWindow();

private:
    void onAdd();
    void onRandom();
    void onErase();

    void fill_text_browser();

    QTextBrowser* text_browser = {nullptr};

    QLineEdit* org_edit = {nullptr};
    QLineEdit* proj_edit = {nullptr};
    QLineEdit* component_edit = {nullptr};
    QLineEdit* class_edit = {nullptr};
    QLineEdit* method_edit = {nullptr};

    QLineEdit* index_edit = {nullptr};

    bool is_valid = {false};

    ModalMessageWindow* message_window = {nullptr};

    SingleLinkedList<CodeSample> list;

    Ui::SingleListWindow *ui;
};

#endif // SINGLELISTWINDOW_H
