#include <QApplication>
#include <QSplitter>
#include <QListView>
#include "qmenumodel.h"
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSplitter main_window;
    QMenuModel model;
    QListView *list = new QListView(&main_window);
    list->setModel(&model);
    main_window.setWindowTitle("Menu of KSU");
    main_window.show();
    return a.exec();
}
