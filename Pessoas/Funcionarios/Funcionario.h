#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#include "../Pessoa.h"
#include <sstream>

class Funcionario : public Pessoa {
public:
    std::string cargo;

    Funcionario(std::string n = "", int i = 0, int id = 0, std::string c = "") : Pessoa(n, i, id), cargo(c) {}

    std::string toString() const override {
        std::ostringstream oss;
        oss << id << "," << nome << "," << idade << "," << cargo;
        return oss.str();
    }

    void fromString(const std::string& str) override {
        std::istringstream iss(str);
        char delimiter;
        iss >> id >> delimiter;
        std::getline(iss, nome, ',');
        iss >> idade >> delimiter;
        std::getline(iss, cargo, ',');
    }
};

#endif // FUNCIONARIO_H
