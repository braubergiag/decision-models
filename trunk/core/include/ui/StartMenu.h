#pragma once

#include <QWidget>
#include <QPushButton>
#include "DecisionModelDialog.h"
#include "../DecisionModel.h"
#include <memory>
QT_BEGIN_NAMESPACE
namespace Ui { class StartMenu; }
QT_END_NAMESPACE

class StartMenu : public QWidget {
Q_OBJECT

public:
    explicit StartMenu(QWidget *parent = nullptr);

    ~StartMenu() override;

private slots:
    void onCreateModelButtonClicked();

private:
    std::shared_ptr<DecisionModel> dmodelPtr_;
    Ui::StartMenu *ui;
};

