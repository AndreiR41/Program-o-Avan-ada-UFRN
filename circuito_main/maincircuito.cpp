#include "maincircuito.h"
#include "ui_maincircuito.h"
#include "modificarporta.h"
#include "modificarsaida.h"
#include <QStringList>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <time.h>
#include <cmath>
#include <vector>
#include <string>
#include "bool3S.h"
#include  "circuito.cpp"
#include "port.cpp"



MainCircuito::MainCircuito(QWidget *parent) : QMainWindow(parent)
,ui(new Ui::MainCircuito)
,numIn(new QLabel(this))
,numOut(new QLabel(this))
,numPortas(new QLabel(this))
,C()
,newCircuito(new NewCircuito(this))
,modificarPorta(new ModificarPorta(this))
,modificarSaida(new ModificarSaida(this))
{
  ui->setupUi(this);

  // Cabecalhos da tabela de portas
  ui->tablePortas->horizontalHeader()->setVisible(true);
  ui->tablePortas->verticalHeader()->setVisible(true);
  ui->tablePortas->setHorizontalHeaderLabels(QStringList() << "TIPO" << "NUM\nENTR"
                                             << "ENTR\n1" << "ENTR\n2" << "ENTR\n3" << "ENTR\n4");
  ui->tableSaidas->setHorizontalHeaderLabels(QStringList() << "ORIG\nSAIDA");

  // Insere os widgets da barra de status
  statusBar()->insertWidget(0,new QLabel("Num entradas: "));
  statusBar()->insertWidget(1,numIn);
  statusBar()->insertWidget(2,new QLabel("   Num saidas: "));
  statusBar()->insertWidget(3,numOut);
  statusBar()->insertWidget(4,new QLabel("   Num portas: "));
  statusBar()->insertWidget(5,numPortas);

  // Conecta sinais
  // Sinais da janela principal para janela novo circuito
  connect(this, &MainCircuito::signShowNewCircuito,
          newCircuito, &NewCircuito::slotShowNewCircuito);
  // Sinais da janela principal para janela modificar porta
  connect(this, &MainCircuito::signSetRangeInputs,
          modificarPorta, &ModificarPorta::slotSetRangeInputs);
  connect(this, &MainCircuito::signShowModificarPorta,
          modificarPorta, &ModificarPorta::slotShowModificarPorta);
  // Sinais da janela principal para janela modificar saida
  connect(this, &MainCircuito::signSetRangeInputs,
          modificarSaida, &ModificarSaida::slotSetRangeInputs);
  connect(this, &MainCircuito::signShowModificarSaida,
          modificarSaida, &ModificarSaida::slotShowModificarSaida);
  // Sinais da janela novo circuito para janela principal
  connect(newCircuito, &NewCircuito::signNewCircuito,
          this, &MainCircuito::slotNewCircuito);
  // Sinais da janela modificar porta para janela principal
  connect(modificarPorta, &ModificarPorta::signModificarPorta,
          this, &MainCircuito::slotModificarPorta);
  // Sinais da janela modificar saida para janela principal
  connect(modificarSaida, &ModificarSaida::signModificarSaida,
          this, &MainCircuito::slotModificarSaida);

  // Redimensiona todas as tabelas e reexibe os valores da barra de status
  // Essa funcao deve ser chamada sempre que mudar o circuito
  redimensionaTabelas();
}

MainCircuito::~MainCircuito()
{
  delete ui;
}

void MainCircuito::slotNewCircuito(int NInputs, int NOutputs, int NPortas)
{
  // O circuito deve ser criado usando a funcao apropriada da classe Circuito
  if(NInputs < 0 || NOutputs <0|| NPortas < 0){
      QMessageBox::critical(this, tr("O Circuito nao esta completamente definido"),"Nao pode ser salvo" );
  }

  C.resize(NInputs, NOutputs, NPortas);


  // Depois do novo circuito criado, as tabelas devem ser redimensionadas
  redimensionaTabelas();
}

void MainCircuito::slotModificarPorta(int IdPort, QString TipoPort, int NumInputsPort,
                                      int IdInput0, int IdInput1, int IdInput2, int IdInput3)
{
  // Aqui deve ser chamado um metodo da classe Circuito que altere a porta cuja
  // id eh IdPort para que ela assuma as caracteristicas especificadas por

  // TipoPort, NumInputsPort

  C.setPort(IdPort, TipoPort.toStdString(),NumInputsPort );


  C.setId_inPort(IdPort, 0, IdInput0);

  if(NumInputsPort >=2 )C.setId_inPort(IdPort, 1, IdInput1);

  if(NumInputsPort >=3)C.setId_inPort(IdPort, 2, IdInput2);

  if(NumInputsPort >= 4)C.setId_inPort(IdPort, 3, IdInput3);

  // Depois de alterada, deve ser reexibida a porta correspondente e limpa a tabela verdade
  showPort(IdPort-1);
  limparTabelaVerdade();
}

