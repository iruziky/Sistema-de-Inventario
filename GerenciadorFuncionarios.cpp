#include <iostream>
#include <fstream>
#include "GerenciadorFuncionarios.h"

GerenciadorFuncionarios::GerenciadorFuncionarios() {
    carregarFuncionarios();  // Carregar funcionários ao iniciar o gerenciador
}

void GerenciadorFuncionarios::salvarFuncionarios() {
    std::ofstream arquivo(arquivoFuncionarios);
    if (arquivo.is_open()) {
        for (const auto& funcionario : funcionarios) {
            arquivo << funcionario.nome << "," << funcionario.idade << "," << funcionario.id << "," << funcionario.cargo << std::endl;
        }
        arquivo.close();
    } else {
        std::cerr << "Erro ao abrir o arquivo para salvar." << std::endl;
    }
}

void GerenciadorFuncionarios::carregarFuncionarios() {
    std::ifstream arquivo(arquivoFuncionarios);
    if (arquivo.is_open()) {
        std::string linha;
        while (std::getline(arquivo, linha)) {
            size_t pos1 = linha.find(",");
            size_t pos2 = linha.find(",", pos1 + 1);
            size_t pos3 = linha.find(",", pos2 + 1);
            if (pos1 != std::string::npos && pos2 != std::string::npos && pos3 != std::string::npos) {
                std::string nome = linha.substr(0, pos1);
                int idade = std::stoi(linha.substr(pos1 + 1, pos2 - pos1 - 1));
                int id = std::stoi(linha.substr(pos2 + 1, pos3 - pos2 - 1));
                std::string cargo = linha.substr(pos3 + 1);
                funcionarios.emplace_back(nome, idade, id, cargo);
            }
        }
        arquivo.close();
    }
}

int GerenciadorFuncionarios::gerarId() {
    // Gera o próximo ID com base no maior ID existente
    int maiorId = 0;
    for (const auto& funcionario : funcionarios) {
        if (funcionario.id > maiorId) {
            maiorId = funcionario.id;
        }
    }
    return maiorId + 1; // Retorna o próximo ID
}

bool GerenciadorFuncionarios::existeFuncionario(int id) {
    for (const auto& funcionario : funcionarios) {
        if (funcionario.id == id) {
            return true; // Funcionário encontrado
        }
    }
    return false; // Funcionário não encontrado
}

void GerenciadorFuncionarios::adicionarFuncionario() {
    std::string nome, cargo;
    int idade;

    std::cout << "Digite o nome do funcionário: ";
    std::cin >> nome;
    std::cout << "Digite a idade do funcionário: ";
    std::cin >> idade;
    std::cout << "Digite o cargo do funcionário: ";
    std::cin >> cargo;

    int id = gerarId(); // Gera o ID automaticamente
    funcionarios.emplace_back(nome, idade, id, cargo);
    salvarFuncionarios();  // Salvar após adicionar um funcionário
    std::cout << "Funcionário adicionado: " << nome << " (ID: " << id << ")" << std::endl;
}

void GerenciadorFuncionarios::listarFuncionarios() {
    if (funcionarios.empty()) {
        std::cout << "Nenhum funcionário cadastrado." << std::endl;
        return;
    }

    std::cout << "Lista de Funcionários:" << std::endl;
    for (const auto& funcionario : funcionarios) {
        std::cout << "ID: " << funcionario.id << ", Nome: " << funcionario.nome << ", Idade: " << funcionario.idade << ", Cargo: " << funcionario.cargo << std::endl;
    }
}
