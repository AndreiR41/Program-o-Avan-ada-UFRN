#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

#include "Poly.h"

using namespace std;


// Construtor default (sem par�metro) cria um polin�mio vazio (grau=-1, a=nullptr)
Poly::Poly() : grau(-1), a(nullptr)
{
  
}

// Construtor que recebe o grau e os coeficientes do polin�mio (padr�o)
Poly::Poly(int g) : grau(g), a(nullptr)
{
    grau = g;
    // Se o par�metro for maior que zero, o polin�mio deve ter todos os coeficientes nulos, com exce��o do de maior grau, an, que ter� valor 1.0.
    if (grau > 0)
    {
        a = new double[grau + 1];
        // Preenchendo o array
        for (int i = 0; i < grau; i++)
        {
            a[i] = 0.0;
        }
        a[grau] = 1.0;
    }
    // Se o par�metro for nulo, deve criar um polin�mio de grau zero, cujo valor do �nico coeficiente, a0, ser� 0.0.
    else if (g == 0)
    {
        grau = 0;
        a = new double[1];
        a[0] = 0.0;
    }
    else
    {
        *this = Poly(); // Mais um jeito se tiver problema na inicializa��o (N�o precisa)
    }
    
}

// Construtor por c�pia
Poly::Poly(const Poly& p) : grau(p.grau), a(nullptr)
{
    if (grau >= 0)
    {
        a = new double[p.grau + 1];
        for (int i = 0; i <= grau; i++)
        {
            a[i] = p.a[i];
        }
    }
}

// Operador de atribui��o por c�pia
Poly& Poly:: operator=(const Poly& p)
{
    if (this != &p)
    {
        delete[] a;    // Limpa conte�do anterior
        grau = p.grau; // Aloca nova �rea
        // a = p.a; nao precisa
        if (grau >= 0)
        {
            a = new double[p.grau + 1];
        }

        else
        {
            a = nullptr;
        }
        for (int i = 0; i <= grau; i++)
        { // copia valores
            a[i] = p.a[i];
        }
    }
    return *this;
}

// Construtor por movimento (op��o 1)
Poly::Poly(Poly&& p) : grau(p.grau), a(p.a)
{ // sem const
    p.grau = -1;
    p.a = nullptr;
}

// Operador de atribui��o por movimento
Poly& Poly:: operator=(Poly&& p)
{
    delete[] a; // Limpa conte�do anterior
    grau = -1;   // Zera o objeto atribu�do
    a = nullptr;

    swap(grau, p.grau); // Troca os valores do grau
    swap(a, p.a);       // Troca os valores do array de coeficientes

    return *this;
}

// Destrutor
Poly:: ~Poly()
{
    delete[] a;
}

// M�todo de consulta para obter o grau do polin�mio
int Poly::getGrau() const
{
    return grau;
}

// M�todo de consulta para obter o coeficiente
double Poly::getCoef(int i) const
{
    if (i < 0 || i > grau)
    {
        return 0.0;
    }
    return a[i];
}

// M�todo para alterar o coeficiente
void Poly::setCoef(int i, double novoCoef)
{

    // Verifica se o �ndice � v�lido
    if (i < 0 || i > grau)
    {
        cerr << "Erro: �ndice inv�lido." << endl;
        return;
    }

    // Verifica se o novo coeficiente � nulo e se o �ndice corresponde ao coeficiente de maior grau,
    // que n�o pode ser nulo para polin�mios de grau maior que 0
    if (novoCoef == 0 && i == grau && grau > 0)
    {
        cerr << "Erro: o coeficiente de maior grau n�o pode ser nulo, exceto para polin�mios de grau 0." << endl;
        return;
    }


    a[i] = novoCoef;
}

// Sobrecarga do operador []
const double Poly:: operator[](int i) const
{
    return getCoef(i);
}


// Construtor padr�o 2.0 (recriar um Poly)
void Poly::recriar(int novo_grau)
{
    *this = Poly(novo_grau);
}


// Sobrecarga de ==
bool Poly:: operator==(const Poly& outro) const
{
    if (grau != outro.grau)
    {
        return false;
    }


    for (int i = 0; i <= grau; i++)
    {
        if (a[i] != outro.a[i])
        {
            return false;
        }
    }
    return true;
}

// sobrecarga do operador !=
bool Poly:: operator!=(const Poly& outro) const
{
    return !(*this == outro);
}

