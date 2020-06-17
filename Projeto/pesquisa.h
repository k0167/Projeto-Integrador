#ifndef PESQUISA_H
#define PESQUISA_H
#include "pessoafisica.h"
#include "pessoajuridica.h"
#include "llde.h"

class Pesquisa
{
private:
    Caio::LLDE<Caio::PessoaFisica> *listaPF;
    Caio::LLDE<H::PessoaJuridica> *listaPJ;
public:
    Pesquisa();
    Pesquisa(Caio::LLDE<Caio::PessoaFisica> &a, Caio::LLDE<H::PessoaJuridica> &b);
    Caio::No<Caio::PessoaFisica>* pesquisarPF(QString c);
    Caio::No<H::PessoaJuridica>* pesquisarPJ(QString c);
};

#endif // PESQUISA_H
