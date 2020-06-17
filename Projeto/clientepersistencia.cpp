#include"clientepersistencia.h"

ClientePersistencia::ClientePersistencia()
{

}

void ClientePersistencia::armazenarClientes(Caio::LLDE<Caio::Cliente*> *p)
{
    if(p == nullptr)
        throw QString("Lista ainda não foi associada");
    string escrita("");
    string um("Armazenamento_Clientes.csv");
    ofstream arquivo1("Armazenamento_Clientes.csv");
    arquivo1.close();
    arquivo1.open(um,ios::app);

    for(int x=0; x<((*p).getQuantidade()); x++){
        if(typeid (*(p->operator[](x))) == typeid (H::PessoaJuridica)){
            escrita= dynamic_cast<H::PessoaJuridica*>((p->operator[](x)))->registro();
            escrita.push_back('\n');
            arquivo1<<escrita;
        }
        else if(typeid (*(p->operator[](x))) == typeid (Caio::PessoaFisica)){
            escrita= dynamic_cast<Caio::PessoaFisica*>((p->operator[](x)))->registro();
            escrita.push_back('\n');
            arquivo1<<escrita;
        }
        escrita="";
    }
}

void ClientePersistencia::resgatarClientes(Caio::LLDE<Caio::Cliente*> *p)
{
    if(p == nullptr)
        throw QString("Lista ainda não foi associada");
    Caio::Cliente **cl;
    QStringList list;
    string leitura("");
    string um("Armazenamento_Clientes.csv");
    ifstream arquivo1;
    arquivo1.open(um);

    if(arquivo1.fail()){
        ofstream criar("Armazenamento_Clientes.csv");
        criar.close();

        arquivo1.open(um);
    }

    while (!arquivo1.eof()) {
        getline(arquivo1,leitura);

        if(!(leitura.size() < 10)){//so pra garantir que nao pegou linha vazia, qualquer linha correta vai ter mais de 10 carcteres
            list=QString::fromStdString(leitura).split(';');

            cl= new Caio::Cliente*;

            if(list[0] == "pf"){
                *cl=new Caio::PessoaFisica(list[1], list[2], list[3], list[4], list[5], list[6], list[7], list[8], list[9]);
                (*cl)->setCodigo(list[10]);
                p->insereOrdenado(*cl);
            }
            else if(list[0] == "pj"){
                string aux[3]{list[7].toStdString(), list[8].toStdString(), list[9].toStdString()};
                *cl=new H::PessoaJuridica(list[1], list[2], list[3], list[4], list[5], list[6], aux[0], aux[1], aux[2]);
                (*cl)->setCodigo(list[10]);
                p->insereOrdenado(*cl);
            }
        }
        leitura="";
    }
}
