#ifndef PRODUTO_H
#define PRODUTO_H
#include"llde.h"


namespace H {
class Produto
{
private:
    int codigo;
    QString descricao;
    float preco;
    int quantidade;

public:
    Produto();
    Produto(int numero,QString texto, float price, int qtd);
    int getCodigo()const{return codigo;}
    void setCodigo(int numero){codigo=numero;}
    QString getDescricao()const{return descricao;}
    void setDescricao(QString texto){descricao=texto;}
    float getPreco()const{return preco;}
    void setPreco(float numero){preco=numero;}
    int getQuantidade()const{return quantidade;}
    void setQuatidade(int numero){quantidade=numero;}

    bool operator ==(Produto item)const;
    bool operator !=(Produto item)const;
    bool operator <=(Produto item)const;
    bool operator >=(Produto item)const;
    bool operator <(Produto item)const;
    bool operator >(Produto item)const;

};
}


#endif // PRODUTO_H
