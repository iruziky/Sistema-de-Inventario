#ifndef PESSOA_H
#define PESSOA_H

#include <string>

class Pessoa {
public:
    std::string nome;
    int idade;
    int id; // Novo atributo

    // Construtor que aceita um ID
    Pessoa(std::string n, int i, int id) : nome(n), idade(i), id(id) {}
};

#endif // PESSOA_H
