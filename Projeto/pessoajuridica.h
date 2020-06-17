#ifndef PESSOAJURIDICA_H
#define PESSOAJURIDICA_H
#include<string>
#include<QString>
#include "cliente.h"

namespace H {
class PessoaJuridica :public Caio::Cliente
{
private:
    std::string cnpj;
    std::string razaoSocial;
    std::string nomecontado;
public:
    virtual ~PessoaJuridica(){}
    PessoaJuridica();
    PessoaJuridica(QString &log, QString &s, QString &c, QString &e, QString &t, QString &em, std::string &cpj, std::string &rzsocial, std::string &nomecont);
    std::string getCnpj()const{return cnpj;}
    void setCnpj(std::string novoCnpj){cnpj=novoCnpj;}
    std::string getRazaoSocial()const{return razaoSocial;}
    void setRazaoSocial(std::string novaRazao){cnpj=novaRazao;}
    std::string getNome()const{return nomecontado;}
    void setNome(std::string novoNome){cnpj=novoNome;}

    bool static validarCnpj(std::string cnpj);

    bool operator ==(const PessoaJuridica &a)const{ return (cnpj == a.cnpj); }
    bool operator !=(const PessoaJuridica &a)const{ return (cnpj != a.cnpj); }
    bool operator <=(const PessoaJuridica &a)const{ return (cnpj <= a.cnpj); }
    bool operator >=(const PessoaJuridica &a)const{ return (cnpj >= a.cnpj); }
    bool operator <(const PessoaJuridica &a)const{ return (cnpj < a.cnpj); }
    bool operator >(const PessoaJuridica &a)const{ return (cnpj > a.cnpj); }

    QString toString()const override;
    string registro()const;

};
}


#endif // PESSOAJURIDICA_H
