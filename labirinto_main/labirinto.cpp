#include <iomanip>
#include <fstream>
#include <list>
#include <cmath> // para sqrt
#include <algorithm>

#include "labirinto.h"

#include "No.h"

using namespace std;

/* ***************** */
/* CLASSE CELULA     */
/* ***************** */

string estadoCel2string(EstadoCel E)
{
  switch(E)
  {
  case EstadoCel::LIVRE:
    return "  ";
  case EstadoCel::OBSTACULO:
    return "##";
  case EstadoCel::ORIGEM:
    return "Or";
  case EstadoCel::DESTINO:
    return "De";
  case EstadoCel::CAMINHO:
    return "..";
  case EstadoCel::INVALIDO:
  default:
    break;
  }
  return "??";
}

/* ***************** */
/* CLASSE LABIRINTO  */
/* ***************** */

/// Construtores

/// Torna o mapa vazio
void Labirinto::clear()
{
  // Esvazia o mapa de qualquer conteudo anterior
  NLin = NCol = 0;
  mapa.clear();
  // Apaga a origem e destino do caminho
  orig = dest = Coord();
}

/// Limpa o caminho anterior
void Labirinto::limpaCaminho()
{
  if (!empty()) for (int i=0; i<NLin; ++i) for (int j=0; j<NCol; ++j)
      {
        if (at(i,j) == EstadoCel::CAMINHO) set(i,j, EstadoCel::LIVRE);
      }
}

/// Retorna o estado da celula correspondente ao i-j-esimo elemento do mapa
EstadoCel Labirinto::at(int i, int j) const
{
  if (i<0 || i>=NLin || j<0 || j>=NCol)
  {
    cerr << "Coordenadas invalidas para o labirinto" << endl;
    return EstadoCel::INVALIDO;
  }
  return mapa.at(NCol*i+j);
}

/// Funcao set de alteracao de valor
void Labirinto::set(int i, int j, EstadoCel valor)
{
  if (i<0 || i>=NLin || j<0 || j>=NCol)
  {
    cerr << "Coordenadas invalidas para o labirinto" << endl;
    return;
  }
  if (valor == EstadoCel::INVALIDO)
  {
    cerr << "Valor invalido para celula" << endl;
    return;
  }
  mapa.at(NCol*i+j) = valor;
}

/// Testa se uma coordenada de celula eh valida para os limites de um mapa
bool Labirinto::coordValida(const Coord& C) const
{
  if (C.lin<0 || C.lin>=NLin || C.col<0 || C.col>=NCol) return false;
  return true;
}

/// Testa se uma celula eh valida e estah livre (nao eh obstaculo) em um mapa
bool Labirinto::celulaValidaLivre(const Coord& C) const
{
  if (!coordValida(C)) return false;
  if (at(C) == EstadoCel::OBSTACULO) return false;
  return true;
}

/// Testa se um movimento MovDe->MovPara eh valido
bool Labirinto::movimentoValido(const Coord& MovDe, const Coord& MovPara) const
{
  // Soh pode mover de e para celulas validas e livres
  if (!celulaValidaLivre(MovDe)) return false;
  if (!celulaValidaLivre(MovPara)) return false;

  // Soh pode mover para celulas vizinhas, ou seja, a diferenca absoluta
  // na coordenada tanto da linha quanto da coluna eh no maximo 1
  Coord delta=abs(MovPara-MovDe);
  if (delta.lin>1 || delta.col>1) return false;

  // Nao pode mover em diagonal se colidir com alguma quina
  // Se o movimento nao for diagonal, esses testes sempre dao certo,
  // pois jah testou que MovDe e MovPara estao livres e ou a linha ou a
  // coluna de MovDe e MovPara sao iguais
  if (!celulaValidaLivre(Coord(MovDe.lin,MovPara.col))) return false;
  if (!celulaValidaLivre(Coord(MovPara.lin,MovDe.col))) return false;

  // Movimento valido
  return true;
}

