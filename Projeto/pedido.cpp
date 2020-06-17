#include "pedido.h"


namespace tp2{
    Pedido::Pedido(){
        numero=valorTotal=0;
        cliente="";
        data=status="";
        ListaDeItens=nullptr;
    }

    Pedido::Pedido(int &numero,QString cliente,QString &data,QString &status,float &valorTotal):
        numero(numero),cliente(cliente),data(data),status(status),valorTotal(valorTotal){}

    void Pedido::setValorTotal()
    {
        int qtde=ListaDeItens->getQuantidade();
        for (int i=0;i<qtde;i++){
            tp2::Item temp=ListaDeItens->operator[](i);
            valorTotal+=temp.getValorTotal();
        }
    }
    bool Pedido::operator == (Pedido &valor)const{
        if(this->numero==valor.getNumero())
            return true;
        else
            return false;
    }
    bool Pedido::operator <= (Pedido &valor)const{
        if(this->numero<=valor.getNumero())
            return true;
        else
            return false;
    }
    bool Pedido::operator >= (Pedido &valor)const{
        if(this->numero>=valor.getNumero())
            return true;
        else
            return false;
    }
    bool Pedido::operator < (Pedido &valor)const{
        if(this->numero<valor.getNumero())
            return true;
        else
            return false;
    }
    bool Pedido::operator > (Pedido &valor)const{
        if(this->numero>valor.getNumero())
            return true;
        else
            return false;
    }
    bool Pedido::operator != (Pedido &valor)const{
        return !(*this==valor);
    }
    void Pedido::operator = (Pedido &valor){
        this->numero=valor.getNumero();
        this->data=valor.getData();
        this->cliente=valor.getCliente();
        this->status=valor.getStatus();
        this->valorTotal=valor.getValorTotal();
    }


}
