#ifndef PESSOAFISICA_H
#define PESSOAFISICA_H
#include "cliente.h"

using std::string;
namespace Caio{
class PessoaFisica :public Cliente
{
private:
    QString cpf;
    QString nome;
    QString celular;
public:
    virtual ~PessoaFisica(){}
    PessoaFisica();
    PessoaFisica(QString &log, QString &s, QString &c, QString &e, QString &t, QString &em, QString &cpf, QString &nome, QString &celular);
    static bool validarCPF(QString &ref);

    bool operator ==(const PessoaFisica &a)const{ return (cpf == a.cpf); }
    bool operator !=(const PessoaFisica &a)const{ return (cpf != a.cpf); }
    bool operator <=(const PessoaFisica &a)const{ return (cpf <= a.cpf); }
    bool operator >=(const PessoaFisica &a)const{ return (cpf >= a.cpf); }
    bool operator <(const PessoaFisica &a)const{ return (cpf < a.cpf); }
    bool operator >(const PessoaFisica &a)const{ return (cpf > a.cpf); }

    QString toString()const override;
    string registro()const;
};
}
#endif // PESSOAFISICA_H
