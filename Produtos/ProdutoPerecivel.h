#ifndef PRODUTOPERECIVEL_H
#define PRODUTOPERECIVEL_H

#include "Produto.h"

class ProdutoPerecivel : public Produto {
public:
    std::string dataValidade;

    ProdutoPerecivel(std::string n, std::string d, int q, double p, std::string v, int id) 
        : Produto(n, d, q, p, id), dataValidade(v) {}

    std::string getTipo() const override {
        return "Perecivel";
    }
};

#endif // PRODUTO_PERECIVEL_H
