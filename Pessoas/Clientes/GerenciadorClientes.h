#ifndef GERENCIADORCLIENTES_H
#define GERENCIADORCLIENTES_H

#include "../../GerenciadorBase.h"
#include "Cliente.h"
#include <iostream>

class GerenciadorClientes : public GerenciadorBase<Cliente> {
public:
    GerenciadorClientes() : GerenciadorBase("../../Arquivos_de_Texto/clientes.txt") {}

    void adicionarCliente() {
        std::string nome;
        int idade;

        std::cout << "Digite o nome do cliente: ";
        std::cin >> nome;
        std::cout << "Digite a idade do cliente: ";
        std::cin >> idade;

        int novoId = this->gerarId();
        Cliente novoCliente(nome, idade, novoId);
        this->adicionarItem(novoCliente);
        std::cout << "Cliente adicionado: " << nome << ", ID: " << novoId << std::endl;
    }

    void editarCliente() {
        this->listarItens();
        int id;
        std::cout << "Digite o ID do cliente a ser editado: ";
        std::cin >> id;

        if (this->existeItem(id)) {
            std::string novoNome;
            int novaIdade;

            std::cout << "Digite o novo nome do cliente: ";
            std::cin >> novoNome;
            std::cout << "Digite a nova idade do cliente: ";
            std::cin >> novaIdade;

            Cliente clienteAtualizado(novoNome, novaIdade, id);
            this->editarItem(id, clienteAtualizado);
            std::cout << "Cliente atualizado: " << novoNome << std::endl;
        } else {
            std::cerr << "Cliente com ID " << id << " não encontrado!" << std::endl;
        }
    }

    void removerCliente(int id) {
        this->removerItem(id);
    }

    void listarClientes() {
        this->listarItens();
    }

    bool existeCliente(int id) {
        return this->existeItem(id);
    }
};

#endif // GERENCIADORCLIENTES_H
