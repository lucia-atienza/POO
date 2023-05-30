#ifndef CADENA_HPP_
#define CADENA_HPP_
#include <iterator> 
#include <iostream>

class Cadena
{
public:
    //constructores
    explicit Cadena(unsigned tam = 0, char car = ' '); 
    Cadena(const char* cad);
    Cadena(const Cadena& cad);
    Cadena(Cadena&& cad); //constructor de movimiento

    unsigned length() const noexcept;
    char* c_str() const noexcept;

    Cadena& operator=(const char* cad) noexcept; 
    Cadena& operator=(const Cadena& cad) noexcept;
    Cadena& operator=(Cadena&& cad) noexcept; //asignacion de movimiento

    Cadena& operator+=(const Cadena& cad) noexcept;
    char operator[](unsigned i) const noexcept;
    char at(unsigned i) const;
    char& operator[](unsigned i) noexcept;
    char& at(unsigned i);
    Cadena substr(unsigned i, unsigned tam) const; 
    
    //iteradores
    typedef char* iterator;
    typedef const char* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    iterator begin() noexcept {return s_;}
    const_iterator begin() const noexcept {return cbegin();}
    const_iterator cbegin() const noexcept {return s_;}
    reverse_iterator rbegin() noexcept {return reverse_iterator(end());}
    const_reverse_iterator rbegin() const noexcept {return const_reverse_iterator(end());}
    const_reverse_iterator crbegin() const noexcept {return const_reverse_iterator(end());}

    iterator end() noexcept {return s_ + tam_;}
    const_iterator end() const noexcept{return cend();}
    const_iterator cend() const noexcept {return s_ + tam_;}
    reverse_iterator rend() noexcept {return reverse_iterator(begin());}
    const_reverse_iterator rend() const noexcept {return const_reverse_iterator(begin());}
    const_reverse_iterator crend() const noexcept {return const_reverse_iterator(begin());}

    ~Cadena();
private:
    char* s_;
    unsigned tam_;
};

Cadena operator+(const Cadena& cad1, const Cadena& cad2) noexcept;
bool operator<(const Cadena& cad1, const Cadena& cad2) noexcept;
bool operator<=(const Cadena& cad1, const Cadena& cad2) noexcept;
bool operator>(const Cadena& cad1, const Cadena& cad2) noexcept;
bool operator>=(const Cadena& cad1, const Cadena& cad2) noexcept;
bool operator==(const Cadena& cad1, const Cadena& cad2) noexcept;
bool operator!=(const Cadena& cad1, const Cadena& cad2) noexcept;

std::istream& operator>>(std::istream& is, Cadena& cad);
std::ostream& operator<<(std::ostream& os, const Cadena& cad);


//metodos observadores
inline char* Cadena::c_str () const noexcept
{
    return s_;
}

inline unsigned Cadena::length() const noexcept
{
    return tam_;
}
namespace std 
{ // Estaremos dentro del espacio de nombres std
    template <> // Es una especialización de una plantilla para Cadena
    struct hash<Cadena> 
    { // Es una clase con solo un operador publico
        size_t operator() (const Cadena& cad) const // El operador función
        {
        hash<string> hs; // Creamos un objeto hash de string
        const char* p = cad.c_str(); // Obtenemos la cadena de la Cadena
        string s(p); // Creamos un string desde una cadena
        size_t res = hs(s); // El hash del string. Como hs.operator()(s);
        return res; // Devolvemos el hash del string
        }
    };
}
#endif //CADENA_HPP_
