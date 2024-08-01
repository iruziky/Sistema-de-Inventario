#ifndef GERENCIADORVENDAS_H
#define GERENCIADORVENDAS_H

#include <vector>
#include "Venda.h"
#include "../Pessoas/Clientes/GerenciadorClientes.h"
#include "../Pessoas/Funcionarios/GerenciadorFuncionarios.h"
#include "../Produtos/GerenciadorProdutos.h"

class GerenciadorVendas {
private:
    const std::string arquivoVendas = "vendas.txt";
    std::vector<Venda> vendas;
    GerenciadorClientes& gerenciadorClientes;
    GerenciadorFuncionarios& gerenciadorFuncionarios;
    GerenciadorProdutos& gerenciadorProdutos;

    void salvarVendas();
    void carregarVendas();

public:
    GerenciadorVendas(GerenciadorClientes& gc, GerenciadorFuncionarios& gf, GerenciadorProdutos& gp);
    void adicionarVenda(int idCliente, int idFuncionario, int idProduto, double precoFinal);
};

#endif // GERENCIADORVENDAS_H
