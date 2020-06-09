#include "modalmessagewindow.h"

#if 1

ModalMessageWindow::ModalMessageWindow(QWidget *parent)
    : QDialog(parent)
{
    resize(QSize(300,240));

    btn = new QPushButton(QString("Ok"), this);
    btn->move(50, 180);
    btn->resize(QSize(200,20));

    connect(btn, &QPushButton::pressed, this, &ModalMessageWindow::onOk);

    msg = new QLabel(QString("Ok"), this);
    msg->setText(QString("ModalMessageWindow::message(const QString& msg)y"));
    msg->move(10, 10);
    msg->resize(QSize(280,150));
    msg->setAlignment(Qt::AlignmentFlag::AlignHCenter | Qt::AlignmentFlag::AlignVCenter);
}

void ModalMessageWindow::message(const QString& msg)
{
    this->msg->setText(msg);
}

void ModalMessageWindow::onOk()
{
    this->close();
}

#endif
