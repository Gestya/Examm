#include "mainwindow.h"
#include "singlelistwindow.h"
#include "splaytreewindow.h"
#include "sortdemowindow.h"

#include <QApplication>
#include <cstdlib>
#include <ctime>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    /* initialize random seed: */
    srand (time(NULL));

    SingleListWindow single_list_window;
    SplayTreeWindow splay_tree_window;
    SortDemoWindow sort_demo_window;

    MainWindow main_window(&single_list_window, &splay_tree_window, &sort_demo_window);
    main_window.show();

    return app.exec();
}
