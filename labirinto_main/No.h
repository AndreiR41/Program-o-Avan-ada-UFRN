#pragma once
#include "coord.h"
struct No {
    Coord pos;//posição do noh
    Coord ant;//posição do antecessor
    double g; //custo passado
    double h;//custo futuro

    
    //construtores
    No() : pos(Coord(-1, -1)), ant(Coord(-1, -1)), g(-1), h(-1) {}

    No(Coord& p, Coord& a, double g, double h) : pos(p), ant(a), g(g), h(h) {}


    //custo total
    double custoTotal() const {
        return g + h;
    }

    //sobrecarga operadores
    bool operator<(const No& j) const {

        return custoTotal() < j.custoTotal();

    }

    bool operator==(const Coord& s) const {
        return s == pos; 
    };


    

};

//Functor para determinar o maior
struct MaiorQue {

    No a;

    MaiorQue(No& a) {
        this->a = a;
    }

    bool operator()(const No& b) const {
        return a.custoTotal() < b.custoTotal();
    }
};



