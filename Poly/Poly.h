#ifndef _POLY_H_
#define _POLY_H_

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>



using namespace std;

class Poly
{
private:
	int grau;  // grau do polin�mio
	double* a; // coeficientes

public:
	// Construtor default (sem par�metro) cria um polin�mio vazio (grau=-1, a=nullptr)
	Poly();


	// Construtor que recebe o grau e os coeficientes do polin�mio (padr�o)
	explicit Poly(int g);


	// Construtor por c�pia
	Poly(const Poly& p);


	// Operador de atribui��o por c�pia
	Poly& operator=(const Poly& p);


	// Construtor por movimento (op��o 1)
	Poly(Poly&& p);


	// Operador de atribui��o por movimento
	Poly& operator=(Poly&& p);


	// Destrutor
	~Poly();


	// M�todo de consulta para obter o grau do polin�mio
	int getGrau() const;


	// M�todo de consulta para obter o coeficiente
	double getCoef(int i) const;


	// M�todo para alterar o coeficiente
	void setCoef(int i, double novoCoef);


	// Sobrecarga do operador []
	const double operator[](int i) const;



	// Construtor padr�o 2.0 (recriar um Poly)
	void recriar(int novo_grau);


	// Sobrecarga de ==
	bool operator==(const Poly& outro) const;


	// sobrecarga do operador !=
	bool operator!=(const Poly& outro) const;


	// vazio
	bool empty() const;


	// se for 0
	bool isZero() const;


	// usando a biblioteca cmath
	double getValor(double x) const;

	double operator()(double x) const;

	//impress�o
	friend ostream& operator << (ostream& out, const Poly& P);


	// entrada para colocar os coeficientes
	friend istream& operator >> (istream& in, Poly& P);


	//metodo salvar
	bool salvar(string nome_arquivo) const;



	// metodo para ler arquivos                                                    
	bool ler(string nome_arquivo);

	Poly operator-() const;

	Poly operator+(const Poly& p) const;


	Poly operator-(const Poly& p) const;


	Poly operator*(const Poly& p) const;




};
#endif
