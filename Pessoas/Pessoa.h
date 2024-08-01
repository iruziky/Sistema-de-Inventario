#ifndef PESSOA_H
#define PESSOA_H

#include <string>

class Pessoa {
public:
    std::string nome;
    int idade;
    int id;

    Pessoa(std::string n = "", int i = 0, int id = 0) : nome(n), idade(i), id(id) {}

    virtual std::string toString() const = 0;
    virtual void fromString(const std::string& str) = 0;
};

#endif // PESSOA_H