void MainCircuito::slotModificarSaida(int IdSaida, int IdOrigemSaida)
{
  // Aqui deve ser chamado um metodo da classe Circuito que altere a saida cuja
  // id eh IdSaida para que ela assuma a origem especificada por
  // IdOrigemSaida
  if(!(C.validIdOrig(IdOrigemSaida) && C.validIdOutput(IdSaida))){
        QMessageBox::critical(this,tr("Sa?da de Circuito inv?lida"), "N?o foi possivel muda a sa?da do circuito");

  }
  C.setIdOutput(IdSaida,IdOrigemSaida);

  // Depois de alterada, deve ser reexibida a saida correspondente e limpa a tabela verdade
  showOutput(IdSaida-1);
  limparTabelaVerdade();
}

// Redimensiona todas as tabelas e reexibe todos os valores da barra de status
// Essa funcao deve ser chamada sempre que mudar o circuito (criar novo ou ler de arquivo)
void MainCircuito::redimensionaTabelas()
{
  // Esses numeros devem ser inicializados a partir de metodos de consulta da classe Circuito
  // Provisoriamente, estao sendo inicializados com valores nulos
  int numInputs= C.getNumInputs();
  int numOutputs= C.getNumOutputs();
  int numPorts= C.getNumPorts();

  // Variaveis auxiliares
  QString texto;
  QLabel *prov;
  int i;

  // ==========================================================
  // Ajusta os valores da barra de status
  // ==========================================================

  numIn->setNum(numInputs);
  numOut->setNum(numOutputs);
  numPortas->setNum(numPorts);

  // ==========================================================
  // Redimensiona a tabela das portas e conexoes
  // ==========================================================

  // Limpa o conteudo, mas nao os cabecalhos
  ui->tablePortas->clearContents();

  ui->tablePortas->setRowCount(numPorts);
  for (i=0; i<numPorts; i++)
  {
    showPort(i);
  }

  // ==========================================================
  // Redimensiona a tabela de saidas
  // ==========================================================

  // Limpa o conteudo, mas nao os cabecalhos
  ui->tableSaidas->clearContents();

  ui->tableSaidas->setRowCount(numOutputs);
  for (i=0; i<numOutputs; i++)
  {
    showOutput(i);
  }

  // ==========================================================
  // Redimensiona a tabela verdade
  // ==========================================================

  // Antes de redimensionar a tabela, anula todos os setSpan da primeira linha
  // Se nao fizer isso, dah erro ao redimensionar
  ui->tableTabelaVerdade->clearSpans();

  // Limpa todo o conteudo, inclusive cabecalhos
  ui->tableTabelaVerdade->clear();

  // Modifica as dimensoes
  ui->tableTabelaVerdade->setColumnCount(numInputs+numOutputs);
  int numCombinacoesEntrada = (numInputs>0 ? round(pow(3,numInputs)) : 0);
  // a tabela verdade tem uma linha a mais do que o numero de combinacoes de entrada
  // para conter o pseudocabecalho
  ui->tableTabelaVerdade->setRowCount(1 + numCombinacoesEntrada);

  // Cria o pseudocabecalho na primeira linha
  // Entradas
  if (numInputs > 0)
  {
    if (numInputs > 1) ui->tableTabelaVerdade->setSpan(0,0,1,numInputs);
    prov = new QLabel("ENTRADAS");
    prov->setAlignment(Qt::AlignCenter);
    prov->setStyleSheet("font-weight: bold");
    ui->tableTabelaVerdade->setCellWidget(0,0,prov);
  }
  // Saidas
  if (numOutputs > 0)
  {
    if (numOutputs > 1) ui->tableTabelaVerdade->setSpan(0,numInputs,1,numOutputs);
    prov = new QLabel("SAIDAS");
    prov->setAlignment(Qt::AlignCenter);
    prov->setStyleSheet("font-weight: bold");
    ui->tableTabelaVerdade->setCellWidget(0,numInputs,prov);
  }

  // ==========================================================
  // Fixa os limites para os spin boxs (emit signSetRangeInputs)
  // de entradas de portas (classe ModificarPorta) e
  // de origem das saidas (classe ModificarSaida)
  // emitindo um sinal que serah recebido por slots dessas classes
  // ==========================================================

  emit signSetRangeInputs(-numInputs, numPorts);
}

