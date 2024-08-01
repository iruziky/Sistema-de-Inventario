#include <iostream>
#include <fstream>
#include "GerenciadorClientes.h"
#include <algorithm>

GerenciadorClientes::GerenciadorClientes() {
    carregarClientes();  // Carregar clientes ao iniciar o gerenciador
}

void GerenciadorClientes::salvarClientes() {
    std::ofstream arquivo(arquivoClientes);
    if (arquivo.is_open()) {
        for (const auto& cliente : clientes) {
            arquivo << cliente.nome << "," << cliente.idade << "," << cliente.id << std::endl; // Salvar ID
        }
        arquivo.close();
    } else {
        std::cerr << "Erro ao abrir o arquivo para salvar." << std::endl;
    }
}

void GerenciadorClientes::carregarClientes() {
    std::ifstream arquivo(arquivoClientes);
    if (arquivo.is_open()) {
        std::string linha;
        while (std::getline(arquivo, linha)) {
            size_t pos1 = linha.find(",");
            size_t pos2 = linha.find(",", pos1 + 1);
            if (pos1 != std::string::npos && pos2 != std::string::npos) {
                std::string nome = linha.substr(0, pos1);
                int idade = std::stoi(linha.substr(pos1 + 1, pos2 - pos1 - 1));
                int id = std::stoi(linha.substr(pos2 + 1)); // Ler ID
                clientes.emplace_back(nome, idade, id);
            }
        }
        arquivo.close();
    }
}

void GerenciadorClientes::removerCliente(int id) {
    auto it = std::remove_if(clientes.begin(), clientes.end(), [id](const Cliente& cliente) {
        return cliente.id == id;
    });

    if (it != clientes.end()) {
        clientes.erase(it, clientes.end());
        salvarClientes(); // Salvar após remover o cliente
        std::cout << "Cliente com ID " << id << " removido com sucesso!" << std::endl;
    } else {
        std::cerr << "Cliente com ID " << id << " não encontrado!" << std::endl;
    }
}

int GerenciadorClientes::gerarId() {
    // Gera o próximo ID com base no maior ID existente
    int maiorId = 0;
    for (const auto& cliente : clientes) {
        if (cliente.id > maiorId) {
            maiorId = cliente.id;
        }
    }
    return maiorId + 1; // Retorna o próximo ID
}

bool GerenciadorClientes::existeCliente(int id) {
    for (const auto& cliente : clientes) {
        if (cliente.id == id) {
            return true; // Cliente encontrado
        }
    }
    return false; // Cliente não encontrado
}

void GerenciadorClientes::adicionarCliente() {
    std::string nome;
    int idade;

    std::cout << "Digite o nome do cliente: ";
    std::cin >> nome;
    std::cout << "Digite a idade do cliente: ";
    std::cin >> idade;

    int novoId = gerarId(); // Gera o ID antes de adicionar o cliente
    clientes.emplace_back(nome, idade, novoId); // Passa o ID para o cliente
    salvarClientes();  // Salvar após adicionar um cliente
    std::cout << "Cliente adicionado: " << nome << ", ID: " << novoId << std::endl;
}

void GerenciadorClientes::editarCliente() {
    listarClientes();
    int index;
    std::cout << "Digite o índice do cliente a ser editado: ";
    std::cin >> index;

    if (index >= 0 && index < clientes.size()) {
        std::string novoNome;
        int novaIdade;

        std::cout << "Digite o novo nome do cliente: ";
        std::cin >> novoNome;
        std::cout << "Digite a nova idade do cliente: ";
        std::cin >> novaIdade;

        clientes[index].nome = novoNome;
        clientes[index].idade = novaIdade;
        salvarClientes();  // Salvar após editar um cliente
        std::cout << "Cliente atualizado: " << novoNome << std::endl;
    } else {
        std::cerr << "Índice inválido!" << std::endl;
    }
}

void GerenciadorClientes::listarClientes() {
    if (clientes.empty()) {
        std::cout << "Nenhum cliente cadastrado." << std::endl;
        return;
    }

    std::cout << "Lista de Clientes:" << std::endl;
    for (size_t i = 0; i < clientes.size(); ++i) {
        std::cout << i << ": " << clientes[i].nome << ", Idade: " << clientes[i].idade << ", ID: " << clientes[i].id << std::endl; // Mostra o ID
    }
}
