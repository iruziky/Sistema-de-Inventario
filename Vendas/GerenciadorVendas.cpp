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
        std::cerr << "Cliente com ID " << idCliente << " não encontrado!" << std::endl;
        return;
    }

    if (!gerenciadorFuncionarios.existeFuncionario(idFuncionario)) {
        std::cerr << "Funcionário com ID " << idFuncionario << " não encontrado!" << std::endl;
        return;
    }

    if (!gerenciadorProdutos.existeProduto(idProduto)) {
        std::cerr << "Produto com ID " << idProduto << " não encontrado!" << std::endl;
        return;
    }

    Venda novaVenda(idCliente, idFuncionario, idProduto, precoFinal);
    vendas.push_back(novaVenda);
    
    salvarVendas();
    std::cout << "Venda registrada com sucesso!" << std::endl;
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

