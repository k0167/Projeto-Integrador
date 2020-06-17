#include "pessoajuridica.h"

namespace H {
PessoaJuridica::PessoaJuridica():
    cnpj(""),
    razaoSocial(""),
    nomecontado("")
{

}

PessoaJuridica::PessoaJuridica(QString &log, QString &s, QString &c, QString &e, QString &t, QString &em, std::string &cpj, std::string &rzsocial, std::string &nomecont)
    :
      Cliente(log, s, c, e, t, em, "PJ"),
      cnpj(cpj),
      razaoSocial(rzsocial),
      nomecontado(nomecont)
{}

bool PessoaJuridica::validarCnpj(std::string cnpj){
    if(cnpj.size()!=18)throw QString ("CNPJ invalido");
    int cont1=2,cont2=2,dig1=0,dig2=0;
    cnpj.erase(2,1);
    cnpj.erase(5,1);
    cnpj.erase(8,1);
    cnpj.erase(12,1);

    for(int i=11;i>=0;i--){
        if(i<4){
            dig1+=int(cnpj[i]-48)*cont1;
            cont1++;
        }
        else{
            dig1+=int(cnpj[i]-48)*cont2;
            cont2++;
        }
    }

    dig1=dig1%11;

    if(dig1<2)dig1=0;
    else dig1=11-dig1;

    cont1=2;
    cont2=2;

    for(int i=12;i>=0;i--){
        if(i<5){
            dig2+=int(cnpj[i]-48)*cont1;
            cont1++;
        }
        else{
            dig2+=int(cnpj[i]-48)*cont2;
            cont2++;
        }
    }

    dig2=dig2%11;

    if(dig2<2)dig2=0;
    else dig2=11-dig2;

    if(dig1==int(cnpj[12]-48) && dig2==int(cnpj[13]-48))return true;
    return false;
}

QString PessoaJuridica::toString() const
{
    QString str("Nome-contato: "+QString::fromStdString(nomecontado)+"\nCodigo: "+codigo+"\nCNPJ: "+QString::fromStdString(cnpj)+"\nLogradouro: "+logradouro+"\nSetor: "+setor+"\nCidade: "+cidade+"\nEstado: "+estado+"\nTelefone: "+telefone+"\nEmail: "+email+"\nRazao social: "+QString::fromStdString(razaoSocial));
    return str;
}

string PessoaJuridica::registro() const
{
    string s("pj;"+logradouro.toStdString()+';'+setor.toStdString()+';'+cidade.toStdString()+';'+estado.toStdString()+';'+telefone.toStdString()+';'+email.toStdString()+';'+cnpj+';'+nomecontado+';'+razaoSocial+';'+codigo.toStdString());
    return s;
}




}
