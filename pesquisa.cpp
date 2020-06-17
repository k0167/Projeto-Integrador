#include "pesquisa.h"

Pesquisa::Pesquisa():
    listaPF(nullptr),
    listaPJ(nullptr)
{

}

Pesquisa::Pesquisa(Caio::LLDE<Caio::PessoaFisica> &a, Caio::LLDE<H::PessoaJuridica> &b):
    listaPF(&a),
    listaPJ(&b)
{

}

Caio::No<Caio::PessoaFisica> *Pesquisa::pesquisarPF(QString c)
{
    Caio::No<Caio::PessoaFisica> *aux=nullptr;
    if(listaPF->vazio())
        return  aux;

    try {
        aux= new Caio::No<Caio::PessoaFisica>;
    } catch (std::bad_alloc&) {
        throw QString("sem memoria para alocar");
    }
}
