#include "usuario.hpp"
#include "tarjeta.hpp"
#include "cadena.hpp"
#include <unistd.h>
#include <utility>
#include <random>
#include <cstring>
#include <unordered_set>
#include <iomanip>
#include <set>

//====================================== CLAVE =========================================================

Clave::Clave(const char* cad)
{
    std::random_device random;
    std::uniform_int_distribution<size_t> dist(0,63); //64 = 26letras * 2 + 10 numeros y 2 caracteres
    const char* encrip = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";
    char salt[2];
    if(strlen(cad) < 5)
        throw Incorrecta{CORTA};

    salt[0] = encrip[dist(random)]; 
    salt[1] = encrip[dist(random)];
    
    /*if(crypt(cad, salt) != NULL)
        clave_ = crypt(cad, salt);
    else
       throw Incorrecta{Razon::ERROR_CRYPT};*/
    if (char* aux = crypt(cad, salt))
        clave_ = aux;
    else
        throw Incorrecta{ERROR_CRYPT};
}

bool Clave::verifica(const char* cad) const
{
    return (crypt(cad, clave_.c_str()) == clave_);
}

//============================================= USUARIO =============================================================

std::unordered_set<Cadena> Usuario::usuarios_;

Usuario::Usuario(const Cadena& id, const Cadena& nombre, const Cadena& apellidos, const Cadena& dir, const Clave& clv) : 
    id_{id},
    nombre_{nombre},
    apellidos_{apellidos},
    dir_{dir},
    contrasenna_{clv}
{
    if(!usuarios_.insert(id).second)
        throw Id_duplicado{id_};
}


void Usuario::es_titular_de(Tarjeta& tar)
{
    if(this == tar.titular())
        tarjetas_.insert(std::pair<Numero, Tarjeta*>(tar.numero(), &tar));
}

void Usuario::no_es_titular_de(Tarjeta& tar)
{
    tar.anula_titular();
    tarjetas_.erase(tar.numero());
}

void Usuario::compra(Articulo& art, std::size_t cantidad)
{
    if(cantidad == 0)
        carrito_.erase(&art);
    else
    {
        if(carrito_.find(&art) == carrito_.end())
            carrito_.insert(std::pair<Articulo *, unsigned int>(&art, cantidad));
        else
            carrito_.find(&art)->second = cantidad;
    }
}


std::ostream& operator <<(std::ostream& os, const Usuario& us)
{
    os << us.id() << " [" << us.contrasenna_.clave()
       << "] " << us.nombre() << us.apellidos() << std::endl << us.direccion() << std::endl
       << "Tarjetas:" << std::endl;

    for(auto pos = us.tarjetas_.begin(); pos != us.tarjetas_.end(); pos++)
        os << *pos->second << std::endl;
    return os;
}

std::ostream& mostrar_carro(std::ostream& os, const Usuario& us)
{
    os << "Carrito de compra de " << us.id() << " [Artículos: "<< us.n_articulos() << "]" << std::endl
       << "Cant. Artículo"<< std::endl
       << std::setw(75) << std::setfill('=') << '\n';

    for (auto pos = us.compra().begin(); pos != us.compra().end(); pos++)
        os << pos->second << "\t" << *pos->first << '\n';	
    return os;
}

Usuario::~Usuario()
{
    for(auto pos = tarjetas_.begin(); pos != tarjetas_.end(); pos++)
        pos->second->anula_titular();
    usuarios_.erase(id_);
}
