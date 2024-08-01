#ifndef GERENCIADORCLIENTES_H
#define GERENCIADORCLIENTES_H

#include <vector>
#include "Cliente.h"

class GerenciadorClientes {
private:
    const std::string arquivoClientes = "clientes.txt";
    std::vector<Cliente> clientes;

    void salvarClientes();
    void carregarClientes();
    int gerarId(); // Novo método para gerar ID

public:
    GerenciadorClientes();
    void adicionarCliente();
    void editarCliente();
    void removerCliente(int id); // Nova função para remover cliente
    void listarClientes();
    bool existeCliente(int id);
};

#endif // GERENCIADORCLIENTES_H
