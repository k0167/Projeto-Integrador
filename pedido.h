#ifndef PEDIDO_H
#define PEDIDO_H
#include <string>
#include "cliente.h"
#include "item.h"
#include "llde.h"

namespace tp2{
    class Pedido{
        private:
            int numero;
            QString cliente;
            QString data;
            QString status;
            float valorTotal;

        public:
            Caio::LLDE<tp2::Item> *ListaDeItens;
            Pedido();
            Pedido(int &numero,QString cliente,QString &data,QString &status,float &valorTotal);

            int getNumero() const{return numero;}
            QString getCliente() const{return cliente;}
            QString getData() const{return data;}
            QString getStatus() const{return status;}
            float getValorTotal() const{return valorTotal;}

            void setNumero(int value){numero = value;}
            void setCliente(const QString &value){cliente = value;}
            void setData(const QString &value){data = value;}
            void setStatus(const QString &value){status = value;}
            void setValorTotal(float value){valorTotal = value;}
            void setValorTotal();

            bool operator == (Pedido &valor)const;
            bool operator <= (Pedido &valor)const;
            bool operator >= (Pedido &valor)const;
            bool operator < (Pedido &valor)const;
            bool operator > (Pedido &valor)const;
            bool operator != (Pedido &valor)const;
            void operator = (Pedido &valor);

    };
}

#endif // PEDIDO_H