// Exibe os dados da i-esima porta (porta cuja id eh i+1)
// Essa funcao deve ser chamada sempre que mudar caracteristicas da porta
// A funcao redimensiona_tabela jah chama essa funcao para todas as portas
void MainCircuito::showPort(unsigned i)
{
  bool indice_valido = C.validIdPort(i + 1);
  if (!indice_valido)
    return;

  QString namePort = QString::fromStdString(C.getNamePort(i + 1));
  int numInputsPort = C.getNumInputsPort(i + 1);

  QLabel *prov;
  int j;

  int idInputPort[4] = {0}; // Inicializa com zeros
  for (j = 0; j < numInputsPort; j++)
  {
    idInputPort[j] = C.getId_inPort(i + 1, j);
  }

  // Cria e define valores dos widgets da linha da tabela que corresponde aa porta
  prov = new QLabel(namePort);
  prov->setAlignment(Qt::AlignCenter);
  ui->tablePortas->setCellWidget(i, 0, prov);

  prov = new QLabel;
  prov->setAlignment(Qt::AlignCenter);
  prov->setNum(numInputsPort);
  ui->tablePortas->setCellWidget(i, 1, prov);

  for (j = 0; j < 4; j++)
  {
    prov = new QLabel;
    prov->setAlignment(Qt::AlignCenter);
    if (j < numInputsPort)
        prov->setNum(idInputPort[j]);
    ui->tablePortas->setCellWidget(i, 2 + j, prov);
  }
}

// Exibe os dados da i-esima saida (saida cuja id eh i+1)
// Essa funcao deve ser chamada sempre que mudar valores da saida
// A funcao redimensiona_tabela jah chama essa funcao para todas as saidas
void MainCircuito::showOutput(unsigned i)
{
  // Testa se indice i eh valido, usando uma funcao de teste da classe Circuito:
  // se i+1 eh uma id valida para uma saida

  // Provisoriamente, o teste eh sempre falso
  bool indice_valido= C.validIdOutput(i+1);
  if (!indice_valido) return;  // Encerra a funcao sem fazer nada

  // Esse valor (idOutput) deve ser lido a partir de metodos de consulta da classe Circuito

  int idOutput= C.getIdOutput(i+1);

  // Variavel auxiliar
  QLabel *prov;

  // Cria o widget da celula da tabela de saidas
  // Coluna 0 (unica)
  prov = new QLabel;
  prov->setAlignment(Qt::AlignCenter);
  prov->setNum(idOutput);
  ui->tableSaidas->setCellWidget(i,0,prov);
}

// Limpa a tabela verdade
// Deve ser chamada sempre que alguma caracteristica do circuito (porta, saida) for alterada
void MainCircuito::limparTabelaVerdade()
{
  // Esses valores (numInputs, numOutputs)
  // devem ser lidos a partir de metodos de consulta da classe Circuito

  int numInputs= C.getNumInputs();
  int numOutputs=C.getNumOutputs();

  // Variavel auxiliar
  QLabel *prov;

  // Limpa todo o conteudo, inclusive cabecalhos
  ui->tableTabelaVerdade->clear();

  // Recoloca os textos dos cabecalhos na primeira linha
  // Entradas
  if (numInputs > 0)
  {
    prov = new QLabel("ENTRADAS");
    prov->setAlignment(Qt::AlignCenter);
    prov->setStyleSheet("font-weight: bold");
    ui->tableTabelaVerdade->setCellWidget(0,0,prov);
  }
  // Saidas
  if (numOutputs > 0)
  {
    prov = new QLabel("SAIDAS");
    prov->setAlignment(Qt::AlignCenter);
    prov->setStyleSheet("font-weight: bold");
    ui->tableTabelaVerdade->setCellWidget(0,numInputs,prov);
  }
}

void MainCircuito::on_actionSair_triggered()
{
  QCoreApplication::quit();
}

// Exibe a caixa de dialogo para fixar caracteristicas de um novo circuito
void MainCircuito::on_actionNovo_triggered()
{
  emit signShowNewCircuito();
}

// Abre uma caixa de dialogo para ler um arquivo
void MainCircuito::on_actionLer_triggered()
{
  QString fileName = QFileDialog::getOpenFileName(this, tr("Arquivo de circuito"), "../Circuito",
                                                  tr("Circuitos (*.txt);;Todos (*.*)"));

  //tive problemas de conversão usando fileName.toStdsStrin
  //o fileName estava certo mas ao passar para std::string
  //ficava .....\Ãrea de Trabalho, e n era feita a leitura
  //ja q n existe um caminho/repositorio Ãrea de trabalho
  std::string arq = fileName.toLocal8Bit().constData();



  if (!fileName.isEmpty()) {
    // Leh o circuito do arquivo com nome "fileName", usando a funcao apropriada da classe Circuito
    // e testa se a leitura deu certo
    // ### falta_fazer(); ###
    // Provisoriamente, o teste eh sempre falso
    bool leitura_OK = (C.ler(arq));

    if (!leitura_OK)
    {
        //std::cout << arq <<std::endl;
      // Exibe uma msg de erro na leitura
      QMessageBox msgBox;
      msgBox.setText("Erro ao ler um circuito a partir do arquivo:\n"+fileName);
      msgBox.exec();
    }

    // Feita a leitura, reexibe todas as tabelas
    redimensionaTabelas();
  }
}

