#ifndef USUARIO_HPP_
#define USUARIO_HPP_
#include <iostream>
#include <unistd.h>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include "cadena.hpp"
#include "articulo.hpp"

class Tarjeta; 
class Numero;


class Clave
{
public:
    Clave(const char* cad);
    bool verifica(const char* cad) const;
    const Cadena& clave() const noexcept { return clave_; };
    enum Razon
    {
        CORTA,
        ERROR_CRYPT
    };

    class Incorrecta
    {
    public:
        Incorrecta(const Razon& r) : r_{r} {};
        const Razon& razon() const noexcept { return r_; };
    private:
        Razon r_;
    };

private:
    Cadena clave_;
};

class Articulo;

class Usuario
{
public:
    typedef std::map<Numero, Tarjeta*> Tarjetas;
    typedef std::unordered_map<Articulo*, unsigned int> Articulos;
    typedef std::unordered_set<Cadena> Usuarios;

    class Id_duplicado
    {
    public:
        Id_duplicado(const Cadena& cad) : cad_{cad} {};
        const Cadena& idd() const noexcept { return cad_; };
    private:
        Cadena cad_;
    };

    Usuario(const Cadena& id, const Cadena& nombre, const Cadena& apellidos, const Cadena& dir, const Clave& clv);
    Usuario(const Usuario& us) = delete;
    Usuario& operator=(const Usuario& tar) = delete;

    const Cadena& id() const noexcept { return id_; };
    const Cadena& nombre() const noexcept { return nombre_; };
    const Cadena& apellidos() const noexcept { return apellidos_; };
    const Cadena& direccion() const noexcept { return dir_; };
    const Tarjetas& tarjetas() const noexcept { return tarjetas_; };
    const Articulos& compra() const noexcept { return carrito_; };
    std::size_t n_articulos() const noexcept { return carrito_.size(); };

    void es_titular_de(Tarjeta& tar);
    void no_es_titular_de(Tarjeta& tar);
    void compra(Articulo& art, std::size_t cantidad = 1);

    ~Usuario();
    
    friend std::ostream& operator <<(std::ostream& os, const Usuario& us);
private:
    const Cadena id_, nombre_, apellidos_, dir_;
    Clave contrasenna_;
    Tarjetas tarjetas_;
    Articulos carrito_;
    static Usuarios usuarios_;
};

std::ostream& mostrar_carro(std::ostream& os, const Usuario& us);

#endif //USUARIO_HPP_
