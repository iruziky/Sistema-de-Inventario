#ifndef CLIENTE_H
#define CLIENTE_H

#include "Pessoa.h"

class Cliente : public Pessoa {
public:
    Cliente(std::string n, int i, int id) : Pessoa(n, i, id) {} // Construtor atualizado
};

#endif // CLIENTE_H
