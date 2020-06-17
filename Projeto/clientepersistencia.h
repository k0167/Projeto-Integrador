#ifndef CLIENTEPERSISTENCIA_H
#define CLIENTEPERSISTENCIA_H
#include <iostream>
#include <QStringList>
#include<fstream>
#include"cliente.h"
#include"llde.h"
#include"pessoafisica.h"
#include"pessoajuridica.h"

class ClientePersistencia
{
private:
public:
    ClientePersistencia();
    static void armazenarClientes(Caio::LLDE<Caio::Cliente*> *p);
    static void resgatarClientes(Caio::LLDE<Caio::Cliente*> *p);
};

#endif // CLIENTEPERSISTENCIA_H
