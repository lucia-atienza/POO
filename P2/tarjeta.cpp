#include "tarjeta.hpp"
#include <iomanip>
#include <utility>
#include <unordered_set>
#include <cstring>
#include <algorithm>
#include <functional>

bool luhn(const Cadena& numero) ;

//====================================== NUMERO =========================================================

Cadena quitarEspacios(const Cadena& cad)
{
    Cadena aux{cad};
    Cadena::iterator fin = std::remove_if(aux.begin(), aux.end() + 1, [](char c) { return std::isspace(c); });
    if(aux.end() + 1 != fin)
        aux = aux.substr(0, std::distance(aux.begin(), fin - 1));
    return Cadena(aux.c_str());
}

Cadena comprobar(const Cadena& cad)
{
    Cadena aux = quitarEspacios(cad);
    if(aux.length() < 13 || aux.length() > 19) 
        throw Numero::Incorrecto{Numero::Razon::LONGITUD};
    return aux;
}

Numero::Numero(Cadena num): num_{comprobar(num)}
{
    if(std::count_if(num_.begin(), num_.end(), isdigit) != num_.length()) 
        throw Incorrecto{DIGITOS};
    if(!luhn(num_)) 
        throw Incorrecto{NO_VALIDO};
}

Numero::operator const char*() const noexcept
{
    return num_.c_str();
}

bool operator <(const Numero& n1, const Numero& n2)
{
    return strcmp(n1, n2) < 0;
}

//=================================================TARJETA=============================================================

std::set<Numero> Tarjeta::numeros_;

Tarjeta::Num_duplicado::Num_duplicado(const Numero& num) : num_duplicado_{num} {};
const Numero& Tarjeta::Num_duplicado::que() const { return num_duplicado_; };

Tarjeta::Caducada::Caducada(const Fecha& f) : caducada_{f} {};
const Fecha& Tarjeta::Caducada::cuando() const noexcept{ return caducada_; };

Tarjeta::Tarjeta(const Numero& num, Usuario& usuario, const Fecha& fech) : 
    num_{num}, 
    usuario_{&usuario}, 
    caducidad_{fech}, 
    activa_{true} 
{
    if(Fecha() > fech)
        throw Caducada{caducidad_};

    if(!numeros_.insert(num).second)
        throw Num_duplicado(num_);

    usuario.es_titular_de(*this);
}

Tarjeta::Tipo Tarjeta::tipo() const noexcept
{
    switch(num_[0])
    {
        case '3':
            if(num_[1] == '4' || num_[1] == '7') 
                return AmericanExpress;
            else
                return JCB;
            break;
    
        case '4':
            return VISA;
            break;

        case '5':
            return Mastercard;
            break;

        case '6':
            return Maestro;
            break;

        default:
            return Otro;
            break;
    }
}


const Usuario* Tarjeta::titular() const noexcept { return usuario_; }


bool Tarjeta::activa(bool nuevo) noexcept
{
    if(nuevo != activa_)
        activa_ = nuevo;
    return nuevo;
}


std::ostream& operator <<(std::ostream &os, const Tarjeta::Tipo& tipo)
{
    switch(tipo)
    {
        case Tarjeta::Tipo::AmericanExpress: 
            os << "AmericanExpress"; 
            break;
        case Tarjeta::Tipo::JCB: 
            os << "JCB"; 
            break;
        case Tarjeta::Tipo::VISA: 
            os << "VISA"; 
            break;
        case Tarjeta::Tipo::Mastercard: 
            os << "Mastercard"; 
            break;
        case Tarjeta::Tipo::Maestro: 
            os << "Maestro"; 
            break;
        case Tarjeta::Tipo::Otro: 
            os << "Otro"; 
            break;
    }

    return os;
}

Cadena up(const Cadena& cad)
{
    Cadena aux{cad};
    std::size_t i = 0;
    while(aux[i] != '\0')
    {
        if(islower(aux[i])) 
            aux[i] = toupper(aux[i]);
        i++;
    } 
    return aux;
}

std::ostream& operator <<(std::ostream& os, const Tarjeta& tar)
{
    os << tar.tipo() << std::endl << tar.numero() << std::endl 
       << up(tar.titular()->nombre()) << " " 
       << up(tar.titular()->apellidos()) << std::endl <<  "Caduca: " 
       << std::setfill('0') << std::setw(2) << tar.caducidad().mes() << '/' 
       << std::setw(2) << (tar.caducidad().anno() % 100) << std::endl;
    return os;
}


void Tarjeta::anula_titular()
{
    const_cast<Usuario*&>(usuario_) = nullptr;
    activa_ = false;
}

bool operator <(const Tarjeta& tar1, const Tarjeta& tar2) { return (tar1.numero() < tar2.numero()); };

Tarjeta::~Tarjeta()
{
    if(Usuario* u = const_cast<Usuario*>(usuario_)) //necesito que no sea const
        u->no_es_titular_de(*this);
    numeros_.erase(num_);
}