// Abre uma caixa de dialogo para salvar um arquivo
void MainCircuito::on_actionSalvar_triggered()
{
  // Soh pode salvar se o Circuito for valido
  // ### falta_fazer(); ###
  // Provisoriamente, o teste eh sempre falso
  bool circuito_valido = C.valid();
  if (!circuito_valido)
  {
    QMessageBox msgBox;
    msgBox.setText("O Circuito nao esta completamente definido.\nNao pode ser salvo.");
    msgBox.exec();
    return;
  }

  QString fileName = QFileDialog::getSaveFileName(this, tr("Arquivo de circuito"), "../Circuito",
                                                  tr("Circuitos (*.txt);;Todos (*.*)"));

  if (!fileName.isEmpty()) {
    // Salva o circuito no arquivo com nome "fileName", usando a funcao apropriada da classe Circuito
    // FEITO
    // Provisoriamente, o teste eh sempre falso
    std::string arq = fileName.toLocal8Bit().constData();
    bool escrita_OK = C.salvar(arq);
    if (!escrita_OK)
    {
      // Exibe uma msg de erro na leitura
      QMessageBox msgBox;
      msgBox.setText("Erro ao salvar o circuito no arquivo:\n"+fileName);
      msgBox.exec();
    }
  }
}

// Gera e exibe a tabela verdade para o circuito
// Chama a funcao simular da classe circuito
void MainCircuito::on_actionGerar_tabela_triggered()
{
  bool circuito_valido = C.valid();
  if (!circuito_valido)
  {
    QMessageBox msgBox;
    msgBox.setText("O Circuito nao esta completamente definido.\nNao pode ser simulado.");
    msgBox.exec();
    return;
  }

  int numInputs = C.getNumInputs();
  int numOutputs = C.getNumOutputs();
  int numCombinacoesEntrada = (numInputs > 0 ? round(pow(3, numInputs)) : 0);

  std::vector<bool3S> in_circ(numInputs);

  QLabel *prov;
  int i, j;

  for (i = 0; i < numInputs; i++) in_circ[i] = bool3S::UNDEF;

  for (i = 0; i < numCombinacoesEntrada; i++)
  {
    for (j = 0; j < numInputs; j++)
    {
      prov = new QLabel(QString(toChar(in_circ[j])));
      prov->setAlignment(Qt::AlignCenter);
      ui->tableTabelaVerdade->setCellWidget(i + 1, j, prov);
    }

    C.simular(in_circ);

    for (j = 0; j < numOutputs; j++)
    {
      bool3S output = C.getOutput(j + 1);
      prov = new QLabel(QString(toChar(output)));
      prov->setAlignment(Qt::AlignCenter);
      ui->tableTabelaVerdade->setCellWidget(i + 1, j + numInputs, prov);
    }

    j = numInputs - 1;
    while (in_circ[j] == bool3S::TRUE && j >= 0)
    {
      in_circ[j] = bool3S::UNDEF;
      j--;
    }

    if (j >= 0) in_circ[j]++;
  }
}


// Exibe a caixa de dialogo para fixar caracteristicas de uma porta
void MainCircuito::on_tablePortas_activated(const QModelIndex &index)
{
  int idPort = index.row() + 1;

  QString namePort = QString::fromStdString(C.getNamePort(idPort));
  int numInputsPort = C.getNumInputsPort(idPort);

  int idInputPort[4] = {0}; // Inicializa com zeros

  for (int j = 0; j < numInputsPort; j++)
  {
    idInputPort[j] = C.getId_inPort(idPort, j);
  }

  emit signShowModificarPorta(idPort, namePort, numInputsPort,
                              idInputPort[0], idInputPort[1], idInputPort[2], idInputPort[3]);
}

// Exibe a caixa de dialogo para fixar caracteristicas de uma saida
void MainCircuito::on_tableSaidas_activated(const QModelIndex &index)
{
  // Converte de indice de linha para Id de porta
  int idSaida = index.row()+1;

  // Esse valor (idOrigemSaida)
  // deve ser lido a partir de metodo de consulta da classe Circuito
  int idOrigemSaida = C.getIdOutput(idSaida);

  // Informa as caracteristicas atuais da saida (emit signShowModificarSaida)
  emit signShowModificarSaida(idSaida, idOrigemSaida);
}
