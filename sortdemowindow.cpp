#include "sortdemowindow.h"
#include "ui_sortdemowindow.h"
#include "algorithms/rndtxt.h"
#include "algorithms/selectingsort.h"
#include "algorithms/quicksort.h"

#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cstdlib>

#include <chrono>
using std::chrono::milliseconds;
using std::chrono::duration_cast;
using std::chrono::system_clock;

#include <iostream> // debug

SortDemoWindow::SortDemoWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SortDemoWindow)
{
    ui->setupUi(this);

    text_browser = findChild<QTextBrowser*>("textBrowser");

    org_edit = findChild<QLineEdit*>("orgEdit");
    proj_edit = findChild<QLineEdit*>("projEdit");
    component_edit = findChild<QLineEdit*>("componentEdit");
    class_edit = findChild<QLineEdit*>("classEdit");
    method_edit = findChild<QLineEdit*>("methodEdit");
    // selectAlg
    // quickAlg

    rnd_count = findChild<QSpinBox*>("rndCount");

    is_valid = text_browser
            && org_edit && proj_edit && component_edit && class_edit && method_edit
            && rnd_count;

    // --------------------------------------

    connect(findChild<QPushButton*>("sortButton"),
            &QPushButton::pressed, this, &SortDemoWindow::onSort);
    connect(findChild<QPushButton*>("shuffleButton"),
            &QPushButton::pressed, this, &SortDemoWindow::onShuffle);
    connect(findChild<QPushButton*>("randomButton"),
            &QPushButton::pressed, this, &SortDemoWindow::onRandom);
    connect(findChild<QPushButton*>("clearButton"),
            &QPushButton::pressed, this, &SortDemoWindow::onClear);
    connect(findChild<QPushButton*>("addButton"),
            &QPushButton::pressed, this, &SortDemoWindow::onAdd);

    // --------------------------------------

    connect(findChild<QRadioButton*>("orgField"),
            &QRadioButton::pressed, this, &SortDemoWindow::onOrganizationSelected);
    connect(findChild<QRadioButton*>("projField"),
            &QRadioButton::pressed, this, &SortDemoWindow::onProjectSelected);
    connect(findChild<QRadioButton*>("componentField"),
            &QRadioButton::pressed, this, &SortDemoWindow::onComponentSelected);
    connect(findChild<QRadioButton*>("classField"),
            &QRadioButton::pressed, this, &SortDemoWindow::onClassSelected);
    connect(findChild<QRadioButton*>("methodField"),
            &QRadioButton::pressed, this, &SortDemoWindow::onMethodSelected);
    connect(findChild<QRadioButton*>("allFields"),
            &QRadioButton::pressed, this, &SortDemoWindow::onAllFieldsSelected);

    // --------------------------------------

    connect(findChild<QRadioButton*>("selectAlg"),
            &QRadioButton::pressed, this, &SortDemoWindow::onSelectingAlg);
    connect(findChild<QRadioButton*>("quickAlg"),
            &QRadioButton::pressed, this, &SortDemoWindow::onQuickAlg);
    connect(findChild<QRadioButton*>("heapAlg"),
            &QRadioButton::pressed, this, &SortDemoWindow::onHeapAlg);
    connect(findChild<QRadioButton*>("radixAlg"),
            &QRadioButton::pressed, this, &SortDemoWindow::onRadixAlg);

    // --------------------------------------

    message_window = new ModalMessageWindow(this);

    onAllFieldsSelected(); // init a pointer to a comporation function
}

SortDemoWindow::~SortDemoWindow()
{
    delete ui;
}

void SortDemoWindow::onSort()
{
    if (!is_valid)
        return;

    if (list.empty())
    {
        message_window->message("List is empty");
        message_window->exec();
        return;
    }

    // Get time before
    milliseconds started_at = duration_cast< milliseconds >(
                system_clock::now().time_since_epoch());

    switch(algo)
    {
    case Select:
        selecting_sort<CodeSample>(list.data(), 0, list.size() - 1, comparator);
        break;
    case Quick:
        quick_sort<CodeSample>(list.data(), 0, list.size() - 1, comparator);
        break;
    default: // other once have no inmplementation yet!
        message_window->message("Internal error");
        message_window->exec();
        return;
    }

    // Get time after
    milliseconds finished_at = duration_cast< milliseconds >(
                system_clock::now().time_since_epoch());

    milliseconds delta = finished_at - started_at;
    double sec = delta.count() / 1000.0;
    std::stringstream s;
    s << "Time: " << std::setprecision(3) << sec << " sec\n";
    s << "Elements: " << list.size();

    fill_text_browser();

    message_window->message(s.str().c_str());
    message_window->exec();
}

