#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
}

About::~About()
{
    delete ui;
}

void About::on_about_button_clicked()
{
    ui->about->setCurrentIndex(0);
}

void About::on_credits_button_clicked()
{
    ui->about->setCurrentIndex(1);
}

void About::on_license_button_clicked()
{
    ui->about->setCurrentIndex(2);
}

void About::on_close_button_clicked()
{
    close();
}
