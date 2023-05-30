#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_
#include <iostream>
#include "cadena.hpp"
#include "fecha.hpp"
#include <set>

class Autor;

class Articulo
{
public:
    typedef std::set<Autor*> Autores;
    class Autores_vacios {};
    Articulo(const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& fecha, double precio);
    const Cadena& referencia() const noexcept { return referencia_; };
    const Cadena& titulo() const noexcept { return titulo_; };
    const Fecha& f_publi() const noexcept { return fecha_publi_; }
    double precio() const noexcept { return precio_; };
    double& precio() { return precio_; };
    const Autores& autores() const noexcept { return autores_; };
    std::ostream& imprimirAutores(std::ostream& os, Autores autores) const;
    virtual void impresion_especifica(std::ostream& os) const = 0; //metodo virtual puro
    virtual ~Articulo();
protected:
    const Autores autores_;
    const Cadena referencia_, titulo_;
    const Fecha fecha_publi_;
    double precio_;
};
inline Articulo::~Articulo() {};
std::ostream& operator<<(std::ostream& os, const Articulo& art); //cambiar


class ArticuloAlmacenable : public Articulo
{
public:
    ArticuloAlmacenable(const Autores& autores, const Cadena& referencia, 
            const Cadena& titulo, const Fecha& fecha, double precio, unsigned stock = 0);
    unsigned stock() const noexcept { return stock_; };
    unsigned& stock() { return stock_; };
    virtual void impresion_especifica(std::ostream& os) const = 0;
    virtual ~ArticuloAlmacenable();
protected:
    unsigned stock_;
};

inline ArticuloAlmacenable::~ArticuloAlmacenable() {};


class Libro : public ArticuloAlmacenable
{
public:
    Libro(const Autores& autores, const Cadena& referencia, const Cadena& titulo, 
            const Fecha& fecha, double precio, unsigned numPags, unsigned stock = 0);
    void impresion_especifica(std::ostream& os) const override;
    unsigned n_pag() const noexcept { return numPags_; };
private:
    const unsigned numPags_;
};


class Cederron : public ArticuloAlmacenable
{
public:
    Cederron(const Autores& autores, const Cadena& referencia, const Cadena& titulo, 
                const Fecha& fecha, double precio, unsigned tam, unsigned stock = 0);
    void impresion_especifica(std::ostream& os) const override;
    unsigned tam() const noexcept { return tam_; };
private:
    const unsigned tam_;
};

class LibroDigital : public Articulo
{
public:
    LibroDigital(const Autores& autores, const Cadena& referencia, const Cadena& titulo, 
                    const Fecha& fecha, double precio, const Fecha& exp);
    const Fecha& f_expir() const noexcept { return f_expir_; };
    void impresion_especifica(std::ostream& os) const override;
private:
    const Fecha f_expir_;
};


class Autor
{
public:
    Autor(const Cadena& nombre, const Cadena& apellido, const Cadena& direccion);
    const Cadena& nombre() const noexcept { return nombre_; };
    const Cadena& apellidos() const noexcept { return apellidos_; };
    const Cadena& direccion() const noexcept { return direccion_; };
private:
    Cadena nombre_, apellidos_, direccion_;
};


#endif //ARTICULO_HPP_
