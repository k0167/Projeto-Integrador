#include "produto_persistencia.h"

Produto_Persistencia::Produto_Persistencia(){

}

void Produto_Persistencia::lerArquivo(Caio::LLDE<H::Produto> *lista){
    string leitura;
        H::Produto produto;
        QString arquivoProdutos="Produtos.csv";
        ifstream arquivo;

        arquivo.open("Produtos.csv");
        if(arquivo.fail()){
            ofstream arq("Produtos.csv");
            arq.close();
            arquivo.open("Produtos.csv");
        }
        getline(arquivo,leitura);
        while(!arquivo.eof()){
           QString linha=QString::fromStdString(leitura);
           if(linha!=""){
               QStringList list=linha.split(';');
               produto.setCodigo(list[0].toInt());
               produto.setDescricao(list[1]);
               produto.setPreco(list[2].toDouble());
               produto.setQuatidade(list[3].toInt());
               lista->insereFim(produto);
           }
            getline(arquivo,leitura);
        }
        arquivo.close();
}

void Produto_Persistencia::salvarArquivo(Caio::LLDE<H::Produto> lista)
{
    ofstream arquivo;
        arquivo.open("Produtos.csv");
        for(int i=0;i<lista.getQuantidade();i++){
            H::Produto produto=lista[i];
            arquivo<<produto.getCodigo()<<";"<<produto.getDescricao().toStdString()<<";"<<produto.getPreco()<<";"
                  <<produto.getQuantidade()<<"\n";
        }
        arquivo.close();
}
