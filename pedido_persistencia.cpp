#include "pedido_persistencia.h"

pedido_persistencia::pedido_persistencia(){

}

int pedido_persistencia::lerArquivo(Caio::LLDE<tp2::Pedido> *lista){
    int contador=0;
    string leitura;
    tp2::Pedido pedido;
    QString arquivoProdutos="ListaDePedidos.csv";
    ifstream arquivo;
    arquivo.open("ListaDePedidos.csv");
    if (arquivo.is_open()){
        getline(arquivo,leitura);
        while(!arquivo.eof()){
           QString linha=QString::fromStdString(leitura);
            if(linha!=""){
                QStringList list=linha.split(';');
                pedido.setNumero(list[0].toInt());
                contador=list[0].toInt();
                pedido.setCliente(list[1]);
                pedido.setData(list[2]);
                pedido.setStatus(list[3]);
                pedido.setValorTotal(list[4].toFloat());
                pedido.ListaDeItens=new Caio::LLDE<tp2::Item>();
                lista->insereFim(pedido);
                int quantidade=list[5].toInt();
                getline(arquivo,leitura);
                linha=QString::fromStdString(leitura);
                if(linha!=""){
                    list=linha.split(';');
                    for(int i=1, j=1;i<=quantidade;i++,j+=3){
                        tp2::Item item;
                        item.setCodigo(list[j].toInt());
                        item.setQuantidade(list[j+1].toInt());
                        item.setPrecoUnitario(list[j+2].toFloat());
                        pedido.ListaDeItens->insereFim(item);
                    }
                }
            }
            getline(arquivo,leitura);
        }
    }

    arquivo.close();
    return contador;
}

void pedido_persistencia::salvarArquivo(Caio::LLDE<tp2::Pedido> lista)
{
    ofstream arquivo;
    arquivo.open("ListaDePedidos.csv");
    for(int i=0;i<lista.getQuantidade();i++){
        tp2::Pedido pedido=lista[i];
        arquivo<<pedido.getNumero()<<";"<<
                 pedido.getCliente().toStdString()<<";"<<
                 pedido.getData().toStdString()<<";"<<
                 pedido.getStatus().toStdString()<<";"<<
                 pedido.getValorTotal()<<";"<<
                 pedido.ListaDeItens->getQuantidade()<<"\n";
        for(int i=0;i<pedido.ListaDeItens->getQuantidade();i++){
            tp2::Item item=pedido.ListaDeItens->operator[](i);
            arquivo<<";"<<item.getCodigo()
                   <<";"<<item.getQuantidade()
                   <<";"<<item.getPrecoUnitario();
        }
        arquivo<<"\n";
    }
}
