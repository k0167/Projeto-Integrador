#include "cliente.h"
namespace Caio{
Cliente::Cliente():
    codigo(""),
    logradouro(""),
    setor(""),
    cidade(""),
    estado(""),
    telefone(""),
    email("")
{

}

Cliente::Cliente(QString &log, QString &se, QString &c, QString &e, QString &t, QString &em, QString type):
    codigo(""),
    logradouro(log),
    setor(se),
    cidade(c),
    estado(e),
    telefone(t),
    email(em),
    tipoDeCliente(type)
{
    ifstream arquivo;
    arquivo.open("unic_id_historic.csv");

    if(!arquivo.is_open()){
        ofstream arquivo2;
        arquivo2.open("unic_id_historic.csv");
        arquivo2<<1;
        codigo="1";
    }
    else{
        string leitura;
        getline(arquivo, leitura);
        arquivo.close();
        unsigned int c= atoi(leitura.c_str());

        codigo= QString::number(++c);

        ofstream archive;
        archive.open("unic_id_historic.csv");
        archive<<c;
        archive.close();
    }
}

Cliente::Cliente(QString &cd, QString &log, QString &se, QString &c, QString &e, QString &t, QString &em):
    codigo(cd),
    logradouro(log),
    setor(se),
    cidade(c),
    estado(e),
    telefone(t),
    email(em)
{}

QString Cliente::toString() const
{
    QString str("Codigo: "+codigo+"\nLogradouro: "+logradouro+"\nSetor: "+setor+"\nCidade: "+cidade+"\nEstado: "+estado+"\nTelefone: "+telefone+"\nEmail: "+email);
    return str;
}

bool Cliente::operator ==(const Cliente &a) const
{
    return (codigo == a.codigo);
}

bool Cliente::operator !=(const Cliente &a) const
{
    return (codigo != a.codigo);
}

bool Cliente::operator <=(const Cliente &a) const
{
    return (codigo <= a.codigo);
}

bool Cliente::operator >=(const Cliente &a) const
{
    return (codigo >= a.codigo);
}

bool Cliente::operator <(const Cliente &a) const
{
    return (codigo < a.codigo);
}

bool Cliente::operator >(const Cliente &a) const
{
    return (codigo > a.codigo);
}

}//namespace
