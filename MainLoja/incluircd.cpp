#include "incluircd.h"
#include "ui_incluircd.h"



IncluirCD::IncluirCD(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IncluirCD)
{
    ui->setupUi(this);
}

IncluirCD::~IncluirCD()
{
    delete ui;
}

void IncluirCD::clear()
{
    ui->lineEditNome->setText("");
    ui->lineEditPreco->setText("");
    ui->lineEditNFaixas->setText("");
}

void IncluirCD::on_buttonBox_accepted()
{
    QString nome = ui-> lineEditNome-> text();
    QString preco = ui-> lineEditPreco-> text();
    QString numfaixas = ui-> lineEditNFaixas-> text();

    emit signIncluirCD(nome,preco,numfaixas);


}

