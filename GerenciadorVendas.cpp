#include <iostream>
#include <fstream>
#include <sstream> // Adicione esta linha
#include "GerenciadorVendas.h"

GerenciadorVendas::GerenciadorVendas(GerenciadorClientes& gc, GerenciadorFuncionarios& gf, GerenciadorProdutos& gp)
    : gerenciadorClientes(gc), gerenciadorFuncionarios(gf), gerenciadorProdutos(gp) {
    carregarVendas(); // Carregar vendas ao iniciar o gerenciador
}

void GerenciadorVendas::adicionarVenda(int idCliente, int idFuncionario, int idProduto, double precoFinal) {
    // A lógica aqui permanece a mesma, mas agora você pode usar os parâmetros passados
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

    // Aqui você deve criar a venda e armazená-la
    Venda novaVenda(idCliente, idFuncionario, idProduto, precoFinal); // Certifique-se de ter a classe Venda implementada
    vendas.push_back(novaVenda);
    
    salvarVendas(); // Salvar as vendas após adicionar uma nova
    std::cout << "Venda registrada com sucesso!" << std::endl;
}

void GerenciadorVendas::salvarVendas() {
    std::ofstream arquivo(arquivoVendas);
    if (arquivo.is_open()) {
        for (const auto& venda : vendas) {
            arquivo << venda.idCliente << "," 
                    << venda.idFuncionario << ","
                    << venda.idProduto << ","
                    << venda.precoFinal << std::endl; // Certifique-se de que os campos estejam corretos na classe Venda
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

            // Leia os dados separados por vírgula
            if (std::getline(iss, linha, ',')) idCliente = std::stoi(linha);
            if (std::getline(iss, linha, ',')) idFuncionario = std::stoi(linha);
            if (std::getline(iss, linha, ',')) idProduto = std::stoi(linha);
            if (std::getline(iss, linha)) precoFinal = std::stod(linha);

            // Cria uma nova venda
            Venda novaVenda(idCliente, idFuncionario, idProduto, precoFinal);
            vendas.push_back(novaVenda);
        }
        arquivo.close();
    } else {
        std::cerr << "Erro ao abrir o arquivo para carregar." << std::endl;
    }
}

