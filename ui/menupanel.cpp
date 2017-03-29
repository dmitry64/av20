#include "menupanel.h"
#include "ui_menupanel.h"

void MenuPanel::closeCurrent()
{
    switch(_state) {
    case MenuState::HelpMenuState:
        _state = MenuState::DefaultState;
        ui->helpButton->setPalette(_defaultPalette);
        emit helpMenuClosed();
        break;
    case MenuState::ModeMenuState:
        _state = MenuState::DefaultState;
        ui->modeButton->setPalette(_defaultPalette);
        emit modeMenuClosed();
        break;
    case MenuState::CalibrationsMenuState:
        _state = MenuState::DefaultState;
        ui->calibrationButton->setPalette(_defaultPalette);
        emit calibrationsMenuClosed();
        break;
    case MenuState::RegistrationMenuState:
        _state = MenuState::DefaultState;
        ui->registrationButton->setPalette(_defaultPalette);
        emit registrationMenuClosed();
        break;
    case MenuState::MemoryMenuState:
        _state = MenuState::DefaultState;
        ui->memoryButton->setPalette(_defaultPalette);
        emit memoryMenuClosed();
        break;
    case MenuState::OptionsMenuState:
        _state = MenuState::DefaultState;
        ui->optionsButton->setPalette(_defaultPalette);
        emit optionsMenuClosed();
        break;
    case MenuState::SystemMenuState:
        _state = MenuState::DefaultState;
        ui->systemButton->setPalette(_defaultPalette);
        emit systemMenuClosed();
        break;
    case MenuState::DefaultState:
        return;
        break;
    }
}

MenuPanel::MenuPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuPanel)
{
    ui->setupUi(this);
    _state = MenuState::DefaultState;
    _defaultPalette = ui->helpButton->palette();
    _activePalette.setColor(QPalette::Button, QColor(120,190,10));
    _activePalette.setColor(QPalette::ButtonText,Qt::black);
}

MenuPanel::~MenuPanel()
{
    delete ui;
}

void MenuPanel::resetMenu()
{
    closeCurrent();
}

void MenuPanel::on_helpButton_released()
{
    if(_state == MenuState::HelpMenuState) {
        closeCurrent();
    }
    else {
        closeCurrent();
        _state = MenuState::HelpMenuState;
        ui->helpButton->setPalette(_activePalette);
        emit helpMenuOpened();
    }
}

void MenuPanel::on_modeButton_released()
{
    if(_state == MenuState::ModeMenuState) {
        closeCurrent();
    }
    else {
        closeCurrent();
        _state = MenuState::ModeMenuState;
        ui->modeButton->setPalette(_activePalette);
        emit modeMenuOpened();
    }
}

void MenuPanel::on_registrationButton_released()
{
    if(_state == MenuState::RegistrationMenuState) {
        closeCurrent();
    }
    else {
        closeCurrent();
        _state = MenuState::RegistrationMenuState;
        ui->registrationButton->setPalette(_activePalette);
        emit registrationMenuOpened();
    }
}

void MenuPanel::on_memoryButton_released()
{
    if(_state == MenuState::MemoryMenuState) {
        closeCurrent();
    }
    else {
        closeCurrent();
        _state = MenuState::MemoryMenuState;
        ui->memoryButton->setPalette(_activePalette);
        emit memoryMenuOpened();
    }
}

void MenuPanel::on_optionsButton_released()
{
    if(_state == MenuState::OptionsMenuState) {
        closeCurrent();
    }
    else {
        closeCurrent();
        _state = MenuState::OptionsMenuState;
        ui->optionsButton->setPalette(_activePalette);
        emit optionsMenuOpened();
    }
}

void MenuPanel::on_systemButton_released()
{
    if(_state == MenuState::SystemMenuState) {
        closeCurrent();
    }
    else {
        closeCurrent();
        _state = MenuState::SystemMenuState;
        ui->systemButton->setPalette(_activePalette);
        emit systemMenuOpened();
    }
}

void MenuPanel::on_calibrationButton_released()
{
    if(_state == MenuState::CalibrationsMenuState) {
        closeCurrent();
    }
    else {
        closeCurrent();
        _state = MenuState::CalibrationsMenuState;
        ui->calibrationButton->setPalette(_activePalette);
        emit calibrationsMenuOpened();
    }
}
