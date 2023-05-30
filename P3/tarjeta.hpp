#ifndef TARJETA_HPP_
#define TARJETA_HPP_
#include <iostream>
#include "cadena.hpp"
#include "fecha.hpp"
#include "usuario.hpp"
#include "articulo.hpp"
#include <set>

class Usuario;

class Numero
{
public:
    enum Razon
    {
        LONGITUD, 
        DIGITOS, 
        NO_VALIDO
    };

    class Incorrecto
    {
    public:
        Incorrecto(Razon r) : r_{r} {};
        const Razon& razon() const noexcept { return r_; };
    private:
        Razon r_;
    };

    Numero(Cadena num);
    operator const char*() const noexcept;
    
private:
    Cadena num_;
};

bool operator <(const Numero& n1 , const Numero& n2);

class Tarjeta
{
public:
    typedef std::set<Numero> Numeros;
    enum Tipo
    {
        Otro,
        VISA,
        Mastercard,
        Maestro,
        JCB,
        AmericanExpress
    };

    class Caducada
    {
    public:
        Caducada(const Fecha& f);
        const Fecha& cuando() const noexcept;
    private:
        Fecha caducada_;
    };

    class Desactivada {};

    class Num_duplicado
    {
    public:
        Num_duplicado(const Numero& num);
        const Numero& que() const;
    private:
        Numero num_duplicado_;
    };


    Tarjeta(const Numero& num, Usuario& usuario, const Fecha& fech);
    Tarjeta(const Tarjeta& tar) = delete;
    Tarjeta& operator =(const Tarjeta& tar) = delete;

    const Numero& numero() const noexcept;
    const Usuario* titular() const noexcept;
    const Fecha& caducidad() const noexcept;
    bool activa() const noexcept;
    Tipo tipo() const noexcept;


    bool activa(bool nuevo = true) noexcept;
    void anula_titular();

    friend std::ostream& operator <<(std::ostream& os, const Tarjeta& tar);
    friend std::ostream& operator <<(std::ostream& os, const Tarjeta::Tipo& tipo);
    ~Tarjeta();
private:
    const Numero num_;
    Usuario* const usuario_;
    const Fecha caducidad_;
    bool activa_;
    static Numeros numeros_;
};

bool operator <(const Tarjeta& tar1, const Tarjeta& tar2);
inline const Fecha& Tarjeta::caducidad() const noexcept { return caducidad_; };
inline const Numero& Tarjeta::numero() const noexcept { return num_; };
inline bool Tarjeta::activa() const noexcept { return activa_; };


#endif //TARJETA_HPP_