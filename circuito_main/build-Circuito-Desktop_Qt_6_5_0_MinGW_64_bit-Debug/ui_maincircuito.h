/********************************************************************************
** Form generated from reading UI file 'maincircuito.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINCIRCUITO_H
#define UI_MAINCIRCUITO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainCircuito
{
public:
    QAction *actionNovo;
    QAction *actionLer;
    QAction *actionSalvar;
    QAction *actionSair;
    QAction *actionGerar_tabela;
    QWidget *centralWidget;
    QTableWidget *tablePortas;
    QLabel *labelPortas;
    QTableWidget *tableSaidas;
    QLabel *labelSaidas;
    QLabel *labelCircuito;
    QLabel *labelCircuito_2;
    QTableWidget *tableTabelaVerdade;
    QMenuBar *menuBar;
    QMenu *menuCircuito;
    QMenu *menuSimular;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainCircuito)
    {
        if (MainCircuito->objectName().isEmpty())
            MainCircuito->setObjectName("MainCircuito");
        MainCircuito->resize(800, 640);
        actionNovo = new QAction(MainCircuito);
        actionNovo->setObjectName("actionNovo");
        actionLer = new QAction(MainCircuito);
        actionLer->setObjectName("actionLer");
        actionSalvar = new QAction(MainCircuito);
        actionSalvar->setObjectName("actionSalvar");
        actionSair = new QAction(MainCircuito);
        actionSair->setObjectName("actionSair");
        actionGerar_tabela = new QAction(MainCircuito);
        actionGerar_tabela->setObjectName("actionGerar_tabela");
        centralWidget = new QWidget(MainCircuito);
        centralWidget->setObjectName("centralWidget");
        tablePortas = new QTableWidget(centralWidget);
        if (tablePortas->columnCount() < 6)
            tablePortas->setColumnCount(6);
        if (tablePortas->rowCount() < 1)
            tablePortas->setRowCount(1);
        tablePortas->setObjectName("tablePortas");
        tablePortas->setGeometry(QRect(0, 48, 311, 551));
        tablePortas->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        tablePortas->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tablePortas->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tablePortas->setTabKeyNavigation(false);
        tablePortas->setAlternatingRowColors(true);
        tablePortas->setSelectionMode(QAbstractItemView::SingleSelection);
        tablePortas->setSelectionBehavior(QAbstractItemView::SelectRows);
        tablePortas->setRowCount(1);
        tablePortas->setColumnCount(6);
        tablePortas->horizontalHeader()->setVisible(false);
        tablePortas->horizontalHeader()->setMinimumSectionSize(25);
        tablePortas->horizontalHeader()->setDefaultSectionSize(45);
        tablePortas->horizontalHeader()->setHighlightSections(false);
        tablePortas->verticalHeader()->setVisible(false);
        tablePortas->verticalHeader()->setMinimumSectionSize(20);
        tablePortas->verticalHeader()->setDefaultSectionSize(25);
        labelPortas = new QLabel(centralWidget);
        labelPortas->setObjectName("labelPortas");
        labelPortas->setGeometry(QRect(0, 24, 311, 25));
        QFont font;
        font.setBold(true);
        labelPortas->setFont(font);
        labelPortas->setFrameShape(QFrame::Box);
        labelPortas->setAlignment(Qt::AlignCenter);
        tableSaidas = new QTableWidget(centralWidget);
        if (tableSaidas->columnCount() < 1)
            tableSaidas->setColumnCount(1);
        if (tableSaidas->rowCount() < 1)
            tableSaidas->setRowCount(1);
        tableSaidas->setObjectName("tableSaidas");
        tableSaidas->setGeometry(QRect(310, 48, 86, 551));
        tableSaidas->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        tableSaidas->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableSaidas->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableSaidas->setTabKeyNavigation(false);
        tableSaidas->setAlternatingRowColors(true);
        tableSaidas->setSelectionMode(QAbstractItemView::SingleSelection);
        tableSaidas->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableSaidas->setRowCount(1);
        tableSaidas->setColumnCount(1);
        tableSaidas->horizontalHeader()->setMinimumSectionSize(25);
        tableSaidas->horizontalHeader()->setDefaultSectionSize(45);
        tableSaidas->horizontalHeader()->setHighlightSections(false);
        tableSaidas->verticalHeader()->setMinimumSectionSize(20);
        tableSaidas->verticalHeader()->setDefaultSectionSize(25);
        labelSaidas = new QLabel(centralWidget);
        labelSaidas->setObjectName("labelSaidas");
        labelSaidas->setGeometry(QRect(310, 24, 86, 25));
        labelSaidas->setFont(font);
        labelSaidas->setFrameShape(QFrame::Box);
        labelSaidas->setAlignment(Qt::AlignCenter);
        labelCircuito = new QLabel(centralWidget);
        labelCircuito->setObjectName("labelCircuito");
        labelCircuito->setGeometry(QRect(0, 0, 396, 25));
        labelCircuito->setFont(font);
        labelCircuito->setFrameShape(QFrame::Box);
        labelCircuito->setAlignment(Qt::AlignCenter);
        labelCircuito_2 = new QLabel(centralWidget);
        labelCircuito_2->setObjectName("labelCircuito_2");
        labelCircuito_2->setGeometry(QRect(404, 0, 396, 25));
        labelCircuito_2->setFont(font);
        labelCircuito_2->setFrameShape(QFrame::Box);
        labelCircuito_2->setAlignment(Qt::AlignCenter);
        tableTabelaVerdade = new QTableWidget(centralWidget);
        if (tableTabelaVerdade->columnCount() < 4)
            tableTabelaVerdade->setColumnCount(4);
        if (tableTabelaVerdade->rowCount() < 99)
            tableTabelaVerdade->setRowCount(99);
        tableTabelaVerdade->setObjectName("tableTabelaVerdade");
        tableTabelaVerdade->setGeometry(QRect(404, 24, 396, 575));
        tableTabelaVerdade->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        tableTabelaVerdade->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tableTabelaVerdade->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableTabelaVerdade->setTabKeyNavigation(false);
        tableTabelaVerdade->setAlternatingRowColors(true);
        tableTabelaVerdade->setSelectionMode(QAbstractItemView::NoSelection);
        tableTabelaVerdade->setSelectionBehavior(QAbstractItemView::SelectItems);
        tableTabelaVerdade->setRowCount(99);
        tableTabelaVerdade->setColumnCount(4);
        tableTabelaVerdade->horizontalHeader()->setVisible(false);
        tableTabelaVerdade->horizontalHeader()->setMinimumSectionSize(25);
        tableTabelaVerdade->horizontalHeader()->setDefaultSectionSize(45);
        tableTabelaVerdade->horizontalHeader()->setHighlightSections(false);
        tableTabelaVerdade->verticalHeader()->setVisible(false);
        tableTabelaVerdade->verticalHeader()->setDefaultSectionSize(25);
        tableTabelaVerdade->verticalHeader()->setHighlightSections(false);
        MainCircuito->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainCircuito);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 800, 22));
        menuCircuito = new QMenu(menuBar);
        menuCircuito->setObjectName("menuCircuito");
        menuSimular = new QMenu(menuBar);
        menuSimular->setObjectName("menuSimular");
        MainCircuito->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainCircuito);
        statusBar->setObjectName("statusBar");
        MainCircuito->setStatusBar(statusBar);

        menuBar->addAction(menuCircuito->menuAction());
        menuBar->addAction(menuSimular->menuAction());
        menuCircuito->addAction(actionNovo);
        menuCircuito->addAction(actionLer);
        menuCircuito->addAction(actionSalvar);
        menuCircuito->addSeparator();
        menuCircuito->addAction(actionSair);
        menuSimular->addAction(actionGerar_tabela);

        retranslateUi(MainCircuito);

        QMetaObject::connectSlotsByName(MainCircuito);
    } // setupUi

    void retranslateUi(QMainWindow *MainCircuito)
    {
        MainCircuito->setWindowTitle(QCoreApplication::translate("MainCircuito", "Simulador de Circuitos Digitais", nullptr));
        actionNovo->setText(QCoreApplication::translate("MainCircuito", "Novo...", nullptr));
        actionLer->setText(QCoreApplication::translate("MainCircuito", "Ler...", nullptr));
        actionSalvar->setText(QCoreApplication::translate("MainCircuito", "Salvar...", nullptr));
        actionSair->setText(QCoreApplication::translate("MainCircuito", "Sair", nullptr));
        actionGerar_tabela->setText(QCoreApplication::translate("MainCircuito", "Gerar tabela", nullptr));
        labelPortas->setText(QCoreApplication::translate("MainCircuito", "PORTAS E CONEXOES", nullptr));
        labelSaidas->setText(QCoreApplication::translate("MainCircuito", "SAIDAS", nullptr));
        labelCircuito->setText(QCoreApplication::translate("MainCircuito", "CIRCUITO", nullptr));
        labelCircuito_2->setText(QCoreApplication::translate("MainCircuito", "TABELA VERDADE", nullptr));
        menuCircuito->setTitle(QCoreApplication::translate("MainCircuito", "Circuito", nullptr));
        menuSimular->setTitle(QCoreApplication::translate("MainCircuito", "Simular", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainCircuito: public Ui_MainCircuito {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINCIRCUITO_H
