#include "pedido.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"
#include <unordered_map>
#include <iomanip>

int Pedido::N_pedidos = 0;

Pedido::Pedido(Usuario_Pedido& usped, Pedido_Articulo& pedart, Usuario& us, const Tarjeta& tar, const Fecha& fch /*= Fecha()*/) :
    num_{N_pedidos + 1}, tarjeta_{&tar}, fecha_{fch}, total_(0)
{
    if(us.n_articulos() == 0)
        throw Vacio{us};

    if(&us != tarjeta_->titular())
        throw Impostor{us};

    if(fecha_ > tarjeta_->caducidad())
        throw Tarjeta::Caducada{tarjeta_->caducidad()};

    if(!tarjeta_->activa())
        throw Tarjeta::Desactivada{};

    Usuario::Articulos::iterator pos;
    Usuario::Articulos carrito = us.compra();
    for(pos = carrito.begin(); pos != carrito.end(); pos++)  //compra es unordered map de articulo* y unsigned (Articulos)
    {
        if(pos->first->stock() < pos->second)
        {
            Usuario::Articulos::iterator aux = pos;
            while(aux != carrito.end())
            {
                us.compra(*aux->first, 0);
                aux++;
            }
            throw SinStock{*pos->first}; //paso el articulo
        }
    }
    //std::unordered_map<Articulo*, unsigned int>::const_iterator
    //Usuario::Articulos::const_iterator
    for(pos = carrito.begin(); pos != carrito.end(); pos++)
    {
        pos->first->stock() -= pos->second;
        pedart.pedir(*this, *pos->first, pos->first->precio(), pos->second);
        total_ += pos->second * pos->first->precio(); //cantidad*precio
        us.compra(*pos->first, 0);
    }
    usped.asocia(us, *this);
    N_pedidos += 1;
}

std::ostream& operator<<(std::ostream& os, const Pedido& pedido)
{
    os << "Núm. pedido: " << pedido.numero() << std::endl
       << "Fecha: " << pedido.fecha() << std::endl 
       << "Pagado con: " << pedido.tarjeta()->tipo() << " n.º: " << pedido.tarjeta()->numero() << std::endl 
       << "Importe: " << std::fixed << std::setprecision(2) << pedido.total() << " €" << std::endl;
    return os;
}
