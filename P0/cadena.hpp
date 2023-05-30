#ifndef CADENA_HPP_
#define CADENA_HPP_

class Cadena
{
public:
    explicit Cadena(unsigned tam = 0, char car = ' ');
    Cadena(const char* cad);
    Cadena(const Cadena& cad);

    const unsigned length() const noexcept;
    operator const char*() const noexcept;

    Cadena& operator=(const Cadena& cad) noexcept ;
    Cadena& operator+=(const Cadena& cad) noexcept;
    friend Cadena operator+(const Cadena& cad1, const Cadena& cad2);
    char operator[](unsigned i) const;
    char at(unsigned i) const;
    char& operator[](unsigned i);
    char& at(unsigned i);
    Cadena substr(unsigned i, unsigned tam) const; 

    ~Cadena();
private:
    char* s_;
    unsigned tam_;
};


bool operator<(const Cadena& cad1, const Cadena& cad2) noexcept;
bool operator<=(const Cadena& cad1, const Cadena& cad2) noexcept;
bool operator>(const Cadena& cad1, const Cadena& cad2) noexcept;
bool operator>=(const Cadena& cad1, const Cadena& cad2) noexcept;
bool operator==(const Cadena& cad1, const Cadena& cad2) noexcept;
bool operator!=(const Cadena& cad1, const Cadena& cad2) noexcept;


#endif //CADENA_HPP_