// vazio
bool Poly::empty() const
{
    if (grau < 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// se for 0
bool Poly::isZero() const
{
    return grau == 0 && a[0] == 0.0;
}

// usando a biblioteca cmath
double Poly::getValor(double x) const
{
    if (empty())
    {
        return 0.0;
    }
    double valor = 0.0;
    for (int i = grau; i >= 0; i--)
    {
        valor += a[i] * pow(x, i);
    }
    return valor;
}

double Poly:: operator()(double x) const
{
    return getValor(x);
}

//impress�o
ostream& operator << (ostream& out, const Poly& P)
{
    // verifica se o polin�mio est� vazio e se sim, retorna o fluxo de sa�da sem imprimir nada.
    if (P.empty())
    {
        return out;
    }
    for (int i = P.grau; i >= 0; i--)
    {
        // coeficiente � verificado se � igual a zero
        if (P.a[i] == 0.0)
        {
            if (i == 0 && P.grau == 0)
            {
                out << P.a[i];
            }
            continue;
        }
        // se for negativo
        if (P.a[i] < 0.0)
        {
            out << "-";
            // se for positivo e n�o for o maior
        }
        else if (i != P.grau)
        {
            out << "+";
        }
        if (abs(P.a[i]) != 1.0 || i == 0)
        {
            out << abs(P.a[i]);
        }
        // impress�o do x

        if (i != 0)
        {
            if (abs(P.a[i]) != 1.0)
            {
                out << "*";
            }
            out << "x";
            if (i > 1)
            {
                out << "^" << i;
            }
        }
    }

    return out;
}

// entrada para colocar os coeficientes
istream& operator >> (istream& in, Poly& P)
{
    if (P.empty()) {
        cout << "Polinomio vazio!" << endl;
        return in;
    }

    double coef;

    for (int i = P.grau; i >= 0; i--) {
        cout << "Coeficiente de grau" << i << "� : ";
        while (true) {
            in >> coef;
            if (i == P.grau && coef == 0 && P.grau > 0) {
                cout << "O maior coeficiente n�o pode ser nulo em um polinomio desse tamanho! Digita denovo:" << endl;
                continue;
            }
            P.setCoef(i, coef);
            break;
        }
    }return in;
}

//metodo salvar
bool Poly::salvar(string nome_arquivo) const
{
    ofstream arquivo(nome_arquivo);
    if (!arquivo.is_open()) {
        return false;
    }
    arquivo << "POLY " << grau << endl;

    // Coeficientes do polin�mio
    if (grau >= 0) {
        for (int i = 0; i <= grau; i++) {
            arquivo << a[i] << " ";
        }
        arquivo << endl;
    }

    arquivo.close();
    return true;
}


// metodo para ler arquivos                                                    
bool Poly::ler(string nome_arquivo) {
    ifstream arquivo(nome_arquivo);
    // se n�o abriu dar falso
    if (!arquivo.is_open()) {
        return false;
    }
    // se a primeira palavra n�o for poly da errado
    string palavra;
    arquivo >> palavra;
    if (palavra != "POLY") {
        arquivo.close();
        return false;
    }
    // se o poly n�o receber o grau
    int grau;
    if (!(arquivo >> grau)) {
        arquivo.close();
        return false; //
    }

    Poly prov(grau); // poly tempor�rio

    double coef;

    for (int i = 0; i <= grau; i++) {
        if (!(arquivo >> coef)) {
            arquivo.close();
            return false; // n�mero de coeficientes menor do que grau + 1
        }
        if (coef != 0.0) { // adiciona apenas coeficientes n�o nulos
            prov.setCoef(i, coef);
        }
    }

    if (prov.getCoef(grau) == 0.0 && grau > 0) {
        arquivo.close();
        return false; // coeficiente de maior grau � 0.0 para um polin�mio de grau >0
    }

    *this = prov; // transfere dados lidos para o polin�mio sendo lido
    arquivo.close();
    return true; // leitura do arquivo conclu�da com sucesso
}



//tornar negativo  
Poly Poly::  operator-() const {
    if (empty()) {  // polin�mio vazio
        return Poly();
    }
    if (isZero()) { // polin�mio nulo
        return Poly(0);
    }

    Poly result(grau);
    for (int i = 0; i <= grau; i++) {
        result.setCoef(i, -a[i]);
    }
    return result;
}

Poly Poly:: operator+(const Poly& p) const
{
    if (empty())
    { // polin�mio vazio
        return p;
    }
    if (p.empty())
    { // polin�mio vazio
        return *this;
    }

    int grau_max = max(grau, p.grau);
    Poly result(grau_max);

    for (int i = 0; i <= grau_max; i++)
    {
        double coef = 0.0;
        if (i <= grau)
        {
            coef += a[i];
        }
        if (i <= p.grau)
        {
            coef += p.a[i];
        }
        result.a[i] = coef;
    }

    // Encontrar o novo grau
    int novo_grau = grau_max;
    while (novo_grau > 0 && result.a[novo_grau] == 0.0)
    {
        novo_grau--;
    }

    // Se o novo grau for diferente do grau inicial do resultado
    if (novo_grau != grau_max)
    {
        // Crie um polin�mio auxiliar com o novo grau
        Poly aux(novo_grau);

        // Copie os coeficientes, at� o novo grau, do resultado para o polin�mio auxiliar
        for (int i = 0; i <= novo_grau; i++)
        {
            aux.a[i] = result.a[i];
        }

        // Fa�a o resultado receber o valor do polin�mio auxiliar
        result = aux;
    }

    return result;
}

Poly Poly:: operator-(const Poly& p) const
{
    return *this + (-p);
}

Poly Poly::  operator*(const Poly& p) const {
    if (empty() || p.empty()) { // polin�mio vazio
        return Poly();
    }
    if (isZero() || p.isZero()) { // polin�mio nulo
        Poly result(0);

        return result;
    }

    int grau_max = grau + p.grau;
    Poly result(grau_max);

    for (int i = 0; i <= grau_max; i++) {
        double coef = 0.0;
        for (int j = 0; j <= i; j++) {
            if (j <= grau && i - j <= p.grau) {
                coef += a[j] * p.a[i - j];
            }
        }
        result.setCoef(i, coef);
    }

    return result;
}





