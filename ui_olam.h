/********************************************************************************
** Form generated from reading UI file 'olam.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OLAM_H
#define UI_OLAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Olam
{
public:
    QAction *action_Exit;
    QAction *action_About;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *mal_eng;
    QWidget *tab;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLineEdit *dict_word;
    QPushButton *maleng_search;
    QSpacerItem *horizontalSpacer_2;
    QTextBrowser *dict_result;
    QWidget *malayalam;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_5;
    QLineEdit *corpus_word;
    QPushButton *malmal_search;
    QSpacerItem *horizontalSpacer_8;
    QTextBrowser *corpus_result;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menu_Help;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Olam)
    {
        if (Olam->objectName().isEmpty())
            Olam->setObjectName(QStringLiteral("Olam"));
        Olam->resize(449, 384);
        action_Exit = new QAction(Olam);
        action_Exit->setObjectName(QStringLiteral("action_Exit"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/prefix1/icons/application-exit.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_Exit->setIcon(icon);
        action_About = new QAction(Olam);
        action_About->setObjectName(QStringLiteral("action_About"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/new/prefix1/icons/help-about.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_About->setIcon(icon1);
        centralWidget = new QWidget(Olam);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        mal_eng = new QTabWidget(centralWidget);
        mal_eng->setObjectName(QStringLiteral("mal_eng"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout_4 = new QVBoxLayout(tab);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(118, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        dict_word = new QLineEdit(tab);
        dict_word->setObjectName(QStringLiteral("dict_word"));

        horizontalLayout->addWidget(dict_word);

        maleng_search = new QPushButton(tab);
        maleng_search->setObjectName(QStringLiteral("maleng_search"));

        horizontalLayout->addWidget(maleng_search);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_4->addLayout(horizontalLayout);

        dict_result = new QTextBrowser(tab);
        dict_result->setObjectName(QStringLiteral("dict_result"));

        verticalLayout_4->addWidget(dict_result);

        mal_eng->addTab(tab, QString());
        malayalam = new QWidget();
        malayalam->setObjectName(QStringLiteral("malayalam"));
        verticalLayout_2 = new QVBoxLayout(malayalam);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        corpus_word = new QLineEdit(malayalam);
        corpus_word->setObjectName(QStringLiteral("corpus_word"));

        horizontalLayout_4->addWidget(corpus_word);

        malmal_search = new QPushButton(malayalam);
        malmal_search->setObjectName(QStringLiteral("malmal_search"));

        horizontalLayout_4->addWidget(malmal_search);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_8);


        verticalLayout_2->addLayout(horizontalLayout_4);

        corpus_result = new QTextBrowser(malayalam);
        corpus_result->setObjectName(QStringLiteral("corpus_result"));

        verticalLayout_2->addWidget(corpus_result);

        mal_eng->addTab(malayalam, QString());

        verticalLayout->addWidget(mal_eng);

        Olam->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Olam);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 449, 20));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QStringLiteral("menu_File"));
        menu_Help = new QMenu(menuBar);
        menu_Help->setObjectName(QStringLiteral("menu_Help"));
        Olam->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Olam);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Olam->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Olam);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Olam->setStatusBar(statusBar);

        menuBar->addAction(menu_File->menuAction());
        menuBar->addAction(menu_Help->menuAction());
        menu_File->addAction(action_Exit);
        menu_Help->addAction(action_About);
        mainToolBar->addAction(action_Exit);
        mainToolBar->addAction(action_About);

        retranslateUi(Olam);

        mal_eng->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Olam);
    } // setupUi

    void retranslateUi(QMainWindow *Olam)
    {
        Olam->setWindowTitle(QApplication::translate("Olam", "Olam", 0));
        action_Exit->setText(QApplication::translate("Olam", "&Exit", 0));
        action_About->setText(QApplication::translate("Olam", "&About", 0));
        maleng_search->setText(QApplication::translate("Olam", "search", 0));
        mal_eng->setTabText(mal_eng->indexOf(tab), QApplication::translate("Olam", "English-Malayalam", 0));
        malmal_search->setText(QApplication::translate("Olam", "search", 0));
        mal_eng->setTabText(mal_eng->indexOf(malayalam), QApplication::translate("Olam", "Malayalam-Malayalam", 0));
        menu_File->setTitle(QApplication::translate("Olam", "&File", 0));
        menu_Help->setTitle(QApplication::translate("Olam", "&Help", 0));
    } // retranslateUi

};

namespace Ui {
    class Olam: public Ui_Olam {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OLAM_H
