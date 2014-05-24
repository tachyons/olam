/********************************************************************************
** Form generated from reading UI file 'about.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_About
{
public:
    QVBoxLayout *verticalLayout;
    QStackedWidget *about;
    QWidget *page;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QWidget *page_3;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_2;
    QListWidget *listWidget;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_4;
    QListWidget *listWidget_2;
    QWidget *page_4;
    QVBoxLayout *verticalLayout_5;
    QPlainTextEdit *plain;
    QWidget *page_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *about_button;
    QPushButton *credits_button;
    QPushButton *license_button;
    QPushButton *close_button;

    void setupUi(QDialog *About)
    {
        if (About->objectName().isEmpty())
            About->setObjectName(QStringLiteral("About"));
        About->resize(400, 300);
        verticalLayout = new QVBoxLayout(About);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        about = new QStackedWidget(About);
        about->setObjectName(QStringLiteral("about"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        label_2 = new QLabel(page);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(160, 120, 67, 17));
        label_3 = new QLabel(page);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(110, 150, 181, 20));
        label_4 = new QLabel(page);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(40, 0, 301, 161));
        about->addWidget(page);
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        verticalLayout_2 = new QVBoxLayout(page_3);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        tabWidget = new QTabWidget(page_3);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        horizontalLayout_2 = new QHBoxLayout(tab);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        listWidget = new QListWidget(tab);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        horizontalLayout_2->addWidget(listWidget);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayout_4 = new QVBoxLayout(tab_2);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        listWidget_2 = new QListWidget(tab_2);
        new QListWidgetItem(listWidget_2);
        listWidget_2->setObjectName(QStringLiteral("listWidget_2"));

        verticalLayout_4->addWidget(listWidget_2);

        tabWidget->addTab(tab_2, QString());

        verticalLayout_2->addWidget(tabWidget);

        about->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QStringLiteral("page_4"));
        verticalLayout_5 = new QVBoxLayout(page_4);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        plain = new QPlainTextEdit(page_4);
        plain->setObjectName(QStringLiteral("plain"));
        plain->setReadOnly(true);
        plain->setPlainText(QLatin1String("Olam is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.\n"
"\n"
"Olam is distributed in the hope that it will be useful,\n"
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"GNU General Public License for more details.\n"
"\n"
"You should have received a copy of the GNU General Public License\n"
"along with Format Junkie; if not, write to the Free Software Foundation, Inc.,\n"
"51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA\n"
"\n"
"For further information you can also visit http://www.gnu.org/licenses/gpl.html"));

        verticalLayout_5->addWidget(plain);

        about->addWidget(page_4);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        about->addWidget(page_2);

        verticalLayout->addWidget(about);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        about_button = new QPushButton(About);
        about_button->setObjectName(QStringLiteral("about_button"));

        horizontalLayout->addWidget(about_button);

        credits_button = new QPushButton(About);
        credits_button->setObjectName(QStringLiteral("credits_button"));

        horizontalLayout->addWidget(credits_button);

        license_button = new QPushButton(About);
        license_button->setObjectName(QStringLiteral("license_button"));

        horizontalLayout->addWidget(license_button);

        close_button = new QPushButton(About);
        close_button->setObjectName(QStringLiteral("close_button"));

        horizontalLayout->addWidget(close_button);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(About);

        about->setCurrentIndex(0);
        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(About);
    } // setupUi

    void retranslateUi(QDialog *About)
    {
        About->setWindowTitle(QApplication::translate("About", "About", 0));
        label_2->setText(QApplication::translate("About", "By", 0));
        label_3->setText(QApplication::translate("About", "Tachyons Creations", 0));
        label_4->setText(QApplication::translate("About", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src=\":/new/prefix1/misc/olam.png\" height=\"60\" /><span style=\" font-family:'Ubuntu'; font-size:11pt;\">	</span></p></body></html>", 0));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("About", "Aboobacker MK (Qt ui)", 0));
        QListWidgetItem *___qlistwidgetitem1 = listWidget->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("About", "Kailash Nadh (Database)", 0));
        listWidget->setSortingEnabled(__sortingEnabled);

        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("About", "Written By", 0));

        const bool __sortingEnabled1 = listWidget_2->isSortingEnabled();
        listWidget_2->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem2 = listWidget_2->item(0);
        ___qlistwidgetitem2->setText(QApplication::translate("About", "Aboobacker MK", 0));
        listWidget_2->setSortingEnabled(__sortingEnabled1);

        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("About", "Art work by", 0));
        about_button->setText(QApplication::translate("About", "&About", 0));
        credits_button->setText(QApplication::translate("About", "&Credits", 0));
        license_button->setText(QApplication::translate("About", "&Licence", 0));
        close_button->setText(QApplication::translate("About", "&Close", 0));
    } // retranslateUi

};

namespace Ui {
    class About: public Ui_About {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H
