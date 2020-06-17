#ifndef PEDIDO_PERSISTENCIA_H
#define PEDIDO_PERSISTENCIA_H
#include"pedido.h"
#include<QStringList>

class pedido_persistencia
{
private:

public:
    pedido_persistencia();
    static int lerArquivo(Caio::LLDE<tp2::Pedido> *lista);
    static void salvarArquivo(Caio::LLDE<tp2::Pedido> lista);
};

#endif // PEDIDO_PERSISTENCIA_H
