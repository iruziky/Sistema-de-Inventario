#ifndef VENDA_H
#define VENDA_H

class Venda {
public:
    int idCliente;
    int idFuncionario;
    int idProduto;
    double precoFinal;

    Venda(int cliente, int funcionario, int produto, double preco) 
        : idCliente(cliente), idFuncionario(funcionario), idProduto(produto), precoFinal(preco) {}
};

#endif // VENDA_H
