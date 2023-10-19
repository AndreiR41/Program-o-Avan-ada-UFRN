#include "incluirdvd.h"
#include "ui_incluirdvd.h"



IncluirDVD::IncluirDVD(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IncluirDVD)
{
    ui->setupUi(this);
}

IncluirDVD::~IncluirDVD()
{
    delete ui;
}

void IncluirDVD::clear()
{
    ui->lineEditNome->setText("");
    ui->lineEditPreco->setText("");
    ui->lineEditDuracao->setText("");
}

void IncluirDVD::on_buttonBox_accepted()
{
    QString nome = ui-> lineEditNome-> text();
    QString preco = ui-> lineEditPreco-> text();
    QString duracao = ui-> lineEditDuracao-> text();

    emit signIncluirDVD(nome,preco,duracao);



}