/// Fixa a origem do caminho a ser encontrado
bool Labirinto::setOrigem(const Coord& C)
{
  if (!celulaValidaLivre(C)) return false;
  // Se for a mesma origen nao faz nada
  if (C==orig) return true;

  limpaCaminho();

  // Apaga a origem anterior no mapa, caso esteja definida
  if (coordValida(orig)) set(orig, EstadoCel::LIVRE);

  // Fixa a nova origem
  orig = C;
  // Marca a nova origem no mapa
  set(orig, EstadoCel::ORIGEM);

  return true;
}

/// Fixa o destino do caminho a ser encontrado
bool Labirinto::setDestino(const Coord& C)
{
  if (!celulaValidaLivre(C)) return false;
  // Se for o mesmo destino nao faz nada
  if (C==dest) return true;

  limpaCaminho();

  // Apaga o destino anterior no mapa, caso esteja definido
  if (coordValida(dest)) set(dest, EstadoCel::LIVRE);

  // Fixa o novo destino
  dest = C;
  // Marca o novo destino no mapa
  set(dest, EstadoCel::DESTINO);

  return true;
}

/// Imprime o mapa no console
void Labirinto::imprimir() const
{
  if (empty())
  {
    cout << "+------------+" << endl;
    cout << "| MAPA VAZIO |" << endl;
    cout << "+------------+" << endl;
    return;
  }

  int i,j;

  // Impressao do cabecalho
  cout << "    ";
  for (j=0; j<NCol; j++)
  {
    cout << setfill('0') << setw(2) << j << setfill(' ') << setw(0) << ' ' ;
  }
  cout << endl;

  cout << "   +";
  for (j=0; j<NCol; j++) cout << "--+" ;
  cout << endl;

  // Imprime as linhas
  for (i=0; i<NLin; i++)
  {
    cout << setfill('0') << setw(2) << i << setfill(' ') << setw(0) << " |" ;
    for (j=0; j<NCol; j++)
    {
      cout << estadoCel2string(at(i,j)) << '|' ;
    }
    cout << endl;

    cout << "   +";
    for (j=0; j<NCol; j++) cout << "--+" ;
    cout << endl;
  }
}

/// Leh um mapa do arquivo nome_arq
/// Caso nao consiga ler do arquivo, cria mapa vazio
/// Retorna true em caso de leitura bem sucedida
bool Labirinto::ler(const string& nome_arq)
{
  // Limpa o mapa
  clear();

  // Abre o arquivo
  ifstream arq(nome_arq);

  // Resultado logico da leitura
  bool resultado=true;

  try
  {
    if (!arq.is_open()) throw 1;

    string prov;
    int numL, numC;
    int valor;

    // Leh o cabecalho
    arq >> prov >> numL >> numC;
    if (!arq.good() || prov != "LABIRINTO" ||
        numL<=0 || numC<=0 ) throw 2;

    // Redimensiona o mapa
    NLin = numL;
    NCol = numC;
    mapa.resize(NLin*NCol);

    // Leh as celulas do arquivo
    for (int i=0; i<NLin; i++)
      for (int j=0; j<NCol; j++)
      {
        arq >> valor;
        if (!arq.good()) throw 3;

        if (valor == 0) set(i,j, EstadoCel::OBSTACULO);
        else set(i,j, EstadoCel::LIVRE);
      }
  }
  catch (int i)
  {
    string msg;
    switch(i)
    {
      case 1: msg = "Erro na abertura"; break;
      case 2: msg = "Dimensoes incompativeis"; break;
      case 3: msg = "Erro na leitura de celula"; break;
      default: msg = "Erro desconhecido"; break;
    }
    cerr << "Arquivo " << nome_arq << " - " << msg << endl;
    resultado = false;
  }
  return resultado;
}

/// Salva um mapa no arquivo nome_arq
/// Retorna true em caso de escrita bem sucedida
bool Labirinto::salvar(const string& nome_arq) const
{
  // Testa o mapa
  if (empty()) return false;

  // Abre o arquivo
  ofstream arq(nome_arq);
  if (!arq.is_open())
  {
    return false;
  }

  // Salva o cabecalho
  arq << "LABIRINTO " << NLin << ' ' << NCol << endl;

  // Salva as celulas do mapa
  for (int i=0; i<NLin; i++)
  {
    for (int j=0; j<NCol; j++)
    {
      if (at(i,j) == EstadoCel::OBSTACULO) arq << 0;
      else arq << 1;
      arq << ' ';
    }
    arq << endl;
  }

  return true;
}

