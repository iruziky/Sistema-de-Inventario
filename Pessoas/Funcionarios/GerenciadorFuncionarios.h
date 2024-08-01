#ifndef GERENCIADORFUNCIONARIOS_H
#define GERENCIADORFUNCIONARIOS_H

#include "../GerenciadorBase.h"
#include "Funcionario.h"
#include <iostream>

class GerenciadorFuncionarios : public GerenciadorBase<Funcionario> {
public:
    GerenciadorFuncionarios() : GerenciadorBase("Arquivos_de_Texto/funcionarios.txt") {}

    void adicionarFuncionario() {
        std::string nome, cargo;
        int idade;

        std::cout << "Digite o nome do funcionario: ";
        std::cin >> nome;
        std::cout << "Digite a idade do funcionario: ";
        std::cin >> idade;
        std::cout << "Digite o cargo do funcionario: ";
        std::cin >> cargo;

        int id = this->gerarId();
        Funcionario novoFuncionario(nome, idade, id, cargo);
        this->adicionarItem(novoFuncionario);
        std::cout << "Funcionario adicionado: " << nome << " (ID: " << id << ")" << std::endl;
    }

    void editarFuncionario() {
        this->listarItens();
        int id;
        std::cout << "Digite o ID do funcionario a ser editado: ";
        std::cin >> id;

        if (this->existeItem(id)) {
            std::string novoNome, novoCargo;
            int novaIdade;

            std::cout << "Digite o novo nome do funcionario: ";
            std::cin >> novoNome;
            std::cout << "Digite a nova idade do funcionario: ";
            std::cin >> novaIdade;
            std::cout << "Digite o novo cargo do funcionario: ";
            std::cin >> novoCargo;

            Funcionario funcionarioAtualizado(novoNome, novaIdade, id, novoCargo);
            this->editarItem(id, funcionarioAtualizado);
            std::cout << "Funcionario atualizado: " << novoNome << std::endl;
        } else {
            std::cerr << "Funcionario com ID " << id << " nao encontrado!" << std::endl;
        }
    }

    void listarFuncionarios() {
        this->listarItens();
    }

    bool existeFuncionario(int id) {
        return this->existeItem(id);
    }

    void removerFuncionario(int id) {
        this->removerItem(id);
    }
};

#endif // GERENCIADORFUNCIONARIOS_H
