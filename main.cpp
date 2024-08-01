#include <iostream>
#include <sstream> // Adicione esta linha
#include "GerenciadorClientes.h"
#include "GerenciadorFuncionarios.h"
#include "GerenciadorProdutos.h"
#include "GerenciadorVendas.h"

int main() {
    GerenciadorClientes gerenciadorClientes;
    GerenciadorFuncionarios gerenciadorFuncionarios;
    GerenciadorProdutos gerenciadorProdutos; // Instância do gerenciador de produtos
    GerenciadorVendas gerenciadorVendas(gerenciadorClientes, gerenciadorFuncionarios, gerenciadorProdutos); // Cria a instância do gerenciador de vendas
    int opcao;

    do {
        std::cout << "\nMenu Principal:\n";
        std::cout << "1. Gerenciar Clientes\n";
        std::cout << "2. Gerenciar Funcionários\n";
        std::cout << "3. Gerenciar Produtos\n"; // Nova opção para produtos
        std::cout << "4. Registrar Venda\n"; // Nova opção para registrar vendas
        std::cout << "5. Sair\n";
        std::cout << "Escolha uma opção: ";
        std::cin >> opcao;

        switch (opcao) {
            case 1: {
                int opCliente;
                do {
                    std::cout << "\nMenu de Clientes:\n";
                    std::cout << "1. Adicionar Cliente\n";
                    std::cout << "2. Editar Cliente\n";
                    std::cout << "3. Listar Clientes\n";
                    std::cout << "4. Remover Cliente\n"; // Nova opção para remover cliente
                    std::cout << "5. Voltar\n";
                    std::cout << "Escolha uma opção: ";
                    std::cin >> opCliente;

                    switch (opCliente) {
                        case 1: gerenciadorClientes.adicionarCliente(); break;
                        case 2: gerenciadorClientes.editarCliente(); break;
                        case 3: gerenciadorClientes.listarClientes(); break;
                        case 4: {
                            int idCliente;
                            std::cout << "Digite o ID do cliente a ser removido: ";
                            std::cin >> idCliente;
                            gerenciadorClientes.removerCliente(idCliente); // Chama a função de remover cliente
                            break;
                        }
                        case 5: break;
                        default: std::cerr << "Opção inválida! Tente novamente." << std::endl;
                    }
                } while (opCliente != 5);
                break;
            }
            case 2: {
                int opFuncionario;
                do {
                    std::cout << "\nMenu de Funcionários:\n";
                    std::cout << "1. Adicionar Funcionário\n";
                    std::cout << "2. Listar Funcionários\n";
                    std::cout << "3. Voltar\n";
                    std::cout << "Escolha uma opção: ";
                    std::cin >> opFuncionario;

                    switch (opFuncionario) {
                        case 1: gerenciadorFuncionarios.adicionarFuncionario(); break;
                        case 2: gerenciadorFuncionarios.listarFuncionarios(); break;
                        case 3: break;
                        default: std::cerr << "Opção inválida! Tente novamente." << std::endl;
                    }
                } while (opFuncionario != 3);
                break;
            }
            case 3: {
                int opProduto;
                do {
                    std::cout << "\nMenu de Produtos:\n";
                    std::cout << "1. Adicionar Produto\n";
                    std::cout << "2. Listar Produtos\n";
                    std::cout << "3. Voltar\n";
                    std::cout << "Escolha uma opção: ";
                    std::cin >> opProduto;

                    switch (opProduto) {
                        case 1: gerenciadorProdutos.adicionarProduto(); break;
                        case 2: gerenciadorProdutos.listarProdutos(); break;
                        case 3: break;
                        default: std::cerr << "Opção inválida! Tente novamente." << std::endl;
                    }
                } while (opProduto != 3);
                break;
            }
            case 4: {
                int idCliente, idFuncionario, idProduto;
                double preco;

                // Solicitar ID do cliente
                std::cout << "Digite o ID do cliente: ";
                std::cin >> idCliente;
                // Verificar se o ID do cliente existe
                if (!gerenciadorClientes.existeCliente(idCliente)) {
                    std::cerr << "Cliente não encontrado!" << std::endl;
                    break;
                }

                // Solicitar ID do funcionário
                std::cout << "Digite o ID do funcionário: ";
                std::cin >> idFuncionario;
                // Verificar se o ID do funcionário existe
                if (!gerenciadorFuncionarios.existeFuncionario(idFuncionario)) {
                    std::cerr << "Funcionário não encontrado!" << std::endl;
                    break;
                }

                // Solicitar ID do produto
                std::cout << "Digite o ID do produto: ";
                std::cin >> idProduto;
                // Verificar se o ID do produto existe
                if (!gerenciadorProdutos.existeProduto(idProduto)) {
                    std::cerr << "Produto não encontrado!" << std::endl;
                    break;
                }

                // Solicitar preço da venda
                std::cout << "Digite o preço de venda: ";
                std::cin >> preco;

                // Adicionar venda
                gerenciadorVendas.adicionarVenda(idCliente, idFuncionario, idProduto, preco);
                break;
            }
            case 5:
                std::cout << "Saindo do programa." << std::endl;
                break;
            default:
                std::cerr << "Opção inválida! Tente novamente." << std::endl;
        }
    } while (opcao != 5);

    return 0;
}