void SortDemoWindow::onShuffle()
{
    if (!is_valid)
        return;

    if (list.size() > 1)
    {
        for (size_t i = list.size()-1; i != 0; --i)
        {
            size_t k = (i == 1) ? 0 : (rand() % i);
            std::swap(list[i], list[k]);
        }
        fill_text_browser();
    }
}

void SortDemoWindow::onClear()
{
    list.clear();
    if (is_valid)
        fill_text_browser();
}


void SortDemoWindow::onAdd()
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
        list.push_back(code_sample);
        fill_text_browser();
    }
}

void SortDemoWindow::onRandom()
{
    if (!is_valid)
        return;

    int k = rnd_count->value();

    if (k < 1 || k > 1000)
        return;

    //for (int i = 0; i < 10; i++)
    for (int i = 0; i < k; i++)
    {
        CodeSample code_sample = {
            //std::to_string(i),
            randomText(10,15),
            randomText(5,10) + "_" + randomText(5,10) + "_" + randomText(5,10),
            randomText(10,20),
            randomText(10,20),
            randomText(5,10,0) + randomText(5,10) + randomText(5,10)
        };
        list.push_back(code_sample);
    }

    fill_text_browser();
}

void SortDemoWindow::fill_text_browser()
{
    if (!is_valid)
        return;

    size_t org_len = {0};
    size_t proj_len = {0};
    size_t component_len = {0};
    size_t class_len = {0};
    size_t method_len = {0};
    for (const auto& cs : list)
    {
        org_len = std::max<size_t>(cs.organization.length(), org_len);
        proj_len = std::max<size_t>(cs.project.length(), proj_len);
        component_len = std::max<size_t>(cs.component.length(), component_len);
        class_len = std::max<size_t>(cs.class_name.length(), class_len);
        method_len = std::max<size_t>(cs.method_name.length(), method_len);
    }

    org_len += 2;
    proj_len += 2;
    component_len += 2;
    class_len += 2;
    method_len += 2;

    std::stringstream s;
    for (const auto& cs : list)
    {
        s << std::left;
        s << std::setw(org_len) << cs.organization;
        s << std::setw(proj_len) << cs.project;
        s << std::setw(component_len) << cs.component;
        s << std::setw(class_len) << cs.class_name;
        s << std::setw(method_len) << cs.method_name;
        s << std::endl;
    }

    text_browser->setText( QString( s.str().c_str() ) );
}

void SortDemoWindow::onOrganizationSelected()
{
    comparator = [](const CodeSample& x, const CodeSample& y) -> bool {
        return x.organization < y.organization;
    };
}

void SortDemoWindow::onProjectSelected()
{
    comparator = [](const CodeSample& x, const CodeSample& y) -> bool {
        return x.project < y.project;
    };
}

void SortDemoWindow::onComponentSelected()
{
    comparator = [](const CodeSample& x, const CodeSample& y) -> bool {
        return x.component < y.component;
    };
}

void SortDemoWindow::onClassSelected()
{
    comparator = [](const CodeSample& x, const CodeSample& y) -> bool {
        return x.class_name < y.class_name;
    };
}

void SortDemoWindow::onMethodSelected()
{
    comparator = [](const CodeSample& x, const CodeSample& y) -> bool {
        return x.method_name < y.method_name;
    };
}

void SortDemoWindow::onAllFieldsSelected()
{
    comparator = [](const CodeSample& x, const CodeSample& y) -> bool {
        return
            (x.organization < y.organization)
            || (x.organization == y.organization && x.project < y.project)
            || (x.organization == y.organization && x.project == y.project
                && x.component < y.component)
            || (x.organization == y.organization && x.project == y.project
                && x.component == y.component && x.class_name < y.class_name)
            || (x.organization == y.organization && x.project == y.project
                && x.component == y.component && x.class_name == y.class_name
                && x.method_name < y.method_name);
    };
}

void SortDemoWindow::onSelectingAlg()
{
    algo = Select;
}

void SortDemoWindow::onQuickAlg()
{
    algo = Quick;
}

void SortDemoWindow::onHeapAlg()
{
    algo = Heap;
}

void SortDemoWindow::onRadixAlg()
{
    algo = Radix;
}
