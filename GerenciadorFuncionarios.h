#ifndef GERENCIADORFUNCIONARIOS_H
#define GERENCIADORFUNCIONARIOS_H

#include <vector>
#include "Funcionario.h"

class GerenciadorFuncionarios {
private:
    const std::string arquivoFuncionarios = "funcionarios.txt";
    std::vector<Funcionario> funcionarios;

    void salvarFuncionarios();
    void carregarFuncionarios();
    int gerarId(); // Método para gerar ID

public:
    GerenciadorFuncionarios();
    void adicionarFuncionario();
    void listarFuncionarios();
    bool existeFuncionario(int id);
};

#endif // GERENCIADORFUNCIONARIOS_H
