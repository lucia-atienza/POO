#include "cadena.hpp"
#include <stdexcept>
#include <cstring>
#include <iomanip>
#include <sstream>

//constructores
Cadena::Cadena(unsigned tam, char car) : tam_{tam}
{
    s_ = new char[tam + 1]; 
    for(unsigned i = 0; i < tam; i++)
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

Cadena::Cadena(Cadena&& cad) : s_{cad.s_}, tam_{cad.tam_}
{
    cad.s_ = nullptr; 
    cad.tam_ = 0;
}


//asignaciones
Cadena& Cadena::operator=(Cadena&& cad) noexcept
{
    if(cad != *this) //evitamos autoasignacion
    {
        tam_ = cad.tam_;
        delete[] s_;
        s_ = cad.s_;
        cad.s_ = nullptr;
        cad.tam_ = 0;
    }
    return *this;
}


Cadena& Cadena::operator=(const char* cad) noexcept
{
    tam_ = strlen(cad);
    delete[] s_;
    s_ = new char[tam_ + 1]; 
    strcpy(s_, cad); 

    return *this ;
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

Cadena operator+(const Cadena& cad1, const Cadena& cad2) noexcept
{
    Cadena aux{cad1};
    aux += cad2;
    return aux;
}


char Cadena::operator[](unsigned i) const noexcept
{
    return s_[i];
}

char Cadena::at(unsigned i) const 
{
    if(i >= tam_ || i < 0)
        throw std::out_of_range{"Índice fuera de rango."};
    else
        return s_[i];
}

char& Cadena::operator[](unsigned i) noexcept
{
    return s_[i];
}

char& Cadena::at(unsigned i)
{
    if(i >= tam_ || i < 0)
        throw std::out_of_range{"Índice fuera de rango."};
    else
        return s_[i];
        
}

Cadena Cadena::substr(unsigned i, unsigned tam) const
{
    if(i >= tam_ || tam >= tam_ - i || tam >= tam_)
        throw std::out_of_range{"Índice fuera de rango."};
    else
    {
        Cadena aux{tam};
        for(unsigned int j = 0, k = i; j < tam; j++, k++)
            aux[j] = s_[k];
        return aux;
    } 
}


//destructor
Cadena::~Cadena()
{
    delete[] s_;
}


bool operator<(const Cadena& cad1, const Cadena& cad2) noexcept
{
    return (strcmp(cad1.c_str(),cad2.c_str()) < 0);
}
bool operator>(const Cadena& cad1, const Cadena& cad2) noexcept
{
    return (cad2 < cad1);
}

bool operator<=(const Cadena& cad1, const Cadena& cad2) noexcept
{
   return !(cad2 < cad1);
}

bool operator>=(const Cadena& cad1, const Cadena& cad2) noexcept
{
    return !(cad1 < cad2);
}

bool operator==(const Cadena& cad1, const Cadena& cad2) noexcept
{
    return (strcmp(cad1.c_str(),cad2.c_str()) == 0);
}

bool operator!=(const Cadena& cad1, const Cadena& cad2) noexcept
{
    return !(cad1 == cad2);
}


//sobrecarga
std::istream& operator>>(std::istream& is, Cadena& cad)
{
    unsigned tam = 33, i = 0;
    char* cadenaAux = new char[tam];
    char c, aux;

    while(isspace(is.get()) != 0 && is.good());

    is.unget();
    
    while(!isspace(static_cast<unsigned char>(c = is.peek())) && i < 32 && is.good())
    {
        aux = is.get();
        if(is.good())
            cadenaAux[i++] = aux;
        
    }
    cadenaAux[i] = '\0';
    cad = cadenaAux;
    delete[] cadenaAux;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Cadena& cad)
{
    os << cad.c_str();
    return os;
}
