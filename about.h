#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>

namespace Ui {
class About;
}

class About : public QDialog
{
    Q_OBJECT
    
public:
    explicit About(QWidget *parent = 0);
    ~About();
    
private slots:

    void on_about_button_clicked();

    void on_credits_button_clicked();

    void on_license_button_clicked();

    void on_close_button_clicked();

private:
    Ui::About *ui;
};

#endif // ABOUT_H
