#ifndef LLDE_H
#define LLDE_H

#include "no.h"
#include "cliente.h"
#include <QString>
#include <iostream>
#include <fstream>

using std::bad_alloc;
using std::ifstream;
using std::ofstream;
using std::string;

namespace Caio{
template <class tipo>
class LLDE
{
private:
    No<tipo>* inicio;
    No<tipo>* fim;
    int quantidade;
public:
    LLDE();
    ~LLDE();

    int getQuantidade() const;
    bool vazio()const;

    void insereInicio(tipo info);
    void insereFim(tipo info);
    void retiraInicio();
    void retiraFim();
    tipo operator[](int posicao)const;
    void insereNaPosicao(int pos, tipo info);
    void retiraNaPosicao(int posicao);
    void insereOrdenado(tipo info);
    int search(tipo info)const;
    int encontre(tipo value) const;

};

template <class tipo>
LLDE<tipo>::LLDE():
    inicio(nullptr),
    fim(nullptr),
    quantidade(0)
{}
template <class tipo>
LLDE<tipo>::~LLDE(){
    while(!(vazio()))
        retiraInicio();
}

template <class tipo>
int LLDE<tipo>::getQuantidade() const{ return quantidade; }

template <class tipo>
bool LLDE<tipo>::vazio()const{ return (quantidade == 0) ? true : false; }

template <class tipo>
void LLDE<tipo>::insereInicio(tipo info){
    No<tipo>* aux=0;

    try {
        aux=new No<tipo>(info);
    } catch (bad_alloc&) {
        throw QString("sem memoria para alocar");
    }

    if(quantidade == 0){
        inicio= aux;
        fim=inicio;
    }
    else{
        inicio->setAnterior(aux);
        aux->setProximo(inicio);
        inicio=aux;
    }
    quantidade++;
}

template <class tipo>
void LLDE<tipo>::insereFim(tipo info){
    No<tipo>* aux=0;

    try {
        aux=new No<tipo>(info);
    } catch (bad_alloc&) {
        throw QString("sem memoria para alocar");
    }

    if(quantidade==0){
        fim=aux;
        inicio=fim;
    }
    else{
        fim->setProximo(aux);
        aux->setAnterior(fim);
        fim=aux;
    }

    quantidade++;
}

template <class tipo>
void LLDE<tipo>::retiraInicio(){

    if(quantidade==1){
        delete inicio;
        fim=inicio=nullptr;
    }else{
        No<tipo>* aux=inicio;
        inicio=inicio->getProximo();
        inicio->setAnterior(nullptr);
        delete aux;
    }
    quantidade--;
}

template <class tipo>
void LLDE<tipo>::retiraFim(){
    if(quantidade==1){
        delete fim;
        fim=inicio=nullptr;
    }else{
        No<tipo>* aux=fim;
        fim=fim->getAnterior();
        fim->setProximo(nullptr);
        delete aux;
    }

    quantidade--;

}

template <class tipo>
tipo LLDE<tipo>::operator[](int posicao)const{
    if(posicao<0 || posicao>=quantidade)
        throw QString("posicao fora do intervalo");
    if(vazio())
        throw QString("nao existe nada na lista");
    if(posicao==0)
        return inicio->getConteudo();
    if(posicao==(quantidade-1))
        return fim->getConteudo();

    No<tipo> *aux=inicio;
    for(int x=0; x<posicao; x++)
        aux=aux->getProximo();

    return aux->getConteudo();
}

template <class tipo>
void LLDE<tipo>::insereNaPosicao(int pos, tipo info){
    if(pos<0 || pos>quantidade)
        throw QString("posicao fora do intervalo");
    if(pos==0){
        insereInicio(info);
    }
    else if(pos==quantidade){
        insereFim(info);
    }
    else{
        No<tipo>* novo=0;
        try {

            novo=new No<tipo>(info);

        } catch (bad_alloc&) {
            throw QString("sem memoria para alocar");
        }

        No<tipo>* aux=inicio;
        for(int x=0; x<pos; x++)
            aux=aux->getProximo();

        aux->getAnterior()->setProximo(novo);
        novo->setAnterior(aux->getAnterior());
        aux->setAnterior(novo);
        novo->setProximo(aux);

        quantidade++;
    }
}

template <class tipo>
void LLDE<tipo>::retiraNaPosicao(int posicao){
    if(vazio())throw QString ("nao ha itens para serem retirados");
    if(posicao<0 || posicao>=quantidade ) throw QString ("Posiçao inválida");
    if(posicao==0)return retiraInicio();
    if(posicao==quantidade-1) return retiraFim();
    No<tipo>* aux(inicio);
    No<tipo>* pos(nullptr);
    for(int i=0;i<posicao-1;i++){
        aux=aux->getProximo();
    }
    pos=aux->getProximo();
    pos->getProximo()->setAnterior(aux);
    aux->setProximo(pos->getProximo());
    quantidade--;
    delete pos;
}

template <class tipo>
void LLDE<tipo>::insereOrdenado(tipo info){
    No<tipo>* aux=fim;

    if(quantidade==0)
        insereInicio(info);

    else if(info >= aux->getConteudo())
        insereFim(info);
    else{
        aux=inicio;
        if(info <= aux->getConteudo())
            insereInicio(info);
        else{

            while (!(info<=aux->getConteudo())) {
                aux=aux->getProximo();
            }

            No<tipo>* novo=0;
            try {

                novo=new No<tipo>(info);

            } catch (bad_alloc&) {
                throw QString("sem memoria para alocar");
            }

            aux->getAnterior()->setProximo(novo);
            novo->setAnterior(aux->getAnterior());
            aux->setAnterior(novo);
            novo->setProximo(aux);

            quantidade++;
        }
    }
}

template <class tipo>
int LLDE<tipo>::search(tipo info)const{
    if(quantidade == 0)
        return -1;

    int limite=quantidade;
    int x=0;

    for(; x<limite; x++){
        tipo i=this->operator[](x);
        if(info == i){
            return x;
        }

    }
    return -1;
}

template<class tipo>//serve só pra lista de ponteiros
int LLDE<tipo>::encontre(tipo value) const
{
    if(quantidade == 0)
        return -1;
    int posicao=0;
    No<tipo> *aux = inicio;
    while(aux && *aux->getConteudo() != *value){
        aux = aux->getProximo();
        posicao++;
    }

    if(aux)
        return posicao;

    else
        return -1;
}
}
#endif // LLDE_H
