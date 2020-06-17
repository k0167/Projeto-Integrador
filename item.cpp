#include "item.h"
namespace tp2{

Item::Item(int codigo,int quantidade,float precoUnitario):
    codigo(codigo),
    quantidade(quantidade),
    precoUnitario(precoUnitario){
}

    bool Item::operator == (Item &valor)const{
        if(this->codigo==valor.getCodigo())
            return true;
        else
            return false;
    }
    bool Item::operator <= (Item &valor)const{
        if(this->codigo<=valor.getCodigo())
            return true;
        else
            return false;
    }
    bool Item::operator >= (Item &valor)const{
        if(this->codigo>=valor.getCodigo())
            return true;
        else
            return false;
    }
    bool Item::operator < (Item &valor)const{
        if(this->codigo<valor.getCodigo())
            return true;
        else
            return false;
    }
    bool Item::operator > (Item &valor)const{
        if(this->codigo>valor.getCodigo())
            return true;
        else
            return false;
    }
    bool Item::operator != (Item &valor)const{
        return !(*this==valor);
    }
    void Item::operator = (Item &valor){
        this->codigo=valor.getCodigo();
        this->quantidade=valor.getQuantidade();
        this->precoUnitario=valor.getPrecoUnitario();
        this->valorTotal=valor.getValorTotal();
    }
}
