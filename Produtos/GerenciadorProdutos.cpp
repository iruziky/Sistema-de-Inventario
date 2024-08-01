#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "GerenciadorProdutos.h"

GerenciadorProdutos::GerenciadorProdutos() {
    carregarProdutos();
}

void GerenciadorProdutos::salvarProdutos() {
    std::ofstream arquivo(arquivoProdutos);
    if (arquivo.is_open()) {
        for (const auto& produto : produtos) {
            if (dynamic_cast<ProdutoPerecivel*>(produto.get())) {
                arquivo << produto->nome << "," 
                        << produto->descricao << ","
                        << produto->quantidade << ","
                        << produto->preco << ","
                        << static_cast<ProdutoPerecivel*>(produto.get())->dataValidade << ",Perecivel" << std::endl;
            } else if (dynamic_cast<ProdutoNaoPerecivel*>(produto.get())) {
                arquivo << produto->nome << ","
                        << produto->descricao << ","
                        << produto->quantidade << ","
                        << produto->preco << ",NAO PERECIVEL" << std::endl;
            }
        }
        arquivo.close();
    } else {
        std::cerr << "Erro ao abrir o arquivo para salvar." << std::endl;
    }
}

void GerenciadorProdutos::carregarProdutos() {
    std::ifstream arquivo(arquivoProdutos);
    if (arquivo.is_open()) {
        std::string linha;
        while (std::getline(arquivo, linha)) {
            std::istringstream iss(linha);
            std::string nome, descricao, tipo;
            double preco;
            int quantidade;
            std::string dataValidade;

            std::getline(iss, nome, ',');
            std::getline(iss, descricao, ',');
            iss >> quantidade;
            iss.ignore();
            iss >> preco;
            iss.ignore();
            std::getline(iss, tipo);

            int id = gerarId();

            if (tipo == "Perecivel") {
                std::getline(iss, dataValidade);
                produtos.push_back(std::make_unique<ProdutoPerecivel>(nome, descricao, quantidade, preco, dataValidade, id));
            } else if (tipo == "NAO PERECIVEL") {
                produtos.push_back(std::make_unique<ProdutoNaoPerecivel>(nome, descricao, quantidade, preco, id));
            }
        }
        arquivo.close();
    }
}

int GerenciadorProdutos::gerarId() {
    int maiorId = 0;
    for (const auto& produto : produtos) {
        if (produto->id > maiorId) {
            maiorId = produto->id;
        }
    }
    return maiorId + 1;
}

bool GerenciadorProdutos::existeProduto(int id) {
    for (const auto& produto : produtos) {
        if (produto->id == id) {
            return true;
        }
    }
    return false;
}

void GerenciadorProdutos::adicionarProduto() {
    std::string nome;
    std::string descricao;
    double preco;
    int quantidade;
    char tipoProduto;

    std::cout << "Digite o nome do produto: ";
    std::cin >> nome;
    std::cout << "Digite a descricao do produto: ";
    std::cin.ignore();
    std::getline(std::cin, descricao);
    std::cout << "Digite a quantidade do produto: ";
    std::cin >> quantidade;
    std::cout << "Digite o preço do produto: ";
    std::cin >> preco;

    std::cout << "É um produto perecível? (s/n): ";
    std::cin >> tipoProduto;

    int id = gerarId();

    if (tipoProduto == 's' || tipoProduto == 'S') {
        std::string dataValidade;
        std::cout << "Digite a data de validade (DD/MM/AAAA): ";
        std::cin >> dataValidade;
        produtos.push_back(std::make_unique<ProdutoPerecivel>(nome, descricao, quantidade, preco, dataValidade, id));
    } else {
        produtos.push_back(std::make_unique<ProdutoNaoPerecivel>(nome, descricao, quantidade, preco, id));
    }

    salvarProdutos();
    std::cout << "Produto adicionado: " << nome << " (ID: " << id << ")" << std::endl;
}

void GerenciadorProdutos::listarProdutos() {
    if (produtos.empty()) {
        std::cout << "Nenhum produto cadastrado." << std::endl;
        return;
    }

    std::cout << "Lista de Produtos:" << std::endl;
    for (const auto& produto : produtos) {
        std::cout << produto->getTipo() << ": " << produto->nome 
                  << ", Descricao: " << produto->descricao 
                  << ", Quantidade: " << produto->quantidade 
                  << ", Preço: " << produto->preco 
                  << ", ID: " << produto->id;
        if (dynamic_cast<ProdutoPerecivel*>(produto.get())) {
            std::cout << ", Data de Validade: " << static_cast<ProdutoPerecivel*>(produto.get())->dataValidade;
        }
        std::cout << std::endl;
    }
}

void GerenciadorProdutos::editarProduto(int id) {
    auto it = std::find_if(produtos.begin(), produtos.end(), [id](const std::unique_ptr<Produto>& p) { return p->id == id; });
    if (it != produtos.end()) {
        std::string nome, descricao, dataValidade;
        double preco;
        int quantidade;
        char tipoProduto;

        std::cout << "Digite o novo nome do produto: ";
        std::cin >> nome;
        std::cout << "Digite a nova descricao do produto: ";
        std::cin.ignore();
        std::getline(std::cin, descricao);
        std::cout << "Digite a nova quantidade do produto: ";
        std::cin >> quantidade;
        std::cout << "Digite o novo preço do produto: ";
        std::cin >> preco;

        std::cout << "É um produto perecível? (s/n): ";
        std::cin >> tipoProduto;

        if (tipoProduto == 's' || tipoProduto == 'S') {
            std::cout << "Digite a nova data de validade (DD/MM/AAAA): ";
            std::cin >> dataValidade;
            *it = std::make_unique<ProdutoPerecivel>(nome, descricao, quantidade, preco, dataValidade, id);
        } else {
            *it = std::make_unique<ProdutoNaoPerecivel>(nome, descricao, quantidade, preco, id);
        }

        salvarProdutos();
        std::cout << "Produto editado: " << nome << " (ID: " << id << ")" << std::endl;
    } else {
        std::cerr << "Produto com ID " << id << " não encontrado!" << std::endl;
    }
}

void GerenciadorProdutos::removerProduto(int id) {
    auto it = std::remove_if(produtos.begin(), produtos.end(), [id](const std::unique_ptr<Produto>& p) { return p->id == id; });
    if (it != produtos.end()) {
        produtos.erase(it, produtos.end());
        salvarProdutos();
        std::cout << "Produto com ID " << id << " removido." << std::endl;
    } else {
        std::cerr << "Produto com ID " << id << " não encontrado!" << std::endl;
    }
}
