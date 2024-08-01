#include <iostream>
#include <sstream>
#include "Pessoas/Clientes/GerenciadorClientes.h"
#include "Pessoas/Funcionarios/GerenciadorFuncionarios.h"
#include "Produtos/GerenciadorProdutos.h"
#include "Vendas/GerenciadorVendas.h"

void exibirPainel(std::string nome) {
    std::cout << "\nMenu de " << nome << "s:\n";
    std::cout << "1. Registrar " << nome << ":\n";
    std::cout << "2. Editar " << nome << ":\n";
    std::cout << "3. Listar " << nome << ":\n";
    std::cout << "4. Remover " << nome << ":\n";
    std::cout << "5. Voltar\n";
    std::cout << "Escolha uma opcao: ";
}

int main() {
    GerenciadorClientes gerenciadorClientes;
    GerenciadorFuncionarios gerenciadorFuncionarios;
    GerenciadorProdutos gerenciadorProdutos;
    GerenciadorVendas gerenciadorVendas(gerenciadorClientes, gerenciadorFuncionarios, gerenciadorProdutos);
    int opcao;

    do {
        std::cout << "\nMenu Principal:\n";
        std::cout << "1. Gerenciar Clientes\n";
        std::cout << "2. Gerenciar Funcionarios\n";
        std::cout << "3. Gerenciar Produtos\n";
        std::cout << "4. Gerenciar Vendas\n";
        std::cout << "5. Sair\n";
        std::cout << "Escolha uma opcao: ";
        std::cin >> opcao;

        switch (opcao) {
            case 1: {
                int opCliente;
                do {
                    exibirPainel("Cliente");
                    std::cin >> opCliente;
                    std::cout << "\n";
                    
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
                        default: std::cerr << "Opcao invalida! Tente novamente." << std::endl;
                    }
                } while (opCliente != 5);
                break;
            }
            case 2: {
                int opFuncionario;
                do {
                    exibirPainel("Funcionario");
                    std::cin >> opFuncionario;
                    std::cout << "\n";
                    
                    switch (opFuncionario) {
                        case 1: gerenciadorFuncionarios.adicionarFuncionario(); break;
                        case 2: gerenciadorFuncionarios.editarFuncionario(); break;
                        case 3: gerenciadorFuncionarios.listarFuncionarios(); break;
                        case 4: {
                            int idFuncionario;
                            std::cout << "Digite o ID do funcionario a ser removido: ";
                            std::cin >> idFuncionario;
                            gerenciadorFuncionarios.removerFuncionario(idFuncionario); 
                            break;
                        }
                        case 5: break;
                        default: std::cerr << "Opcao invalida! Tente novamente." << std::endl;
                    }
                } while (opFuncionario != 5);
                break;
            }
            case 3: {
                int opProduto;
                do {
                    exibirPainel("Produto");
                    std::cin >> opProduto;
                    std::cout << "\n";
                    
                    switch (opProduto) {
                        case 1: gerenciadorProdutos.adicionarProduto(); break;
                        case 2: {
                            int idProduto;
                            std::cout << "Digite o ID do produto a ser editado: ";
                            std::cin >> idProduto;
                            if (!gerenciadorProdutos.existeProduto(idProduto)) {
                                std::cerr << "Produto nao encontrado!" << std::endl;
                                break;
                            }
                            gerenciadorProdutos.editarProduto(idProduto);
                            break;
                        }
                        case 3: gerenciadorProdutos.listarProdutos(); break;
                        case 4: {
                            int idProduto;
                            std::cout << "Digite o ID do produto a ser removido: ";
                            std::cin >> idProduto;
                            gerenciadorProdutos.removerProduto(idProduto);
                            break;
                        }
                        case 5: break;
                        default: std::cerr << "Opcao invalida! Tente novamente." << std::endl;
                    }
                } while (opProduto != 5);
                break;
            }
            case 4: {
                int opVenda;
                do {
                    exibirPainel("Venda");
                    std::cin >> opVenda;
                    std::cout << "\n";
                    
                    switch (opVenda) {
                        case 1: {
                            int idCliente, idFuncionario, idProduto;
                            double preco;

                            std::cout << "Digite o ID do cliente: ";
                            std::cin >> idCliente;
                            if (!gerenciadorClientes.existeCliente(idCliente)) {
                                std::cerr << "Cliente nao encontrado!" << std::endl;
                                break;
                            }

                            std::cout << "Digite o ID do funcionario: ";
                            std::cin >> idFuncionario;
                            if (!gerenciadorFuncionarios.existeFuncionario(idFuncionario)) {
                                std::cerr << "Funcionario nao encontrado!" << std::endl;
                                break;
                            }

                            std::cout << "Digite o ID do produto: ";
                            std::cin >> idProduto;
                            if (!gerenciadorProdutos.existeProduto(idProduto)) {
                                std::cerr << "Produto nao encontrado!" << std::endl;
                                break;
                            }

                            std::cout << "Digite o preço de venda: ";
                            std::cin >> preco;

                            gerenciadorVendas.adicionarVenda(idCliente, idFuncionario, idProduto, preco);
                            break;
                        }
                        case 2: {
                            gerenciadorVendas.listarVendas();
                            
                            int idVenda, novoIdCliente, novoIdFuncionario, novoIdProduto;
                            double novoPrecoFinal;

                            std::cout << "Digite o ID da venda a ser editada: ";
                            std::cin >> idVenda;

                            std::cout << "Digite o novo ID do cliente: ";
                            std::cin >> novoIdCliente;
                            if (!gerenciadorClientes.existeCliente(novoIdCliente)) {
                                std::cerr << "Cliente nao encontrado!" << std::endl;
                                break;
                            }

                            std::cout << "Digite o novo ID do funcionario: ";
                            std::cin >> novoIdFuncionario;
                            if (!gerenciadorFuncionarios.existeFuncionario(novoIdFuncionario)) {
                                std::cerr << "Funcionario nao encontrado!" << std::endl;
                                break;
                            }

                            std::cout << "Digite o novo ID do produto: ";
                            std::cin >> novoIdProduto;
                            if (!gerenciadorProdutos.existeProduto(novoIdProduto)) {
                                std::cerr << "Produto nao encontrado!" << std::endl;
                                break;
                            }

                            std::cout << "Digite o novo preço de venda: ";
                            std::cin >> novoPrecoFinal;

                            gerenciadorVendas.editarVenda(idVenda, novoIdCliente, novoIdFuncionario, novoIdProduto, novoPrecoFinal);
                            break;
                        }
                        case 3: gerenciadorVendas.listarVendas(); break;
                        case 4: {
                            gerenciadorVendas.listarVendas();

                            int idVenda;
                            std::cout << "Digite o ID da venda a ser removida: ";
                            std::cin >> idVenda;
                            gerenciadorVendas.removerVenda(idVenda);
                            break;
                        }
                        case 5: break;
                        default: std::cerr << "Opcao invalida! Tente novamente." << std::endl;
                    }
                } while (opVenda != 5);
                break;
            }
            case 5:
                std::cout << "Saindo do programa." << std::endl;
                break;
            default:
                std::cerr << "Opcao invalida! Tente novamente." << std::endl;
        }
    } while (opcao != 5);

    return 0;
}
