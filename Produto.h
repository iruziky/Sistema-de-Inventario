#ifndef PRODUTO_H
#define PRODUTO_H

#include <string>

class Produto {
public:
    std::string nome;
    std::string descricao;
    int quantidade;
    double preco;
    int id; // Novo atributo ID

    Produto(std::string n, std::string d, int q, double p, int id) : nome(n), descricao(d), quantidade(q), preco(p), id(id) {}
    virtual ~Produto() = default; // Adiciona um destrutor virtual
    virtual std::string getTipo() const = 0; // Método virtual puro
};

#endif // PRODUTO_H
