#ifndef ITEM_H
#define ITEM_H


namespace tp2 {
    class Item {
        private:
            int codigo;
            int quantidade;
            float precoUnitario;
            float valorTotal;
        public:
            Item(){codigo=quantidade=precoUnitario=valorTotal=0;}
            Item(int produto,int quantidade,float precoUnitario);

        int getQuantidade() const{return quantidade;}
        float getPrecoUnitario() const{return precoUnitario;}
        float getValorTotal() const{return valorTotal;}
        int getCodigo() const {return codigo;}


        void setQuantidade(int value){quantidade = value;}
        void setPrecoUnitario(float value){precoUnitario = value;valorTotal=precoUnitario*quantidade;}
        void setCodigo(int value){codigo = value;}

        bool operator == (Item &valor)const;
        bool operator <= (Item &valor)const;
        bool operator >= (Item &valor)const;
        bool operator < (Item &valor)const;
        bool operator > (Item &valor)const;
        bool operator != (Item &valor)const;
        void operator = (Item &valor);
    };
}
#endif // ITEM_H
