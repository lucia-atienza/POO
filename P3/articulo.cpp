#include "articulo.hpp"
#include <iomanip>

Articulo::Articulo(const Cadena& referencia, const Cadena& titulo, const Fecha& fecha, double precio, unsigned stock) :
    referencia_{referencia},
    titulo_{titulo},
    fecha_publi_{fecha},
    precio_{precio},
    stock_{stock}
{}


std::ostream& operator<<(std::ostream& os, const Articulo& art)
{
    os << "[" << art.referencia() << "] " 
       << "\"" << art.titulo() << "\", " << art.f_publi().anno() 
       << ". " << std::fixed << std::setprecision(2) 
       << art.precio() << " €" << std::endl;
    return os;
}