#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#include "Pessoa.h"

class Funcionario : public Pessoa {
public:
    std::string cargo;

    Funcionario(std::string n, int i, int id, std::string c) : Pessoa(n, i, id), cargo(c) {}
};

#endif // FUNCIONARIO_H
