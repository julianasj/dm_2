#include "mainwindow.h"
#include <iostream>
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnDecide, &QPushButton::clicked, this, &MainWindow::processDecision);
}

MainWindow::~MainWindow() { delete ui; }



bool AND(bool a, bool b) { return a && b; }
bool OR(bool a, bool b) { return a || b; }
bool NOT(bool a) { return !a; }
bool IMPLIES(bool a, bool b) { return !a || b; }


void MainWindow::processDecision(){

    bool enemyNearby = ui->checkEnemy->isChecked();
    bool healthLow = ui->checkHealth->isChecked();
    bool hasPotion = ui->checkPotion->isChecked();
    bool hasWeapon = ui->checkWeapon->isChecked();
    bool isTired = ui->checkTired->isChecked();

    QString action, reason;

    char again;
    
    if (AND(healthLow, hasPotion)) {
        action = "HEAL";
        reason = "Health is low AND potion is available.";
    }

    // Rule 2: (enemyNearby ∧ ¬healthLow ∧ hasWeapon) → Attack
    else if (AND(enemyNearby, AND(NOT(healthLow), hasWeapon))) {
        action = "ATTACK";
        reason = "Enemy nearby AND health is good AND has weapon.";
    }

    // Rule 3: (enemyNearby ∧ healthLow ∧ ¬hasPotion) → Run
    else if (AND(enemyNearby, AND(healthLow, NOT(hasPotion)))) {
        action = "RUN";
        reason = "Enemy nearby AND low health AND no potion.";
    }
    
    //rule 4: (¬enemyNearby ∧ healthLow v tired) → Rest
    else if(AND(NOT(enemyNearby),OR(healthLow,isTired))){
        action = "REST";
        reason = "No enemy nearby and player is tired or low health.";
    }

    // Rule 4: (¬enemyNearby) → Explore
    else if (NOT(enemyNearby)) {
        action = "EXPLORE";
        reason = "No enemy nearby. So player will rest";
    }
    
    else {
        action = "IDLE";
        reason = "No specific rule satisfied.";
    }
    
    ui->lblResult->setText("<b>Action:</b> " + action);
    ui->lblReason->setText("<i>Reason:</i> " + reason);

}