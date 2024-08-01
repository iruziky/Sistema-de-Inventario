#ifndef PRODUTO_H
#define PRODUTO_H

#include <string>

class Produto {
public:
    std::string nome;
    std::string descricao;
    int quantidade;
    double preco;
    int id;

    Produto(std::string n, std::string d, int q, double p, int id) : nome(n), descricao(d), quantidade(q), preco(p), id(id) {}
    virtual ~Produto() = default;
    virtual std::string getTipo() const = 0;
};

#endif // PRODUTO_H
