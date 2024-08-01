#ifndef GERENCIADORFUNCIONARIOS_H
#define GERENCIADORFUNCIONARIOS_H

#include "../../GerenciadorBase.h"
#include "Funcionario.h"
#include <iostream>

class GerenciadorFuncionarios : public GerenciadorBase<Funcionario> {
public:
    GerenciadorFuncionarios() : GerenciadorBase("../../Arquivos_de_Texto/funcionarios.txt") {}

    void adicionarFuncionario() {
        std::string nome, cargo;
        int idade;

        std::cout << "Digite o nome do funcionário: ";
        std::cin >> nome;
        std::cout << "Digite a idade do funcionário: ";
        std::cin >> idade;
        std::cout << "Digite o cargo do funcionário: ";
        std::cin >> cargo;

        int id = this->gerarId();
        Funcionario novoFuncionario(nome, idade, id, cargo);
        this->adicionarItem(novoFuncionario);
        std::cout << "Funcionário adicionado: " << nome << " (ID: " << id << ")" << std::endl;
    }

    void listarFuncionarios() {
        this->listarItens();
    }

    bool existeFuncionario(int id) {
        return this->existeItem(id);
    }

    void editarFuncionario() {
        this->listarItens();
        int id;
        std::cout << "Digite o ID do funcionário a ser editado: ";
        std::cin >> id;

        if (this->existeItem(id)) {
            std::string novoNome, novoCargo;
            int novaIdade;

            std::cout << "Digite o novo nome do funcionário: ";
            std::cin >> novoNome;
            std::cout << "Digite a nova idade do funcionário: ";
            std::cin >> novaIdade;
            std::cout << "Digite o novo cargo do funcionário: ";
            std::cin >> novoCargo;

            Funcionario funcionarioAtualizado(novoNome, novaIdade, id, novoCargo);
            this->editarItem(id, funcionarioAtualizado);
            std::cout << "Funcionário atualizado: " << novoNome << std::endl;
        } else {
            std::cerr << "Funcionário com ID " << id << " não encontrado!" << std::endl;
        }
    }

    void removerFuncionario(int id) {
        this->removerItem(id);
    }
};

#endif // GERENCIADORFUNCIONARIOS_H
