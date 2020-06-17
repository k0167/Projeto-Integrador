#include "gerenciamento_de_armazenamento.h"

Gerenciamento_de_Armazenamento::Gerenciamento_de_Armazenamento(Caio::LLDE<Caio::Cliente*> *a):
    p1(a)
{

}

void Gerenciamento_de_Armazenamento::armazenarClientes()
{
    string escrita("");
    string um("Armazenamento_Clientes.txt");
    ofstream arquivo1;
    arquivo1.open(um,ios::app);

    for(int x=0; x<((*p1).getQuantidade()); x++){
        if(typeid (*(p1->operator[](x))) == typeid (H::PessoaJuridica)){
            escrita= dynamic_cast<H::PessoaJuridica*>((p1->operator[](x)))->registro();
            escrita.push_back('\n');
            arquivo1<<escrita;
        }
        else if(typeid (*(p1->operator[](x))) == typeid (Caio::PessoaFisica)){
            escrita= dynamic_cast<Caio::PessoaFisica*>((p1->operator[](x)))->registro();
            escrita.push_back('\n');
            arquivo1<<escrita;
        }
        escrita="";
    }
}

void Gerenciamento_de_Armazenamento::resgatarClientes()
{
    Caio::PessoaFisica *pf;
    H::PessoaJuridica *pj;
    Caio::Cliente *cl;
    QStringList list;
    string leitura("");
    string um("Armazenamento_Clientes.txt");
    ifstream arquivo1;
    arquivo1.open(um);

    while (arquivo1.eof()) {
        getline(arquivo1,leitura);

        if(!(leitura.size() < 10)){//so pra garantir que nao pegou linha vazia, qualquer linha correta vai ter mais de 10 carcteres
            list=QString::fromStdString(leitura).split(';');

            if(list[0] == "pf"){
                pf=new Caio::PessoaFisica(list[1], list[2], list[3], list[4], list[5], list[6], list[7], list[8], list[9]);
                cl= pf;
                p1->insereOrdenado(cl);
            }
            else if(list[0] == "pj"){
                string aux[3]{list[7].toStdString(), list[8].toStdString(), list[9].toStdString()};
                pj=new H::PessoaJuridica(list[1], list[2], list[3], list[4], list[5], list[6], aux[0], aux[1], aux[2]);
                cl= pj;
                p1->insereOrdenado(cl);
            }
        }
        leitura="";
    }
}


