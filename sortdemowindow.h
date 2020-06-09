#ifndef SORTDEMOWINDOW_H
#define SORTDEMOWINDOW_H

#include <QDialog>
//#include <QPushButton>
#include <QTextBrowser>
#include <QLineEdit>
#include <QSpinBox>

#include <vector>
#include <data_scheme/CodeSample.h>

#include "modalmessagewindow.h"
#include "algorithms/rndtxt.h"

namespace Ui {
class SortDemoWindow;
}

class SortDemoWindow:public QDialog
{
    Q_OBJECT

public:
    explicit SortDemoWindow(QWidget *parent = nullptr);
    ~SortDemoWindow();

private:
    void onSort();
    void onShuffle();
    void onClear();
    void onAdd();
    void onRandom();

    void onOrganizationSelected();
    void onProjectSelected();
    void onComponentSelected();
    void onClassSelected();
    void onMethodSelected();
    void onAllFieldsSelected();

    void onSelectingAlg();
    void onQuickAlg();
    void onHeapAlg();
    void onRadixAlg();

    void fill_text_browser();

    QTextBrowser* text_browser = {nullptr};

    QLineEdit* org_edit = {nullptr};
    QLineEdit* proj_edit = {nullptr};
    QLineEdit* component_edit = {nullptr};
    QLineEdit* class_edit = {nullptr};
    QLineEdit* method_edit = {nullptr};

    QSpinBox* rnd_count = {nullptr};

    ModalMessageWindow* message_window = {nullptr};

    bool is_valid = {false};

    Ui::SortDemoWindow *ui;

    // ---------------

    std::vector<CodeSample> list;

    typedef bool(*CodeSample_Comparator)(const CodeSample&, const CodeSample&);
    CodeSample_Comparator comparator = {nullptr};

    enum algo_types{Select, Quick, Heap, Radix};
    algo_types algo = {Select};
};

#endif // SORTDEMOWINDOW_H
