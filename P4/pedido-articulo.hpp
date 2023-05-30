#ifndef PEDIDO_ARTICULO_HPP_
#define PEDIDO_ARTICULO_HPP_
#include <map>
#include "articulo.hpp"
#include "pedido.hpp"

class LineaPedido
{
public:
    explicit LineaPedido(double precio, unsigned cantidad = 1);  //no se permite conversion implicita
    //observadores
    double precio_venta() const noexcept { return precio_; };
    unsigned cantidad() const noexcept { return cantidad_; };
private:
    double precio_;
    unsigned cantidad_;
};

std::ostream& operator<<(std::ostream& os, const LineaPedido& linea);

class OrdenaArticulos
{
public:
    bool operator()(const Articulo* a1, const Articulo* a2) const { return (a1->referencia() < a2->referencia()); };
};

class OrdenaPedidos
{
public:
    bool operator()(const Pedido* p1, const Pedido* p2) const { return (p1->numero() < p2->numero()); };
};


class Pedido_Articulo
{
public:
    typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
    typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;
    void pedir(Pedido& ped, Articulo& art, double precio, unsigned cantidad = 1);
    void pedir(Articulo& art, Pedido& ped, double precio, unsigned cantidad = 1);
    const ItemsPedido& detalle(Pedido& ped);
    Pedidos ventas(Articulo& art);

    std::ostream& mostrarDetallePedidos(std::ostream& os);
    std::ostream& mostrarVentasArticulos(std::ostream& os);
private:
    std::map<Pedido*, ItemsPedido, OrdenaPedidos> pedido_articulo_; //nombres de asociacion: desde pedido a articulo
    std::map<Articulo*, Pedidos, OrdenaArticulos> articulo_pedido_;
};

std::ostream& operator<<(std::ostream& os, const Pedido_Articulo::ItemsPedido& art);
std::ostream& operator<<(std::ostream& os, const Pedido_Articulo::Pedidos& ped);

#endif //PEDIDO_ARTICULO_HPP_
