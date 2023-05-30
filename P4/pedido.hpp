#ifndef PEDIDO_HPP_
#define PEDIDO_HPP_
#include "tarjeta.hpp"
#include "fecha.hpp"

class Pedido_Articulo;
class Usuario_Pedido;

class Pedido
{
public:
    //carrito vacio
    class Vacio
    {
    public:
        Vacio(Usuario& us) : user_{&us} {};
        const Usuario& usuario() const noexcept { return *user_; };
    private:
        Usuario* const user_;
    };
    //no es titular de tarjeta
    class Impostor
    {
    public:
        Impostor(Usuario& us) : user_{&us} {};
        const Usuario& usuario() const noexcept { return *user_; };
    private:
        Usuario* const user_;
    };

    class SinStock
    {
    public:
        SinStock(Articulo& articulo) : art_{&articulo} {};
        const Articulo& articulo() const noexcept { return *art_; };
    private:
        const Articulo* art_;
    };
    //constructor
    Pedido(Usuario_Pedido& usped, Pedido_Articulo& pedart, Usuario& us, const Tarjeta& tar, const Fecha& fch = Fecha());

    //observadores
    int numero() const noexcept { return num_; };
    const Tarjeta* tarjeta() const noexcept { return tarjeta_; };
    const Fecha& fecha() const noexcept { return fecha_; };
    double total() const noexcept { return total_; };
    static int n_total_pedidos() noexcept { return N_pedidos; };

private:
    int num_;
    const Tarjeta* tarjeta_;
    Fecha fecha_;
    double total_;
    static int N_pedidos;
};

std::ostream& operator<<(std::ostream& os, const Pedido& pedido);
#endif //PEDIDO_HPP_