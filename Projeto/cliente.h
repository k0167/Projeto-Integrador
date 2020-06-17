#ifndef CLIENTE_H
#define CLIENTE_H
#include <QString>
#include <fstream>

using namespace std;
namespace Caio{
class Cliente
{
protected:
    QString codigo;
    QString logradouro;
    QString setor;
    QString cidade;
    QString estado;
    QString telefone;
    QString email;
    QString tipoDeCliente;
public:
    virtual ~Cliente(){}
    Cliente();
    Cliente(QString &log, QString &se, QString &c, QString &e, QString &t, QString &em, QString type);
    Cliente(QString &cd, QString &log, QString &se, QString &c, QString &e, QString &t, QString &em);//n utilizado
    void setCodigo(const QString &value){ codigo= value; }
    QString getCodigo() const{ return codigo; }
    QString getLogradouro() const{ return logradouro; }
    void setLogradouro(const QString &value){ logradouro= value; }
    QString getSetor() const{ return setor; }
    void setSetor(const QString &value){ setor= value; }
    QString getCidade() const{ return cidade; }
    void setCidade(const QString &value){ cidade= value; }
    QString getEstado() const{ return estado; }
    void setEstado(const QString &value){ estado= value; }
    QString getTelefone() const{ return telefone; }
    void setTelefone(const QString &value){ telefone= value; }
    QString getEmail() const{ return email; }
    void setEmail(const QString &value){ email= value; }
    QString getTipo()const{ return tipoDeCliente; }
    virtual QString toString()const;

    bool operator ==(const Cliente &a)const;
    bool operator !=(const Cliente &a)const;
    bool operator <=(const Cliente &a)const;
    bool operator >=(const Cliente &a)const;
    bool operator <(const Cliente &a)const;
    bool operator >(const Cliente &a)const;
};
}
#endif // CLIENTE_H
