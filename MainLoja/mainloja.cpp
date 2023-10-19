#include "mainloja.h"
#include "./ui_mainloja.h"

#include "loja.h"
#include "loja.cpp"

#include "incluirlivro.h"
#include "incluircd.h"
#include "incluirdvd.h"



#include <Qlabel>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <string>




MainLoja::MainLoja(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainLoja)
{
    ui->setupUi(this);

    inclLivro = new IncluirLivro(this);
    inclDVD = new IncluirDVD(this);
    inclCD = new IncluirCD(this);

    int totalItens= 0;
    total_itens= new QLabel(this);
    statusBar()-> addWidget(total_itens);
    total_itens->setNum(totalItens);


    connect(inclLivro,SIGNAL(signIncluirLivro(QString,QString,QString)),this,SLOT(slotIncluirLivro(QString,QString,QString)));
    connect(inclCD,SIGNAL(signIncluirCD(QString,QString,QString)),this,SLOT(slotIncluirCD(QString,QString,QString)));
    connect(inclDVD,SIGNAL(signIncluirDVD(QString,QString,QString)),this,SLOT(slotIncluirDVD(QString,QString,QString)));

    // Alterar a cor de fundo dos QLabel
    ui->LIVROS->setStyleSheet("background-color: lightgray;");
    ui->CDS->setStyleSheet("background-color: lightgray;");
    ui->DVDS->setStyleSheet("background-color: lightgray;");

    // Alterar a cor de fundo dos cabeçalhos das tabelas
    ui->listaLivro->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: lightgray; }");
    ui->listaCD->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: lightgray; }");
    ui->listaDVD->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: lightgray; }");



    // Ajustar comportamento das colunas da tabela de livros
    ui->listaLivro->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->listaLivro->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->listaLivro->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);

    // Ajustar comportamento das colunas da tabela de CDs
    ui->listaCD->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->listaCD->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->listaCD->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);

    // Ajustar comportamento das colunas da tabela de DVDs
    ui->listaDVD->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->listaDVD->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->listaDVD->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    /*
    ui->listaLivro->setHorizontalHeaderLabels(QStringList() << "NOME" << "PREÇO" << "AUTOR");
    ui->listaCD->setHorizontalHeaderLabels(QStringList() << "NOME" << "PREÇO" << "NÚMERO DE FAIXAS");
    ui->listaDVD->setHorizontalHeaderLabels(QStringList() << "NOME" << "PREÇO" << "DURAÇÃO");
        */

}

MainLoja::~MainLoja()
{
    delete ui;
}


void MainLoja:: atualizarTotal(){
    total_itens->setText(QString::number(X.getNumLivro() + X.getNumCD() + X.getNumDVD()));
}


//Falta colocar na table
void MainLoja::on_actionLer_triggered()
{
    QString fileName = QFileDialog::
        getOpenFileName(this, "Ler estoque",QString(),"*.txt");

    std::string fileString = fileName.toStdString();

    if (!fileName.isEmpty())
    {
        if (!X.ler(fileString))
        {
            QMessageBox::critical(this,tr("Erro"), tr("Erro na leitura do arquivo."));
        }
    }
    exibirLivro();
    exibirCD();
    exibirDVD();
    atualizarTotal();


}


void MainLoja::on_actionSalvar_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Salvar estoque", QString(), "*.txt");

    if (fileName.isEmpty()) // Verifica se o nome do arquivo não está vazio
    {
        return;
    }

    std::string fileString = fileName.toStdString();

    if (!X.salvar(fileString))
    {
        QMessageBox::critical(this, tr("Erro"), tr("Erro na escrita do arquivo."));
    }
}


void MainLoja::on_actionSair_triggered()
{
    QCoreApplication::quit();
}




//Exibir Janelas de Diálogo
void MainLoja::on_actionIncluir_Livro_triggered()
{
    inclLivro->clear();
    inclLivro->show();

}

void MainLoja::on_actionIncluir_CD_triggered()
{
    inclCD->clear();
    inclCD->show();
}

void MainLoja::on_actionIncluir_DVD_triggered()
{
    inclDVD->clear();
    inclDVD->show();
}


// Slots privados

void MainLoja:: slotIncluirLivro(QString nome, QString preco, QString autor){

    std:: string nomeString = nome.toStdString();
    std:: string autorString = autor.toStdString();

    int precoCents =round(preco.toFloat()*100);

    if( nomeString==""||precoCents==0||autorString==""){
        QMessageBox::critical(this,"Livro Inválido\n" ,
                                    "Não foi possível inlcluir o Livro: \n Nome:"+nome+"\n Preço:"+preco+"\n Autor: "+autor,"OK");
    }else{

        Livro novoLivro(nomeString,precoCents,autorString);
        X.incluirLivro(novoLivro);
        exibirLivro();
        atualizarTotal();
    }
}

