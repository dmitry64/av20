#include "ascaninfowidget.h"
#include "ui_ascaninfowidget.h"

AScanInfoWidget::AScanInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AScanInfoWidget)
{
    ui->setupUi(this);
}

AScanInfoWidget::~AScanInfoWidget()
{
    delete ui;
}

void AScanInfoWidget::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
    QWidget::changeEvent(event);
}

void AScanInfoWidget::setHValue(int value)
{
    ui->hLabel->setText(QString::number(value)+tr(" us"));
}

void AScanInfoWidget::setChannel(const Channel &chan, DisplayChannelID dispIndex)
{
    ui->channelNameLabel->setText(chan.getDisplayChannels().at(dispIndex).getRx().getName());
    ui->angleLabel->setText(QString::number(chan.getDisplayChannels().at(dispIndex).angle())+"°");
}