/// Gera um novo mapa aleatorio
/// numL e numC sao as dimensoes do labirinto
/// perc_obst eh o percentual de casas ocupadas (obstaculos) no mapa.
void Labirinto::gerar(int numL, int numC, double perc_obst)
{
  // Testa os parametros
  if (numL<=0) numL = ALTURA_PADRAO_MAPA;
  if (numC<=0) numC = LARGURA_PADRAO_MAPA;
  if (perc_obst <= 0.0 || perc_obst >= 1.0) perc_obst = PERC_PADRAO_OBST;

  // Limpa o mapa
  clear();

  // Inicializa a semente de geracao de numeros aleatorios
  srand(time(nullptr));

  // Assume as dimensoes passadas como parametro
  NLin = numL;
  NCol = numC;

  // Redimensiona o mapa
  mapa.resize(NLin*NCol);

  // Preenche o mapa
  bool obstaculo;
  for (int i=0; i<NLin; i++) for (int j=0; j<NCol; j++)
    {
      obstaculo = (rand()/double(RAND_MAX) <= perc_obst);
      if (obstaculo) set(i,j, EstadoCel::OBSTACULO);
      else set(i,j, EstadoCel::LIVRE);
    }
}

/// *******************************************************************************
/// Calcula o caminho entre a origem e o destino do labirinto usando o algoritmo A*
/// *******************************************************************************

/// Retorna o comprimento do caminho (<0 se nao existe)
///
/// O parametro prof deve conter o numero de nos (profundidade) do caminho encontrado
/// ou <0 caso nao exista caminho.
///
/// O parametro NAbert deve conter o numero de nos em aberto ao termino do algoritmo A*
/// O parametro NFech deve conter o numero de nos em fechado ao termino do algoritmo A*
/// Mesmo quando nao existe caminho, esses parametros devem ter valor atribuido.