void MainLoja:: slotIncluirCD(QString nome, QString preco, QString numfaixas){

    std:: string nomeString = nome.toStdString();

    int precoCents =round(preco.toFloat()*100);
    int NumeroFaixas = numfaixas.toInt();

    if( nomeString==""||precoCents==0||NumeroFaixas==0){
        QMessageBox::critical(this,"CD Inválido\n ",
                                    "Não foi possível inlcluir o CD: \n Nome:"+nome+"\n Preço:"+preco+"\n Nº de Faixas:"+numfaixas,"OK");
    }else{
        CD novoCD(nomeString,precoCents,NumeroFaixas);
        X.incluirCD(novoCD);
        exibirCD();
        atualizarTotal();
    }
}

void MainLoja:: slotIncluirDVD(QString nome, QString preco, QString duracao){

    std:: string nomeString = nome.toStdString();

    int precoCents =round(preco.toFloat()*100);
    int minutos = round(duracao.toInt());
    if( nomeString==""||precoCents==0||minutos==0){
        QMessageBox::critical(this,"DVD Inválido\n ",
                                    "Não foi possível inlcluir o DVD: \n Nome:"+nome+"\n Preço:"+preco+"\n Duração:"+duracao,"OK");
    }else{
        DVD novoDVD(nomeString,precoCents,minutos);
        X.incluirDVD(novoDVD);
        exibirDVD();
        atualizarTotal();
    }
}



//Exibir na tabela

void MainLoja:: exibirLivro(){

    ui->listaLivro->clearContents();
    int numItens = X.getNumLivro();
    ui->listaLivro->setRowCount(numItens);

    // Iterar sobre as linhas da tabela
    for (int i = 0; i < numItens; i++) {
        Livro L = X.getLivro(i);
        QLabel* labelNome = new QLabel(L.getNome().c_str());
        QLabel* labelPreco = new QLabel(QString::number(L.getPreco(), 'f', 2));
        QLabel* labelAutor = new QLabel(L.getAutor().c_str());

        // Definir alinhamento de acordo com o layout da coluna específica
        labelNome->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        labelPreco->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        labelAutor->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

        // Incluir os QLabel na tabela
        ui->listaLivro->setCellWidget(i, 0, labelNome);
        ui->listaLivro->setCellWidget(i, 1, labelPreco);
        ui->listaLivro->setCellWidget(i, 2, labelAutor);
    }
}
void MainLoja:: exibirCD(){

    ui->listaCD->clearContents();
    int numItens = X.getNumCD();
    ui->listaCD->setRowCount(numItens);

    // Iterar sobre as linhas da tabela
    for (int i = 0; i < numItens; i++) {
        CD cd = X.getCD(i);
        QLabel* labelNome = new QLabel(cd.getNome().c_str());
        QLabel* labelPreco = new QLabel(QString::number(cd.getPreco(), 'f', 2));
        QLabel* labelNFaixas = new QLabel(QString::number(cd.getNumFaixas()));

        // Definir alinhamento de acordo com o layout da coluna específica
        labelNome->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        labelPreco->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        labelNFaixas->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);

        // Incluir os QLabel na tabela
        ui->listaCD->setCellWidget(i, 0, labelNome);
        ui->listaCD->setCellWidget(i, 1, labelPreco);
        ui->listaCD->setCellWidget(i, 2, labelNFaixas);
    }
}
void MainLoja:: exibirDVD(){

    ui->listaDVD->clearContents();
    int numItens = X.getNumDVD();
    ui->listaDVD->setRowCount(numItens);

    // Iterar sobre as linhas da tabela
    for (int i = 0; i < numItens; i++) {
        DVD dvd = X.getDVD(i);
        QLabel* labelNome = new QLabel(dvd.getNome().c_str());
        QLabel* labelPreco = new QLabel(QString::number(dvd.getPreco(), 'f', 2));
        QLabel* labelDuracao = new QLabel(QString::number(dvd.getDuracao()));

        // Definir alinhamento de acordo com o layout da coluna específica
        labelNome->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        labelPreco->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        labelDuracao->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);

        // Incluir os QLabel na tabela
        ui->listaDVD->setCellWidget(i, 0, labelNome);
        ui->listaDVD->setCellWidget(i, 1, labelPreco);
        ui->listaDVD->setCellWidget(i, 2, labelDuracao);
    }
}





void MainLoja::on_listaLivro_cellDoubleClicked(int row, int column)
{

    if (row >= 0 && row < X.getNumLivro())
    {
        Livro livro = X.getLivro(row);

        X.excluirLivro(row);

        exibirLivro();
        atualizarTotal();
    }
}


void MainLoja::on_listaCD_cellDoubleClicked(int row, int column)
{
    if (row >= 0 && row < X.getNumCD())
    {
        CD cd = X.getCD(row);

        X.excluirCD(row);

        exibirCD();
        atualizarTotal();
    }

}


void MainLoja::on_listaDVD_cellDoubleClicked(int row, int column)
{
    if (row >= 0 && row < X.getNumDVD())
    {
        DVD dvd = X.getDVD(row);

        X.excluirDVD(row);

        exibirDVD();
        atualizarTotal();
    }
}

