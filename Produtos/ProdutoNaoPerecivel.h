#ifndef PRODUTONAOPERECIVEL_H
#define PRODUTONAOPERECIVEL_H

#include "Produto.h"

class ProdutoNaoPerecivel : public Produto {
public:
    ProdutoNaoPerecivel(std::string n, std::string d, int q, double p, int id) 
        : Produto(n, d, q, p, id) {}

    std::string getTipo() const override {
        return "Nao Perecivel";
    }
};

#endif // PRODUTONAOPERECIVEL_H
