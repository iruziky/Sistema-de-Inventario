#ifndef CLIENTE_H
#define CLIENTE_H

#include "../Pessoa.h"
#include <sstream>

class Cliente : public Pessoa {
public:
    Cliente(std::string n = "", int i = 0, int id = 0) : Pessoa(n, i, id) {}

    std::string toString() const override {
        std::ostringstream oss;
        oss << id << "," << nome << "," << idade;
        return oss.str();
    }

    void fromString(const std::string& str) override {
        std::istringstream iss(str);
        char delimiter;
        iss >> id >> delimiter;
        std::getline(iss, nome, ',');
        iss >> idade;
    }
};

#endif // CLIENTE_H
