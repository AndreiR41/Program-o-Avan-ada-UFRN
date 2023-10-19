#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

#include "Poly.h"

using namespace std;


// Construtor default (sem parâmetro) cria um polinômio vazio (grau=-1, a=nullptr)
Poly::Poly() : grau(-1), a(nullptr)
{
  
}

// Construtor que recebe o grau e os coeficientes do polinômio (padrão)
Poly::Poly(int g) : grau(g), a(nullptr)
{
    grau = g;
    // Se o parâmetro for maior que zero, o polinômio deve ter todos os coeficientes nulos, com exceção do de maior grau, an, que terá valor 1.0.
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
    // Se o parâmetro for nulo, deve criar um polinômio de grau zero, cujo valor do único coeficiente, a0, será 0.0.
    else if (g == 0)
    {
        grau = 0;
        a = new double[1];
        a[0] = 0.0;
    }
    else
    {
        *this = Poly(); // Mais um jeito se tiver problema na inicialização (Não precisa)
    }
    
}

// Construtor por cópia
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

// Operador de atribuição por cópia
Poly& Poly:: operator=(const Poly& p)
{
    if (this != &p)
    {
        delete[] a;    // Limpa conteúdo anterior
        grau = p.grau; // Aloca nova área
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

// Construtor por movimento (opção 1)
Poly::Poly(Poly&& p) : grau(p.grau), a(p.a)
{ // sem const
    p.grau = -1;
    p.a = nullptr;
}

// Operador de atribuição por movimento
Poly& Poly:: operator=(Poly&& p)
{
    delete[] a; // Limpa conteúdo anterior
    grau = -1;   // Zera o objeto atribuído
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

// Método de consulta para obter o grau do polinômio
int Poly::getGrau() const
{
    return grau;
}

// Método de consulta para obter o coeficiente
double Poly::getCoef(int i) const
{
    if (i < 0 || i > grau)
    {
        return 0.0;
    }
    return a[i];
}

// Método para alterar o coeficiente
void Poly::setCoef(int i, double novoCoef)
{

    // Verifica se o índice é válido
    if (i < 0 || i > grau)
    {
        cerr << "Erro: Índice inválido." << endl;
        return;
    }

    // Verifica se o novo coeficiente é nulo e se o índice corresponde ao coeficiente de maior grau,
    // que não pode ser nulo para polinômios de grau maior que 0
    if (novoCoef == 0 && i == grau && grau > 0)
    {
        cerr << "Erro: o coeficiente de maior grau não pode ser nulo, exceto para polinômios de grau 0." << endl;
        return;
    }


    a[i] = novoCoef;
}

// Sobrecarga do operador []
const double Poly:: operator[](int i) const
{
    return getCoef(i);
}


// Construtor padrão 2.0 (recriar um Poly)
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

//impressão
ostream& operator << (ostream& out, const Poly& P)
{
    // verifica se o polinômio está vazio e se sim, retorna o fluxo de saída sem imprimir nada.
    if (P.empty())
    {
        return out;
    }
    for (int i = P.grau; i >= 0; i--)
    {
        // coeficiente é verificado se é igual a zero
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
            // se for positivo e não for o maior
        }
        else if (i != P.grau)
        {
            out << "+";
        }
        if (abs(P.a[i]) != 1.0 || i == 0)
        {
            out << abs(P.a[i]);
        }
        // impressão do x

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
        cout << "Coeficiente de grau" << i << "° : ";
        while (true) {
            in >> coef;
            if (i == P.grau && coef == 0 && P.grau > 0) {
                cout << "O maior coeficiente não pode ser nulo em um polinomio desse tamanho! Digita denovo:" << endl;
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

    // Coeficientes do polinômio
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
    // se não abriu dar falso
    if (!arquivo.is_open()) {
        return false;
    }
    // se a primeira palavra não for poly da errado
    string palavra;
    arquivo >> palavra;
    if (palavra != "POLY") {
        arquivo.close();
        return false;
    }
    // se o poly não receber o grau
    int grau;
    if (!(arquivo >> grau)) {
        arquivo.close();
        return false; //
    }

    Poly prov(grau); // poly temporário

    double coef;

    for (int i = 0; i <= grau; i++) {
        if (!(arquivo >> coef)) {
            arquivo.close();
            return false; // número de coeficientes menor do que grau + 1
        }
        if (coef != 0.0) { // adiciona apenas coeficientes não nulos
            prov.setCoef(i, coef);
        }
    }

    if (prov.getCoef(grau) == 0.0 && grau > 0) {
        arquivo.close();
        return false; // coeficiente de maior grau é 0.0 para um polinômio de grau >0
    }

    *this = prov; // transfere dados lidos para o polinômio sendo lido
    arquivo.close();
    return true; // leitura do arquivo concluída com sucesso
}



//tornar negativo  
Poly Poly::  operator-() const {
    if (empty()) {  // polinômio vazio
        return Poly();
    }
    if (isZero()) { // polinômio nulo
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
    { // polinômio vazio
        return p;
    }
    if (p.empty())
    { // polinômio vazio
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
        // Crie um polinômio auxiliar com o novo grau
        Poly aux(novo_grau);

        // Copie os coeficientes, até o novo grau, do resultado para o polinômio auxiliar
        for (int i = 0; i <= novo_grau; i++)
        {
            aux.a[i] = result.a[i];
        }

        // Faça o resultado receber o valor do polinômio auxiliar
        result = aux;
    }

    return result;
}

Poly Poly:: operator-(const Poly& p) const
{
    return *this + (-p);
}

Poly Poly::  operator*(const Poly& p) const {
    if (empty() || p.empty()) { // polinômio vazio
        return Poly();
    }
    if (isZero() || p.isZero()) { // polinômio nulo
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





