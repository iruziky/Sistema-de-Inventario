#include <iostream>
#include <fstream>
#include <sstream>
#include "GerenciadorProdutos.h"

GerenciadorProdutos::GerenciadorProdutos() {
    carregarProdutos();  // Carregar produtos ao iniciar o gerenciador
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
                        << static_cast<ProdutoPerecivel*>(produto.get())->dataValidade << ",Perecível" << std::endl;
            } else if (dynamic_cast<ProdutoNaoPerecivel*>(produto.get())) {
                arquivo << produto->nome << ","
                        << produto->descricao << ","
                        << produto->quantidade << ","
                        << produto->preco << ",NÃO PERECÍVEL" << std::endl;
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
            iss.ignore(); // Ignora a vírgula
            iss >> preco;
            iss.ignore(); // Ignora a vírgula
            std::getline(iss, tipo);

            int id = gerarId(); // Gera um ID ao carregar produtos

            if (tipo == "Perecível") {
                std::getline(iss, dataValidade);
                produtos.push_back(std::make_unique<ProdutoPerecivel>(nome, descricao, quantidade, preco, dataValidade, id));
            } else if (tipo == "NÃO PERECÍVEL") {
                produtos.push_back(std::make_unique<ProdutoNaoPerecivel>(nome, descricao, quantidade, preco, id));
            }
        }
        arquivo.close();
    }
}

int GerenciadorProdutos::gerarId() {
    // Gera o próximo ID com base no maior ID existente
    int maiorId = 0;
    for (const auto& produto : produtos) {
        if (produto->id > maiorId) {
            maiorId = produto->id;
        }
    }
    return maiorId + 1; // Retorna o próximo ID
}

bool GerenciadorProdutos::existeProduto(int id) {
    for (const auto& produto : produtos) {
        if (produto->id == id) { // Acesso ao ID do produto
            return true; // Produto encontrado
        }
    }
    return false; // Produto não encontrado
}

void GerenciadorProdutos::adicionarProduto() {
    std::string nome;
    std::string descricao;
    double preco;
    int quantidade;
    char tipoProduto;

    std::cout << "Digite o nome do produto: ";
    std::cin >> nome;
    std::cout << "Digite a descrição do produto: ";
    std::cin.ignore(); // Ignora a nova linha anterior
    std::getline(std::cin, descricao);
    std::cout << "Digite a quantidade do produto: ";
    std::cin >> quantidade;
    std::cout << "Digite o preço do produto: ";
    std::cin >> preco;

    std::cout << "É um produto perecível? (s/n): ";
    std::cin >> tipoProduto;

    int id = gerarId(); // Gera o ID automaticamente

    if (tipoProduto == 's' || tipoProduto == 'S') {
        std::string dataValidade;
        std::cout << "Digite a data de validade (DD/MM/AAAA): ";
        std::cin >> dataValidade;
        produtos.push_back(std::make_unique<ProdutoPerecivel>(nome, descricao, quantidade, preco, dataValidade, id));
    } else {
        produtos.push_back(std::make_unique<ProdutoNaoPerecivel>(nome, descricao, quantidade, preco, id));
    }

    salvarProdutos();  // Salvar após adicionar um produto
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
                  << ", Descrição: " << produto->descricao 
                  << ", Quantidade: " << produto->quantidade 
                  << ", Preço: " << produto->preco 
                  << ", ID: " << produto->id; // Exibe o ID do produto
        if (dynamic_cast<ProdutoPerecivel*>(produto.get())) {
            std::cout << ", Data de Validade: " << static_cast<ProdutoPerecivel*>(produto.get())->dataValidade;
        }
        std::cout << std::endl;
    }
}