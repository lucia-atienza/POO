#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_
#include <iostream>
#include "cadena.hpp"
#include "fecha.hpp"

class Articulo
{
public:
    Articulo(const Cadena& referencia, const Cadena& titulo, const Fecha& fecha, double precio, unsigned stock = 0);
    const Cadena& referencia() const noexcept { return referencia_; };
    const Cadena& titulo() const noexcept { return titulo_; };
    const Fecha& f_publi() const noexcept { return fecha_publi_; }
    double precio() const noexcept { return precio_; };
    double& precio() { return precio_; };
    unsigned stock() const noexcept { return stock_; };
    unsigned& stock() { return stock_; };

private:
    const Cadena referencia_;
    const Cadena titulo_;
    const Fecha fecha_publi_;
    double precio_;
    unsigned stock_;
};

std::ostream& operator <<(std::ostream& os, const Articulo& art);

#endif //ARTICULO_HPP_
