#pragma once

#include <QWidget>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class start_menu; }
QT_END_NAMESPACE

class start_menu : public QWidget {
Q_OBJECT

public:
    explicit start_menu(QWidget *parent = nullptr);

    ~start_menu() override;

private:
    Ui::start_menu *ui;
};

