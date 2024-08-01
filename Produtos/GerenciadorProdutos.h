#ifndef GERENCIADORPRODUTOS_H
#define GERENCIADORPRODUTOS_H

#include <vector>
#include <memory>
#include "Produto.h"
#include "ProdutoPerecivel.h"
#include "ProdutoNaoPerecivel.h"

class GerenciadorProdutos {
private:
    const std::string arquivoProdutos = "../Arquivos_de_Texto/produtos.txt";
    std::vector<std::unique_ptr<Produto>> produtos;

    void salvarProdutos();
    void carregarProdutos();
    int gerarId();

public:
    GerenciadorProdutos();
    void adicionarProduto();
    void listarProdutos();
    bool existeProduto(int id);
};

#endif // GERENCIADORPRODUTOS_H
