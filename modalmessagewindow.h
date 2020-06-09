#ifndef MODALMESSAGEWINDOW_H
#define MODALMESSAGEWINDOW_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>

class ModalMessageWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ModalMessageWindow(QWidget *parent);

    void message(const QString& msg);

private:
    void onOk();

    QPushButton* btn = {nullptr};
    QLabel* msg = {nullptr};
};


#endif // MODALMESSAGEWINDOW_H
