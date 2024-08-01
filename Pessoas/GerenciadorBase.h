#ifndef GERENCIADORBASE_H
#define GERENCIADORBASE_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

template<typename T>
class GerenciadorBase {
protected:
    std::string arquivo;
    std::vector<T> itens;

    void salvarItens() {
        std::ofstream arquivoSaida(arquivo);
        if (arquivoSaida.is_open()) {
            for (const auto& item : itens) {
                arquivoSaida << item.toString() << std::endl;
            }
            arquivoSaida.close();
        } else {
            std::cerr << "Erro ao abrir o arquivo para salvar." << std::endl;
        }
    }

    void carregarItens() {
        std::ifstream arquivoEntrada(arquivo);
        if (arquivoEntrada.is_open()) {
            std::string linha;
            while (std::getline(arquivoEntrada, linha)) {
                T item;
                item.fromString(linha);
                itens.push_back(item);
            }
            arquivoEntrada.close();
        }
    }

    int gerarId() {
        int maiorId = 0;
        for (const auto& item : itens) {
            if (item.id > maiorId) {
                maiorId = item.id;
            }
        }
        return maiorId + 1;
    }

public:
    GerenciadorBase(const std::string& arquivo) : arquivo(arquivo) {
        carregarItens();
    }

    void adicionarItem(const T& item) {
        itens.push_back(item);
        salvarItens();
    }

    void listarItens() const {
        if (itens.empty()) {
            std::cout << "Nenhum item cadastrado." << std::endl;
            return;
        }
        for (const auto& item : itens) {
            std::cout << item.toString() << std::endl;
        }
    }

    bool existeItem(int id) const {
        return std::any_of(itens.begin(), itens.end(), [id](const T& item) { return item.id == id; });
    }

    void editarItem(int id, const T& novoItem) {
        auto it = std::find_if(itens.begin(), itens.end(), [id](const T& item) { return item.id == id; });
        if (it != itens.end()) {
            *it = novoItem;
            salvarItens();
        }
    }

    void removerItem(int id) {
        auto it = std::remove_if(itens.begin(), itens.end(), [id](const T& item) { return item.id == id; });
        if (it != itens.end()) {
            itens.erase(it, itens.end());
            salvarItens();
        }
    }
};

#endif // GERENCIADORBASE_H
