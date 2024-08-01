#include <iostream>
#include <sstream>
#include "Pessoas/Clientes/GerenciadorClientes.h"
#include "Pessoas/Funcionarios/GerenciadorFuncionarios.h"
#include "Produtos/GerenciadorProdutos.h"
#include "Vendas/GerenciadorVendas.h"

int main() {
    GerenciadorClientes gerenciadorClientes;
    GerenciadorFuncionarios gerenciadorFuncionarios;
    GerenciadorProdutos gerenciadorProdutos;
    GerenciadorVendas gerenciadorVendas(gerenciadorClientes, gerenciadorFuncionarios, gerenciadorProdutos);
    int opcao;

    do {
        std::cout << "\nMenu Principal:\n";
        std::cout << "1. Gerenciar Clientes\n";
        std::cout << "2. Gerenciar Funcionários\n";
        std::cout << "3. Gerenciar Produtos\n";
        std::cout << "4. Registrar Venda\n";
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
                    std::cout << "4. Remover Cliente\n";
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
                            gerenciadorClientes.removerCliente(idCliente);
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
                    std::cout << "2. Editar Funcionário\n";
                    std::cout << "3. Listar Funcionários\n";
                    std::cout << "4. Remover Funcionário\n";
                    std::cout << "5. Voltar\n";
                    std::cout << "Escolha uma opção: ";
                    std::cin >> opFuncionario;

                    switch (opFuncionario) {
                        case 1: 
                            gerenciadorFuncionarios.adicionarFuncionario(); 
                            break;
                        case 2: 
                            gerenciadorFuncionarios.editarFuncionario(); 
                            break;
                        case 3: 
                            gerenciadorFuncionarios.listarFuncionarios(); 
                            break;
                        case 4: {
                            int idFuncionario;
                            std::cout << "Digite o ID do funcionário a ser removido: ";
                            std::cin >> idFuncionario;
                            gerenciadorFuncionarios.removerFuncionario(idFuncionario); 
                            break;
                        }
                        case 5: 
                            break;
                        default: 
                            std::cerr << "Opção inválida! Tente novamente." << std::endl;
                    }
                } while (opFuncionario != 5);
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

                std::cout << "Digite o ID do cliente: ";
                std::cin >> idCliente;
                if (!gerenciadorClientes.existeCliente(idCliente)) {
                    std::cerr << "Cliente não encontrado!" << std::endl;
                    break;
                }

                std::cout << "Digite o ID do funcionário: ";
                std::cin >> idFuncionario;
                if (!gerenciadorFuncionarios.existeFuncionario(idFuncionario)) {
                    std::cerr << "Funcionário não encontrado!" << std::endl;
                    break;
                }

                std::cout << "Digite o ID do produto: ";
                std::cin >> idProduto;
                if (!gerenciadorProdutos.existeProduto(idProduto)) {
                    std::cerr << "Produto não encontrado!" << std::endl;
                    break;
                }

                std::cout << "Digite o preço de venda: ";
                std::cin >> preco;

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