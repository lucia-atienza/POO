#include <iostream>
#include "cadena.hpp"
#include <stdexcept>
#include <cstring>

Cadena::Cadena(unsigned tam, char car) : tam_{tam}
{
    s_ = new char[tam + 1]; 
    for (unsigned i = 0; i < tam; i++)
        s_[i] = car;
    s_[tam_] = '\0';
}

Cadena::Cadena(const Cadena& cad) : tam_{cad.length()}
{
    s_ = new char[cad.tam_ + 1];
    strcpy(s_, cad.s_);
}

Cadena::Cadena(const char* cad) : tam_(std::strlen(cad))
{
    s_ = new char[std::strlen(cad) + 1];
    strcpy(s_, cad);
    s_[tam_] = '\0';
}

Cadena::operator const char*() const noexcept
{
    return s_;
}

const unsigned Cadena::length() const noexcept
{
    return tam_;
}

Cadena& Cadena::operator=(const Cadena& cad) noexcept
{
    if(cad != *this)
    {
        delete[] s_;
        s_ = new char[cad.tam_ + 1];
        tam_ = cad.tam_;
        std::strcpy(s_, cad.s_);
    }
    return *this;
}

Cadena& Cadena::operator+=(const Cadena& cad) noexcept
{
    Cadena aux{*this};
    delete[] s_;
    s_ = new char[aux.tam_ + cad.tam_ + 1];
    tam_ = aux.tam_ + cad.tam_;
    std::strcpy(s_, aux.s_);
    std::strcat(s_, cad.s_);

    return *this;
}

Cadena operator+(const Cadena& cad1, const Cadena& cad2)
{
    Cadena aux{cad1};
    aux += cad2;
    return aux;
}


char Cadena::operator[](unsigned i) const
{
    return s_[i];
}

char Cadena::at(unsigned i) const
{
    if(i >= tam_ || i < 0)
        throw std::out_of_range{"Indice fuera de rango."};
    else
        return s_[i];
}

char& Cadena::operator[](unsigned i)
{
    return s_[i];
}

char& Cadena::at(unsigned i)
{
    if(i >= tam_ || i < 0)
        throw std::out_of_range{"Indice fuera de rango."};
    else
        return s_[i];
        
}

Cadena Cadena::substr(unsigned i, unsigned tam) const
{
    if(i >= tam_ || tam >= tam_ - i || tam >= tam_)
        throw std::out_of_range{"Indice fuera de rango."};
    else
    {
        Cadena aux;
        aux.tam_ = tam;
        aux.s_ = new char[tam + 1];
        for(unsigned k = 0, j = i; k < tam; j++, k++)
            aux.s_[k] = s_[j];
        aux.s_[tam_] = '\0';
        return aux;
    } 
}



Cadena::~Cadena()
{
    delete[] s_;
}


bool operator<(const Cadena& cad1, const Cadena& cad2) noexcept
{
    return (strcmp(cad1,cad2) < 0);
}
bool operator>(const Cadena& cad1, const Cadena& cad2) noexcept
{
    return (strcmp(cad1,cad2) > 0);
}

bool operator<=(const Cadena& cad1, const Cadena& cad2) noexcept
{
   return !(cad1 > cad2);
}

bool operator>=(const Cadena& cad1, const Cadena& cad2) noexcept
{
    return !(cad1 < cad2);
}

bool operator==(const Cadena& cad1, const Cadena& cad2) noexcept
{
    return (strcmp(cad1,cad2) == 0);
}

bool operator!=(const Cadena& cad1, const Cadena& cad2) noexcept
{
    return !(cad1 == cad2);
}
