#include "pessoafisica.h"
namespace Caio{
PessoaFisica::PessoaFisica():
    Cliente(),
    cpf(""),
    nome(""),
    celular("")
{

}

PessoaFisica::PessoaFisica(QString &log, QString &s, QString &c, QString &e, QString &t, QString &em, QString &cpf, QString &nome, QString &celular):
    Cliente(log, s, c, e, t, em, "PF"),
    cpf(cpf),
    nome(nome),
    celular(celular)
{
}

bool PessoaFisica::validarCPF(QString &ref)
{
    string s(ref.toStdString());
            int digitos[11];

            if(s.size() != 11){ return false; }
            else if(s == "00000000000" || s == "99999999999"){ return false; }
            else{
                for(unsigned long long x=0; x<11; x++)
                    if(isdigit(s[x]) == false){ return false;}

                for(unsigned long long x=0; x<11; x++)
                    digitos[x]=(int)s[x]-48;

                int pd=0;
                bool validarpd=false;
                for(int x=0, m=10; x<9; x++, m--)
                    pd+=digitos[x]*m;

                pd=pd%11;
                if(pd<2)
                    pd=0;
                else pd=11-pd;

                int sd=0;
                bool validarsd=false;

                int x=0, m=11;
                for(; x<9; x++, m--){
                    sd+=digitos[x]*m;
                }
                sd+=pd*m;

                sd=sd%11;
                if(sd<2)
                    sd=0;
                else sd=11-sd;

                if(digitos[9]==pd)
                    validarpd=true;

                if(digitos[10]==sd)
                    validarsd=true;

                if(validarpd==true && validarsd==true){
                    return true;
                }
                else
                    return false;
            }
}

QString PessoaFisica::toString() const
{
    QString str("Nome: "+nome+"\nCodigo: "+codigo+"\nCPF: "+cpf+"\nLogradouro: "+logradouro+"\nSetor: "+setor+"\nCidade: "+cidade+"\nEstado: "+estado+"\nTelefone: "+telefone+"\nCelular: "+celular+"\nEmail: "+email);
    return str;
    //falta adicionar coisa
}

string PessoaFisica::registro() const
{
    string s("pf;"+logradouro.toStdString()+';'+setor.toStdString()+';'+cidade.toStdString()+';'+estado.toStdString()+';'+telefone.toStdString()+';'+email.toStdString()+';'+cpf.toStdString()+';'+nome.toStdString()+';'+celular.toStdString()+';'+codigo.toStdString());
    return s;
}

}//namespace
