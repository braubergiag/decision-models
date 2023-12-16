#pragma once

#include <QWidget>
#include <QPushButton>
#include "DecisionModelDialog.h"
QT_BEGIN_NAMESPACE
namespace Ui { class StartMenu; }
QT_END_NAMESPACE

class StartMenu : public QWidget {
Q_OBJECT

public:
    explicit StartMenu(QWidget *parent = nullptr);

    ~StartMenu() override;

private slots:
    void on_createModelButton_clicked();

private:
    Ui::StartMenu *ui;
};

