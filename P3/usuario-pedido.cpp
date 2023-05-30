#include "usuario-pedido.hpp"
#include <map>
#include <set>

void Usuario_Pedido::asocia(Usuario& us, Pedido& ped)
{
    usuario_pedido_[&us].insert(&ped);
    pedido_usuario_[&ped] = &us;
}

void Usuario_Pedido::asocia(Pedido& ped, Usuario& us)
{
    asocia(us, ped);
}

Usuario_Pedido::Pedidos Usuario_Pedido::pedidos(Usuario& us) { return usuario_pedido_[&us]; }

Usuario* Usuario_Pedido::cliente(Pedido& p) { return pedido_usuario_[&p]; }