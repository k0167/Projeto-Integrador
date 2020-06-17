#include "produto.h"

namespace H {
Produto::Produto():
    codigo(0),
    descricao(""),
    preco(0),
    quantidade(0)
{
}

Produto::Produto(int numero,QString texto, float price, int qtd):
    codigo(numero),
    descricao(texto),
    preco(price),
    quantidade(qtd)
{
}

bool Produto::operator ==(Produto item) const{
    if(codigo==item.getCodigo())return true;
    return false;
}

bool Produto::operator !=(Produto item) const{
    if(codigo!=item.getCodigo())return true;
    return false;
}

bool Produto::operator <=(Produto item) const{
    if(codigo<=item.getCodigo())return true;
    return false;
}

bool Produto::operator >=(Produto item) const{
    if(codigo>=item.getCodigo())return true;
    return false;
}

bool Produto::operator <(Produto item) const{
    if(codigo<item.getCodigo())return true;
    return false;
}

bool Produto::operator >(Produto item) const{
    if(codigo>item.getCodigo())return true;
    return false;
}



}

