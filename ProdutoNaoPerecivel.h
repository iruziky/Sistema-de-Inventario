#ifndef PRODUTONAOPERECIVEL_H
#define PRODUTONAOPERECIVEL_H

#include "Produto.h"

class ProdutoNaoPerecivel : public Produto {
public:
    ProdutoNaoPerecivel(std::string n, std::string d, int q, double p, int id) 
        : Produto(n, d, q, p, id) {} // Adiciona o id ao construtor

    std::string getTipo() const override {
        return "Não Perecível";
    }
};

#endif // PRODUTONAOPERECIVEL_H
