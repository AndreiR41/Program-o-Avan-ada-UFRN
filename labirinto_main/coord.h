#ifndef _COORD_H_
#define _COORD_H_
#include <iostream>
#include <cmath>

/// As coordenadas de uma celula do mapa
struct Coord
{
public:
  int lin,col;

  /// Construtores
  Coord(): lin(-1), col(-1) {}
  Coord(int L, int C): lin(L), col(C) {}

  // Comparacao
  bool operator==(const Coord& C) const {return lin==C.lin && col==C.col;}
  bool operator!=(const Coord& C) const {return !operator==(C);}

  // Valor absoluto de uma coordenada
  Coord abs() const {return Coord(::abs(lin), ::abs(col));}

  // Modulo
  double modulo() const {return sqrt(lin*lin + col*col);}

  // Soma e subtracao
  Coord operator+(const Coord& C) const {return Coord(lin+C.lin, col+C.col);}
  Coord operator-(const Coord& C) const {return Coord(lin-C.lin, col-C.col);}

  // Produto escalar
  double operator*(const Coord& C) const {return lin*C.lin + col*C.col;}


  //DISTANCIA DIAGONAL
  double heuristicaDiag(Coord& C) const {

	  double dcol = col - C.col;//variação coluna
	  double dlin = lin - C.lin;//variação linha

	  double mod_dlin = fabs(dlin);//Módulo da variação da linha
	  double mod_dcol = fabs(dcol);//Módulo da varaiação da coluna

	  double dmin = std::min(mod_dlin, mod_dcol); //minimo dos módulos

	  double ddif = mod_dlin - mod_dcol;//diferença entre os módulos
	  

	  double hrot;//fator adcional opcional
	  if (dlin == 0.0 || dcol == 0.0 || dcol == dlin) {
		  hrot = 0.0;
	  }//arrumar esse pi
	  else { 
		  hrot= ((3.14159265358) / 4) / 2; 
	  }

	  //ℎ = √2 ∙ min(|Δ𝑙𝑖𝑛|, |Δ𝑐𝑜𝑙|) + abs(| 𝛥𝑙𝑖𝑛 | − | 𝛥𝑐𝑜𝑙 | ) + ℎrot
	  return sqrt(2.0) * dmin + fabs(ddif) + hrot;

  }
};

/// Formas alternativas de uso de funcoes membros como funcoes classicas
inline Coord abs(const Coord& C) {return C.abs();}
inline double modulo(const Coord& C) {return C.modulo();}

/// Funcoes de E/S de coordenadas
std::istream& operator>>(std::istream& I, Coord& C);
std::ostream& operator<<(std::ostream& O, const Coord& C);



#endif // _COORD_H_
