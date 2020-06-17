#ifndef NO_H
#define NO_H

#include <iostream>
using std::bad_alloc;

namespace Caio{
template <class tipo>
class No
{
private:
    No<tipo>* anterior;
    tipo conteudo;
    No<tipo>* proximo;
public:
    No<tipo>();
    No<tipo>(tipo info);

    No<tipo>* getProximo() const{ return proximo; }
    void setProximo(No<tipo> *value){ proximo= value; }

    tipo getConteudo() const{ return conteudo; }
    void setConteudo(tipo value){ conteudo= value; }

    No<tipo>* getAnterior() const{ return anterior; }
    void setAnterior(No<tipo> *value){ anterior= value; }
};

template <class tipo>
No<tipo>::No():
    anterior(0),
    proximo(0)
{}

template <class tipo>
No<tipo>::No(tipo info):
    anterior(0),
    conteudo(info),
    proximo(0)
{}
}
#endif // NO_H
