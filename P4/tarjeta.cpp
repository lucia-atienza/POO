#include "tarjeta.hpp"
#include "cadena.hpp"
#include <iomanip>
#include <utility>
#include <unordered_set>
#include <cstring>
#include <algorithm>
#include <functional>
#include <unistd.h>
bool luhn(const Cadena& numero);

struct EsDigito: public std::unary_function<char,bool>
{
    bool operator() (char c) const { return isdigit(c); };
};

struct EsBlanco: public std::unary_function<char,bool>
{
    bool operator() (char c) const { return isspace(c); };
};

//====================================== NUMERO =========================================================
Cadena comprobar(const Cadena& cad)
{
    //compruebo espacios
    Cadena aux1{cad};
    Cadena::iterator fin = std::remove_if(aux1.begin(), aux1.end() + 1, EsBlanco());
    if(aux1.end() + 1 != fin)
        aux1 = aux1.substr(0, std::distance(aux1.begin(), fin-1)); //distance return value : number of increments needed to go from first to last

    Cadena aux2 = Cadena(aux1.c_str()); //nueva cadena sin espacios 
    //compruebo longitud
    if(aux2.length() < 13 || aux2.length() > 19) 
        throw Numero::Incorrecto{Numero::Razon::LONGITUD};
    return aux2;
}

Numero::Numero(Cadena num): num_{comprobar(num)}
{
    if(std::find_if(num_.begin(), num_.end(), std::not1(EsDigito())) != num_.end())
        throw Incorrecto{DIGITOS};
    if(!luhn(num_)) 
        throw Incorrecto{NO_VALIDO};
}

Numero::operator const char*() const noexcept
{
    return num_.c_str();
}

bool operator<(const Numero& n1, const Numero& n2)
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


bool Tarjeta::activa(bool nuevo/*bool nuevo = true*/) noexcept
{
    if(nuevo != activa_)
        activa_ = nuevo;
    return nuevo;
}


std::ostream& operator<<(std::ostream &os, const Tarjeta::Tipo& tipo)
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
            os << "Tipo indeterminado"; 
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

std::ostream& operator<<(std::ostream& os, const Tarjeta& tar)
{
    os << "  " << std::setw(27) << std::setfill('-') << "  \n"
       << "/" << std::setw(28) << std::setfill(' ') << "\\\n"
       << "| " << tar.tipo() << std::endl << "| " << tar.numero() << std::endl 
       << "| " << up(tar.titular()->nombre()) << " " 
       << up(tar.titular()->apellidos()) << std::endl <<  "| Caduca: " 
       << std::setfill('0') << std::setw(2) << tar.caducidad().mes() << '/' 
       << std::setw(2) << tar.caducidad().anno() % 100 << std::endl
       << "\\" << std::setw(28) << std::setfill(' ') << "/\n"
       << "  " << std::setw(27) << std::setfill('-') << "  \n";;
    return os;
}


void Tarjeta::anula_titular()
{
    const_cast<Usuario*&>(usuario_) = nullptr;
    activa_ = false;
}

bool operator<(const Tarjeta& tar1, const Tarjeta& tar2) { return (tar1.numero() < tar2.numero()); };

Tarjeta::~Tarjeta()
{
    if(Usuario* u = const_cast<Usuario*>(usuario_)) //necesito que no sea const
        u->no_es_titular_de(*this);
    numeros_.erase(num_);
}
