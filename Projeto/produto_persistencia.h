#ifndef PRODUTO_PERSISTENCIA_H
#define PRODUTO_PERSISTENCIA_H
#include"produto.h"
#include<QStringList>


class Produto_Persistencia
{

public:
    Produto_Persistencia();
    static void lerArquivo(Caio::LLDE<H::Produto> *lista);
    static void salvarArquivo(Caio::LLDE<H::Produto> lista);
};

#endif // PRODUTO_PERSISTENCIA_H
