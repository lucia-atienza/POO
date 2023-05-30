#include "articulo.hpp"
#include <iomanip>

Articulo::Articulo(const Autores& autores, const Cadena& referencia, const Cadena& titulo, 
        const Fecha& fecha, double precio) :
    autores_{autores},
    referencia_{referencia},
    titulo_{titulo},
    fecha_publi_{fecha},
    precio_{precio}
{
    if(autores_.empty()) //true if the range doesn't have any element. (cppreference)
        throw Autores_vacios{};
}

ArticuloAlmacenable::ArticuloAlmacenable(const Autores& autores, const Cadena& referencia, 
        const Cadena& titulo, const Fecha& fecha, double precio, unsigned stock /* unsigned stock = 0*/) :
    Articulo{autores, referencia, titulo, fecha, precio},
    stock_{stock} 
{}

Libro::Libro(const Autores& autores, const Cadena& referencia, const Cadena& titulo, 
        const Fecha& fecha, double precio, unsigned numPags, unsigned stock /* unsigned stock = 0*/) :
    ArticuloAlmacenable{autores, referencia, titulo, fecha, precio, stock},
    numPags_{numPags}
{}

Cederron::Cederron(const Autores& autores, const Cadena& referencia, const Cadena& titulo, 
        const Fecha& fecha, double precio, unsigned tam, unsigned stock /* unsigned stock = 0*/) :
    ArticuloAlmacenable{autores, referencia, titulo, fecha, precio, stock},
    tam_{tam}
{}



LibroDigital::LibroDigital(const Autores& autores, const Cadena& referencia, 
        const Cadena& titulo, const Fecha& fecha, double precio, const Fecha& exp) :
    Articulo{autores, referencia, titulo, fecha, precio},
    f_expir_{exp}
{}


Autor::Autor(const Cadena& nombre, const Cadena& apellido, const Cadena& direccion) :
    nombre_{nombre},
    apellidos_{apellido},
    direccion_{direccion}
{}

void Libro::impresion_especifica(std::ostream& os) const
{
    os << n_pag() << " págs., " << stock() << " unidades.";
}

void Cederron::impresion_especifica(std::ostream& os) const
{
    os << tam() << " MB, " << stock() << " unidades.";
}

void LibroDigital::impresion_especifica(std::ostream& os) const
{
    os << "A la venta hasta el " << f_expir() << ".";
}


std::ostream& operator<<(std::ostream& os, const Articulo& art)
{
    os << "[" << art.referencia() << "] " 
       << "\"" << art.titulo() << "\", de ";

    for(auto pos = art.autores().begin(), aux = pos; pos != art.autores().end(); pos++, aux++)
    {
        if(pos == art.autores().begin())
            os << (*pos)->apellidos();
        else   
            os << ", " << (*pos)->apellidos(); 
    }

    os << ". " << art.f_publi().anno() 
       << ". " << std::fixed << std::setprecision(2) 
       << art.precio() << " €\n\t";
    art.impresion_especifica(os);
    return os;
}