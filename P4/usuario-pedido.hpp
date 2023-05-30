#ifndef USUARIO_PEDIDO_HPP_
#define USUARIO_PEDIDO_HPP_
#include <map>
#include <set>
#include "usuario.hpp"
#include "pedido.hpp"

class Usuario_Pedido
{
public:
    typedef std::set<Pedido*> Pedidos;
    void asocia(Usuario& us, Pedido& ped);
    void asocia(Pedido& ped, Usuario& us);
    Pedidos pedidos(Usuario& us);
    Usuario* cliente(Pedido& p);
private:
    std::map<Usuario*, Pedidos> usuario_pedido_;
    std::map<Pedido*, Usuario*> pedido_usuario_;
};
#endif //USUARIO_PEDIDO_HPP_