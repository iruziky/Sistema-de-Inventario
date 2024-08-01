#include <iostream>
#include <fstream>
#include <sstream>
#include "GerenciadorVendas.h"

GerenciadorVendas::GerenciadorVendas(GerenciadorClientes& gc, GerenciadorFuncionarios& gf, GerenciadorProdutos& gp)
    : gerenciadorClientes(gc), gerenciadorFuncionarios(gf), gerenciadorProdutos(gp) {
    carregarVendas();
}

void GerenciadorVendas::adicionarVenda(int idCliente, int idFuncionario, int idProduto, double precoFinal) {
    if (!gerenciadorClientes.existeCliente(idCliente)) {
        std::cerr << "Cliente com ID " << idCliente << " nao encontrado!" << std::endl;
        return;
    }

    if (!gerenciadorFuncionarios.existeFuncionario(idFuncionario)) {
        std::cerr << "Funcionario com ID " << idFuncionario << " nao encontrado!" << std::endl;
        return;
    }

    if (!gerenciadorProdutos.existeProduto(idProduto)) {
        std::cerr << "Produto com ID " << idProduto << " nao encontrado!" << std::endl;
        return;
    }

    Venda novaVenda(idCliente, idFuncionario, idProduto, precoFinal);
    vendas.push_back(novaVenda);
    
    salvarVendas();
    std::cout << "Venda registrada com sucesso!" << std::endl;
}

void GerenciadorVendas::listarVendas() const {
    for (const auto& venda : vendas) {
        std::cout << "ID Cliente: " << venda.idCliente
                  << ", ID Funcionario: " << venda.idFuncionario
                  << ", ID Produto: " << venda.idProduto
                  << ", Preco Final: " << venda.precoFinal << std::endl;
    }
}

void GerenciadorVendas::editarVenda(int idVenda, int novoIdCliente, int novoIdFuncionario, int novoIdProduto, double novoPrecoFinal) {
    for (auto& venda : vendas) {
        if (venda.idCliente == idVenda) { // Aqui você pode querer usar um ID específico para a venda
            if (!gerenciadorClientes.existeCliente(novoIdCliente)) {
                std::cerr << "Cliente com ID " << novoIdCliente << " nao encontrado!" << std::endl;
                return;
            }

            if (!gerenciadorFuncionarios.existeFuncionario(novoIdFuncionario)) {
                std::cerr << "Funcionario com ID " << novoIdFuncionario << " nao encontrado!" << std::endl;
                return;
            }

            if (!gerenciadorProdutos.existeProduto(novoIdProduto)) {
                std::cerr << "Produto com ID " << novoIdProduto << " nao encontrado!" << std::endl;
                return;
            }

            venda.idCliente = novoIdCliente;
            venda.idFuncionario = novoIdFuncionario;
            venda.idProduto = novoIdProduto;
            venda.precoFinal = novoPrecoFinal;

            salvarVendas();
            std::cout << "Venda editada com sucesso!" << std::endl;
            return;
        }
    }
    std::cerr << "Venda com ID " << idVenda << " nao encontrada!" << std::endl;
}

void GerenciadorVendas::removerVenda(int idVenda) {
    auto it = std::remove_if(vendas.begin(), vendas.end(), [idVenda](const Venda& venda) {
        return venda.idCliente == idVenda; // Aqui também pode-se usar um ID específico de venda
    });

    if (it != vendas.end()) {
        vendas.erase(it, vendas.end());
        salvarVendas();
        std::cout << "Venda removida com sucesso!" << std::endl;
    } else {
        std::cerr << "Venda com ID " << idVenda << " nao encontrada!" << std::endl;
    }
}

void GerenciadorVendas::salvarVendas() {
    std::ofstream arquivo(arquivoVendas);
    if (arquivo.is_open()) {
        for (const auto& venda : vendas) {
            arquivo << venda.idCliente << "," 
                    << venda.idFuncionario << ","
                    << venda.idProduto << ","
                    << venda.precoFinal << std::endl;
        }
        arquivo.close();
    } else {
        std::cerr << "Erro ao abrir o arquivo para salvar." << std::endl;
    }
}

void GerenciadorVendas::carregarVendas() {
    std::ifstream arquivo(arquivoVendas);
    if (arquivo.is_open()) {
        std::string linha;
        while (std::getline(arquivo, linha)) {
            std::istringstream iss(linha);
            int idCliente, idFuncionario, idProduto;
            double precoFinal;

            if (std::getline(iss, linha, ',')) idCliente = std::stoi(linha);
            if (std::getline(iss, linha, ',')) idFuncionario = std::stoi(linha);
            if (std::getline(iss, linha, ',')) idProduto = std::stoi(linha);
            if (std::getline(iss, linha)) precoFinal = std::stod(linha);

            Venda novaVenda(idCliente, idFuncionario, idProduto, precoFinal);
            vendas.push_back(novaVenda);
        }
        arquivo.close();
    } else {
        std::cerr << "Erro ao abrir o arquivo para carregar." << std::endl;
    }
}