double Labirinto::calculaCaminho(int& prof, int& NAbert, int& NFech)
{
  double compr;

  if (empty() || !origDestDefinidos())
  {
    // Impossivel executar o algoritmo
    compr = -1.0;
    prof = -1;
    NAbert = NFech = -1;
    return compr;
  }

  // Apaga um eventual caminho anterior
  limpaCaminho();

  // Testa se origem igual a destino
  if (orig==dest)
  {
    // Caminho tem comprimento e profundidade nula
    compr = 0.0;
    prof = 0;
    // Algoritmo de busca nao gerou nenhum noh
    NAbert = NFech = 0;
    // Caminho tem comprimento nulo
    return compr;
  }

  ////////////////////////////
  //////// FALTA FAZER ///////
  //////////////////////////
 


 


  //Conjunto de N�s
  list <No> Abertos; //Nos abertos
  list <No> Fechados;

    //Criando o N� atual
  No atual;
      Coord orig = getOrig();
      Coord dest = getDest();
        
      atual.pos = getOrig();
      atual.ant = getOrig();
      atual.g = 0;
      atual.h = atual.pos.heuristicaDiag(dest);
      
      //double custo_Total = atual.custoTotal();

      Abertos.push_back(atual);

 //aqui usa mov para indicar a dire��o (movimento que vai fazer)
 Coord mov, mov_ant, mov_viz, prox, viz;

  do {
     //Le e Exclui o primeiro(menor custo) No de aberto
     atual = Abertos.front();
     Abertos.pop_front();
     //acrescenta atual em fechado
     Fechados.push_back(atual);
     // expande se n�o � solu��o
     if (atual.pos != dest) {
         //Calcula movimento anterior
         mov_ant = atual.pos - atual.ant;
         //Gera sucessores de atual
         for (mov.lin = -1; mov.lin <= 1; mov.lin++)
         {
             for (mov.col = -1; mov.col <= 1; mov.col++)
             {     //se mov diferente (0,0), n�o � v�lida
                 if (mov != Coord(0, 0)) {
                     prox = atual.pos + mov;
                     //Testa se pode mover de atual para prox
                     if (movimentoValido(atual.pos, prox)) {
                         //Gera novo sucessor
                         No suc;
                         suc.pos = prox;
                         suc.ant = atual.pos;
                         //Angulo de rota��o  
                         double th;
                         if (mov_ant != Coord(0, 0)) {  //como membros da classe
                             th = acos((mov * mov_ant) / (mov.modulo() * mov_ant.modulo()));
                         }
                         else {
                             th = 0.0;
                         }
                         //Custo passado
                         suc.g = atual.g + (th / 2) + modulo(mov); //como fun��o solta
                         // Estimativa custo futuro
                         suc.h = prox.heuristicaDiag(dest);
                         //custo diferencial por vizinhan�a (8 vizinhos)
                         for (mov_viz.lin = -1; mov_viz.lin <= 1; mov_viz.lin++) {
                             for (mov_viz.col = -1; mov_viz.col <= 1; mov_viz.col++) {
                                 if (mov_viz != Coord(0, 0)) {
                                     viz = suc.pos + mov_viz;
                                     if (!celulaValidaLivre(viz)) {
                                         suc.g = suc.g + 0.0001; 
                                     }
                                 }
                             }
                         }
                         //Assume que n�o existe n� igual ao sucessor
                         bool eh_inedito = true;
                         // Procura em Aberto Noh com pos igual a possuc
                         auto old = find(Abertos.begin(), Abertos.end(), suc.pos);
                         // se EXISTE old em aberto(quando usa o find e n�o encontra nada aponta pro .end)
                         if (old != Abertos.end()) {
                             // testa qual tem menor custo total f =h+g
                             if (suc < *old) {
                                 // Exclui o anterior
                                 Abertos.erase(old);
                             }
                             else {
                                 //n� j� existe
                                 eh_inedito = false;
                             }
                         }
                         else {
                             // procura em fechado n� igual a pos suc(mesma posi��o que suc)
                             auto old = find(Fechados.begin(), Fechados.end(), suc.pos);
                             // se existe old testa qual tem menor custo 
                             if (old != Fechados.end()) {
                                 if (suc < *old) {
                                     Fechados.erase(old);
                                 }
                                 else {
                                     eh_inedito = false;
                                 }
                             }
                         }
                         //Insere em aberto se n�o exsite nem em aberto nem em fechado
                         if (eh_inedito) {
                             //acha big,o 1� N� de aberto com custo total< suc.custoTotal
                             auto big = find_if(Abertos.begin(), Abertos.end(), MaiorQue(suc));
                             Abertos.insert(big, suc);
                         }
                     }
                 }
             }
         }
     }
 } while (atual.pos != dest && !Abertos.empty());
     //disponibiliza o estado final da busca ,quer encontre ou n�o o caminho
         NFech = Fechados.size();
         NAbert = Abertos.size();
         
     // Pode ter terminado porque encontrou a solu��o ou porque n�o h� mais n�s 
         if (atual.pos != dest) {
         //Disponibiliza a informa��o que n�o existe caminho
             compr = -1.0;
             prof = -1;
         }
         else {
         //calcula depois disponibiliza comrpimento e profundidade
             compr = atual.g;
             prof = 1;

             while (atual.ant != orig && prof >= 0)
             {
                 // Assinala a c�lula como pertencente ao caminho
                 set(atual.ant, EstadoCel::CAMINHO);
                 // Procura o antecessor (pai) do atual em Fechado
                 auto pai = find(Fechados.begin(), Fechados.end(), atual.ant);
                 // Testa se pai foi encontrado
                 if ((pai != Fechados.end()))
                 {
                     atual = *pai;
                     prof++;
                 }
                 else
                 {
                     cout << "Erro no algoritimo" << endl;
                     prof= -1;
                 }
             }
         }
  
  return compr;
}
