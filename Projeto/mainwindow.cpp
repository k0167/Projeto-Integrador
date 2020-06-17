#include "mainwindow.h"
#include "ui_mainwindow.h"

int contaPed;
Caio::LLDE<tp2::Item> *listatemp;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,pf(false)
    ,pj(false)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
    ui->stackedWidgetCLIENTE->setCurrentIndex(0);
    limparLineEdits_Cliente();
    bloquearLineEdits_Cliente();
    Produto_Persistencia::lerArquivo(&listaDeProdutos);
    contaPed = pedido_persistencia::lerArquivo(&listaDePedidos);
    contaPed++;
    ClientePersistencia::resgatarClientes(&listaDeCliente);
}

MainWindow::~MainWindow()
{  
    ClientePersistencia::armazenarClientes(&listaDeCliente);
    Produto_Persistencia::salvarArquivo(listaDeProdutos);
    pedido_persistencia::salvarArquivo(listaDePedidos);
    delete ui;
}

void MainWindow::on_pushButtonCADASTRAR_PROD_clicked()
{
    try {
        produto.setCodigo(ui->lineEditCODIGO->text().toInt());
        produto.setDescricao(ui->lineEditDESCRICAO->text());
        produto.setPreco(ui->lineEditPRECO->text().toFloat());
        produto.setQuatidade(ui->lineEditQUANTIDADE->text().toInt());
        if(listaDeProdutos.search(produto)!=-1){
            QMessageBox::information(this,"ATENCAO","PRODUTO JA CADASTRADO");
        }
        else{
            listaDeProdutos.insereOrdenado(produto);
            QMessageBox::information(this,"ATENCAO","PRODUTO CADASTRADO COM SUCESSO");
        }
        ui->lineEditCODIGO->clear();
        ui->lineEditDESCRICAO->clear();
        ui->lineEditPRECO->clear();
        ui->lineEditQUANTIDADE->clear();
        ui->lineEditCODIGO->setFocus();

    } catch (QString &erro) {
        QMessageBox::information(this,"ATENCAO",erro);
    }
}

void MainWindow::on_pushButtonCADASTRAR_PRODUTO_clicked()
{
    ui->stackedWidgetPRODUTO->setCurrentIndex(1);
    ui->lineEditCODIGO->setFocus();
}

void MainWindow::on_lineEditCODIGO_returnPressed()
{
    ui->lineEditDESCRICAO->setFocus();
}

void MainWindow::on_lineEditDESCRICAO_returnPressed()
{
    ui->lineEditPRECO->setFocus();
}

void MainWindow::on_lineEditPRECO_returnPressed()
{
    ui->lineEditQUANTIDADE->setFocus();
}

void MainWindow::on_lineEditQUANTIDADE_returnPressed()
{
    ui->pushButtonCADASTRAR_PROD->click();
}

void MainWindow::on_pushButtonCONSULTAR_PRODUTO_clicked()
{
    try {
        ui->stackedWidgetPRODUTO->setCurrentIndex(0);
        produto.setCodigo(QInputDialog::getInt(this,"CONSULTA","CODIGO"));
        int valor=listaDeProdutos.search(produto);
        if(valor!=-1){
            produto = listaDeProdutos[valor];
            QString saida="CODIGO: "+QString::number(produto.getCodigo())+"\n";
            saida+="DESCRICAO: "+produto.getDescricao()+"\n";
            saida+="PRECO UNITARIO: "+QString::number(produto.getPreco())+"\n";
            saida+="QUANTIDADE EM ESTOQUE: "+QString::number(produto.getQuantidade());
            ui->textEditPRODUTO->setText(saida);
        }
        else{
            QMessageBox::information(this,"ATENCAO","PRODUTO NAO CADASTRADO");
        }
    } catch (QString &erro) {
        QMessageBox::information(this,"ERRO",erro);
    }

}

void MainWindow::on_pushButtonLISTAR_PRODUTOS_clicked()
{
    try {
        ui->stackedWidgetPRODUTO->setCurrentIndex(0);
        QString saida;
        if(listaDeProdutos.getQuantidade()!=0){

            for(int i=0;i<listaDeProdutos.getQuantidade();i++){
                produto = listaDeProdutos[i];
                saida+="PRODUTO "+QString::number(i+1)+"\nCODIGO: "+QString::number(produto.getCodigo())+"\n";
                saida+="DESCRICAO: "+produto.getDescricao()+"\n";
                saida+="PRECO UNITARIO: "+QString::number(produto.getPreco())+"\n";
                saida+="QUANTIDADE EM ESTOQUE: "+QString::number(produto.getQuantidade())+"\n\n";
            }
        }
        else saida+="NENHUM PRODUTO CADASTRADO.";
        ui->textEditPRODUTO->setText(saida);
    } catch (QString &erro) {
        QMessageBox::information(this,"ERRO",erro);
    }
}



void MainWindow::on_pushButtonREMOVER_PRODUTO_clicked()
{
    try {
        produto.setCodigo(QInputDialog::getInt(this,"CONSULTA","CODIGO"));
        int valor=listaDeProdutos.search(produto);
        if(valor!=-1){
            tp2::Item item;
            tp2::Pedido pedido;
            item.setCodigo(produto.getCodigo());
            bool go=true;

            for(int i=0;i<listaDePedidos.getQuantidade()&& go;i++){
                if(listaDePedidos[i].ListaDeItens->search(item)!=-1)go=false;
            }
            if(go){//nao tem o produto em pedidos
                QMessageBox::StandardButton resposta;
                resposta = QMessageBox::question(this, "CONFIRMACAO", "DESEJA REMOVER O PRODUTO?",QMessageBox::Yes|QMessageBox::No);
                if(resposta==QMessageBox::Yes){
                    listaDeProdutos.retiraNaPosicao(listaDeProdutos.search(produto));
                }
            }
            else{
                QMessageBox::information(this,"ATENCAO","NAO FOI POSSIVEL REMOVER, HA PEDIDOS COM ESTE PRODUTO");
            }
        }//produto nao cadastrado
        else QMessageBox::information(this,"ATENCAO","PRODUTO NAO CADASTRADO");

    } catch (QString &erro) {
        QMessageBox::information(this,"ERRO",erro);
    }
}

//================================botoes da tabWindow=========================================
void MainWindow::on_pushButtonCADASTRAR_PEDIDO_clicked()
{
    limparPedido();
    ui->stackedWidgetPEDIDO->setCurrentIndex(0);
    ui->stackedWidgetBotoes->setCurrentIndex(0);
    ui->stackedWidgetLupas->setCurrentIndex(0);
    ui->pushButtonVerificaCodigo->setEnabled(false);
    ui->lineEditCodigoP->setEnabled(false);
    ui->lineEditCodigoP->setText(QString::number(contaPed));
    ui->lineEditClienteP->setEnabled(true);
    ui->lineEditDataP->setText((QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss")));
    ui->lineEditStatusP->setText("Aberto");
    listatemp=new Caio::LLDE<tp2::Item>;
}

void MainWindow::on_pushButtonCONSULTAR_PEDIDO_clicked()
{
    ui->stackedWidgetPEDIDO->setCurrentIndex(0);
    ui->stackedWidgetBotoes->setCurrentIndex(1);
    ui->stackedWidgetLupas->setCurrentIndex(2);
    ui->lineEditClienteP->setEnabled(false);
    ui->pushButtonVerificaCodigo->setEnabled(false);
    ui->lineEditCodigoP->setEnabled(true);
    limparPedido();
}

void MainWindow::on_pushButtonLISTAR_PEDIDO_clicked()
{
    ui->stackedWidgetPEDIDO->setCurrentIndex(1);
    QStringListModel *model;
    model = new QStringListModel(this);
    QStringList List;
    List << "Numero | Cliente | Itens |  Total  ";

    int qtde=listaDePedidos.getQuantidade();
    for (int i=0;i<qtde;i++){
        tp2::Pedido temp=listaDePedidos[i];
        QString linha= QString::number(temp.getNumero())+"       ";
        linha=linha.left(7)+"|";
        linha += temp.getCliente()+"         ";
        linha=linha.left(17)+"|";
        linha += QString::number(temp.ListaDeItens->getQuantidade())+"        ";
        linha=linha.left(25)+"|";
        linha += "R$"+QString::number(temp.getValorTotal());
        List << linha;
    }
    model->setStringList(List);
    ui->listViewPedidos->setModel(model);
}

void MainWindow::on_pushButtonREMOVER_PEDIDO_clicked()
{
    ui->stackedWidgetPEDIDO->setCurrentIndex(0);
    ui->stackedWidgetBotoes->setCurrentIndex(2);
    ui->stackedWidgetLupas->setCurrentIndex(1);
    ui->lineEditClienteP->setEnabled(false);
    ui->pushButtonVerificaCodigo->setEnabled(true);
    ui->lineEditCodigoP->setEnabled(true);
    limparPedido();
}
//=====================================Pedidos==========================================
void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    if (index==2)
        ui->pushButtonCADASTRAR_PEDIDO->click();
}

void MainWindow::limparPedido()
{
    ui->lineEditDataP->setText("");
    ui->lineEditStatusP->setText("");
    ui->lineEditCodigoP->setText("");
    ui->lineEditValorP->setText("");
    ui->lineEditClienteP->setText("");
    ui->listViewItens->setModel(nullptr);
}
void MainWindow::on_pushButtonConcluirCadastro_clicked()
{
    tp2::Pedido inserir;
    QString cliente=ui->lineEditClienteP->text();
    int q,y;
    q= listaDeCliente.getQuantidade();

    for(y=0; y<q && cliente != listaDeCliente.operator[](y)->getCodigo(); y++);

    if(y == q){
        QMessageBox::about(this,"AVISO","CLIENTE NAO CADASTRADO");
    }else{
        inserir.setNumero(ui->lineEditCodigoP->text().toUInt());
        inserir.setData(ui->lineEditDataP->text());
        inserir.setStatus("Listado");
        inserir.setCliente(ui->lineEditClienteP->text());
        inserir.ListaDeItens=listatemp;
        inserir.setValorTotal();
        listaDePedidos.insereFim(inserir);
        contaPed++;
    }
    ui->pushButtonCADASTRAR_PEDIDO->click();
}

void MainWindow::on_pushButtonConcluirConsulta_clicked()
{
    try {
        tp2::Pedido buscar;
        buscar.setNumero(ui->lineEditCodigoP->text().toInt());
            int posicao=listaDePedidos.search(buscar);
            if(posicao!=-1){
                tp2::Pedido buscar=listaDePedidos.operator[](posicao);
                ui->lineEditClienteP->setText((buscar.getCliente()));
                ui->lineEditStatusP->setText(buscar.getStatus());
                ui->lineEditDataP->setText(buscar.getData());
                ui->lineEditValorP->setText(QString::number(buscar.getValorTotal()));
                ui->listViewItens->setModel(retornamodelpedido(buscar.ListaDeItens));
            }else{
                throw (QString("Pedido Não Encontrado"));
            }
    } catch (QString &msg) {
        QMessageBox::warning(this,"Erro",msg);
    }
}

void MainWindow::on_pushButtonRemoverPedido_clicked()
{
    tp2::Pedido remover;
    remover.setNumero(ui->lineEditCodigoP->text().toUInt());
    int posicao=listaDePedidos.search(remover);
    if(posicao!=-1){
        QMessageBox::StandardButton questao;
        questao = QMessageBox::question(this, "Atenção", "Deseja realmente remover esse Pedido?",QMessageBox::Yes|QMessageBox::No);
        if(questao==QMessageBox::Yes){
            listaDePedidos.retiraNaPosicao(posicao);
            limparPedido();
            ui->lineEditCodigoP->setText("Removido!");
        }
    }else{
        QMessageBox::warning(this,"Erro","Pedido Já Removido ou Inexistente!");
    }
}

void MainWindow::on_pushButtonVerificaCodigo_clicked()
{
    ui->pushButtonConcluirConsulta->click();
}

void MainWindow::on_pushButtonIncluiItem_clicked()
{
    bool ok;
    QString produto,qtde;
    produto = QInputDialog::getText(this, "Produto","Digite o codigo do Produto:", QLineEdit::Normal,"",&ok);
    if ((ok) && !(produto.isEmpty()))
        qtde = QInputDialog::getText(this, "Quantidade","Digite a Quantidade do Produto:", QLineEdit::Normal,"",&ok);
    if ((ok) && !(qtde.isEmpty())){
        H::Produto verificar;
        verificar.setCodigo(produto.toInt());
        int pos = listaDeProdutos.search(verificar);
        if(pos != -1){
            tp2::Item incluir;
            incluir.setCodigo(produto.toInt());
            incluir.setQuantidade(qtde.toInt());
            incluir.setPrecoUnitario(listaDeProdutos.operator[](pos).getPreco());
            listatemp->insereFim(incluir);
            ui->listViewItens->setModel(retornamodelpedido(listatemp));
            ui->lineEditValorP->setText(QString::number(ui->lineEditValorP->text().toFloat()+incluir.getValorTotal()));
        }else{
            QMessageBox::warning(this,"Erro","Produto não cadastrado!");
        }
    }
}

QStringListModel *MainWindow::retornamodelpedido(Caio::LLDE<tp2::Item> *lista) const
{
    QStringListModel *modelitens = new QStringListModel(nullptr);
    QStringList List;
    List << "Codigo | Qtde |   Desc.  |  Total  ";

    int qtde=lista->getQuantidade();
    for (int i=0;i<qtde;i++){
        tp2::Item temp=lista->operator[](i);
        QString linha= QString::number(temp.getCodigo())+"       ";
        linha=linha.left(7)+"|";
        linha += QString::number(temp.getQuantidade())+"         ";
        linha=linha.left(14)+"|";
        H::Produto buscardesc;
        buscardesc.setCodigo(temp.getCodigo());
        linha += listaDeProdutos.operator[](listaDeProdutos.search(buscardesc)).getDescricao()+"           ";
        linha=linha.left(25)+"|";
        linha += "R$"+QString::number(temp.getValorTotal());
        List << linha;
    }
    modelitens->setStringList(List);
    return modelitens;
}
//==================================================================================
void MainWindow::bloquearLineEdits_Cliente()
{
    ui->lineEditLOGRADOURO->setEnabled(false);
    ui->lineEditSETOR->setEnabled(false);
    ui->lineEditCIDADE->setEnabled(false);
    ui->lineEditESTADO->setEnabled(false);
    ui->lineEditTELEFONE->setEnabled(false);
    ui->lineEditEMAIL->setEnabled(false);
    ui->lineEditCPF->setEnabled(false);
    ui->lineEditNOME->setEnabled(false);
    ui->lineEditCELULAR->setEnabled(false);
    ui->lineEditCNPJ->setEnabled(false);
    ui->lineEditRAZAO_SOCIAL->setEnabled(false);
    ui->lineEditNOME_CONTATO->setEnabled(false);
}

void MainWindow::desbloquearLineEdits_Cliente()
{
    ui->lineEditLOGRADOURO->setEnabled(true);
    ui->lineEditSETOR->setEnabled(true);
    ui->lineEditCIDADE->setEnabled(true);
    ui->lineEditESTADO->setEnabled(true);
    ui->lineEditTELEFONE->setEnabled(true);
    ui->lineEditEMAIL->setEnabled(true);
    ui->lineEditCPF->setEnabled(true);
    ui->lineEditNOME->setEnabled(true);
    ui->lineEditCELULAR->setEnabled(true);
    ui->lineEditCNPJ->setEnabled(true);
    ui->lineEditRAZAO_SOCIAL->setEnabled(true);
    ui->lineEditNOME_CONTATO->setEnabled(true);
}

void MainWindow::limparLineEdits_Cliente()
{
    ui->lineEditLOGRADOURO->setText("");
    ui->lineEditSETOR->setText("");
    ui->lineEditCIDADE->setText("");
    ui->lineEditESTADO->setText("");
    ui->lineEditTELEFONE->setText("");
    ui->lineEditEMAIL->setText("");
    ui->lineEditCPF->setText("");
    ui->lineEditNOME->setText("");
    ui->lineEditCELULAR->setText("");
    ui->lineEditCNPJ->setText("");
    ui->lineEditRAZAO_SOCIAL->setText("");
    ui->lineEditNOME_CONTATO->setText("");
}

void MainWindow::on_pushButtonCADASTRAR_CLIENTE_clicked()
{
    ui->stackedWidgetCLIENTE->setCurrentIndex(1);
    desbloquearLineEdits_Cliente();
    QMessageBox::StandardButton resultado;
    resultado = QMessageBox::question(this, "Tipo de cliente", "Deseja cadastrar cliente do tipo juridico ?",QMessageBox::Yes|QMessageBox::No);
    if(resultado==QMessageBox::Yes){
        ui->lineEditCPF->setEnabled(false);
        ui->lineEditNOME->setEnabled(false);
        ui->lineEditCELULAR->setEnabled(false);
        pf= false;
        pj= true;
    }
    else if(resultado==QMessageBox::No){
        ui->lineEditCNPJ->setEnabled(false);
        ui->lineEditNOME_CONTATO->setEnabled(false);
        ui->lineEditRAZAO_SOCIAL->setEnabled(false);
        pf= true;
        pj= false;
    }
}

void MainWindow::on_pushButtonREALIZAR_CADASTRO_clicked()
{//referente a Cliente
    QString dados_para_cadastro[9];
    try {

        dados_para_cadastro[0]=ui->lineEditLOGRADOURO->text();
        dados_para_cadastro[1]=ui->lineEditSETOR->text();
        dados_para_cadastro[2]=ui->lineEditCIDADE->text();
        dados_para_cadastro[3]=ui->lineEditESTADO->text();
        dados_para_cadastro[4]=ui->lineEditTELEFONE->text();
        dados_para_cadastro[5]=ui->lineEditEMAIL->text();

        pont_cliente= new Caio::Cliente*;

        if(pf == true){
            QString str(ui->lineEditCPF->text());
            if(Caio::PessoaFisica::validarCPF(str) == true){
                dados_para_cadastro[6]=ui->lineEditCPF->text();
                dados_para_cadastro[7]=ui->lineEditNOME->text();
                dados_para_cadastro[8]=ui->lineEditCELULAR->text();

                *pont_cliente= new Caio::PessoaFisica(dados_para_cadastro[0], dados_para_cadastro[1], dados_para_cadastro[2], dados_para_cadastro[3], dados_para_cadastro[4], dados_para_cadastro[5], dados_para_cadastro[6], dados_para_cadastro[7], dados_para_cadastro[8]);
                if(listaDeCliente.encontre(*pont_cliente) != -1){
                    QMessageBox::information(this,"ERRO","CPF JA CADASTRADO");
                    ui->lineEditCPF->setText("");
                    ui->lineEditCPF->setFocus();
                }
                else{
                    listaDeCliente.insereOrdenado(*pont_cliente);
                    QString mensagem("CLIENTE CADASTRADO\nSEU CODIGO E: "+dynamic_cast<Caio::PessoaFisica*>(*pont_cliente)->getCodigo());
                    QMessageBox::information(this,"SUCESSO",mensagem);
                }
            }
            else{
                QMessageBox::information(this,"ERRO","CPF INVALIDO");
            }
        }
        else if(pj == true){
            QString str(ui->lineEditCNPJ->text());
            if(H::PessoaJuridica::validarCnpj(str.toStdString()) == true){
                dados_para_cadastro[6]=ui->lineEditCNPJ->text();
                dados_para_cadastro[7]=ui->lineEditRAZAO_SOCIAL->text();
                dados_para_cadastro[8]=ui->lineEditNOME_CONTATO->text();
                std::string aux6(dados_para_cadastro[6].toStdString());
                std::string aux7(dados_para_cadastro[7].toStdString());
                std::string aux8(dados_para_cadastro[8].toStdString());

                *pont_cliente= new H::PessoaJuridica(dados_para_cadastro[0], dados_para_cadastro[1], dados_para_cadastro[2], dados_para_cadastro[3], dados_para_cadastro[4], dados_para_cadastro[5], aux6, aux7, aux8);
                if(listaDeCliente.encontre(*pont_cliente) != -1){
                    QMessageBox::information(this,"ERRO","CNPJ JA CADASTRADO");
                    ui->lineEditCNPJ->setText("");
                    ui->lineEditCNPJ->setFocus();
                }
                else{
                    listaDeCliente.insereOrdenado(*pont_cliente);
                    QString mensagem("CLIENTE CADASTRADO\nSEU CODIGO E: "+dynamic_cast<H::PessoaJuridica*>(*pont_cliente)->getCodigo());
                    QMessageBox::information(this,"SUCESSO",mensagem);
                }
            }
            else{
                QMessageBox::information(this,"ERRO","CNPJ INVALIDO");
            }
        }
        bloquearLineEdits_Cliente();
        limparLineEdits_Cliente();
        ui->stackedWidgetCLIENTE->setCurrentIndex(0);
        ui->pushButtonCADASTRAR_CLIENTE->setFocus();
    } catch (QString &e) {
        QMessageBox::information(this,"ERRO",e);
    }catch (std::string &a) {
        QMessageBox::information(this,"ERRO",QString::fromStdString(a));
    }
}

void MainWindow::on_pushButtonCONSULTAR_CLIENTE_clicked()
{
    try {

        int x= QInputDialog::getInt(this,"Leitura","Codigo do cliente");
        int q,y;
        q= listaDeCliente.getQuantidade();

        for(y=0; y<q && QString::number(x) != listaDeCliente.operator[](y)->getCodigo(); y++);

        if(y == q){
            QMessageBox::about(this,"AVISO","CLIENTE NAO CADASTRADO");
        }
        else{
            ui->textEditCLIENTES->setText(listaDeCliente.operator[](y)->toString());
            ui->stackedWidgetCLIENTE->setCurrentIndex(0);
        }

    } catch (QString &e) {
        QMessageBox::information(this,"ERRO",e);
    }
}

void MainWindow::on_pushButtonREMOVER_CLIENTE_clicked()
{
    try {

        int x= QInputDialog::getInt(this,"Leitura","Codigo do cliente");
        int q,y;
        q= listaDeCliente.getQuantidade();

        for(y=0; y<q && QString::number(x) != listaDeCliente.operator[](y)->getCodigo(); y++);

        if(y == q){
            QMessageBox::about(this,"AVISO","CLIENTE NAO CADASTRADO");
        }
        else{
            QMessageBox::StandardButton resultado= QMessageBox::question(this,"Remover cliente","Tem certeza que quer remover o cliente ?",QMessageBox::Yes|QMessageBox::No);
            if(resultado == QMessageBox::Yes){
                listaDeCliente.retiraNaPosicao(y);
                QMessageBox::about(this,"AVISO","CLIENTE REMOVIDO");
            }
            else{
                QMessageBox::about(this,"AVISO","CLIENTE NÃO REMOVIDO");
            }
        }

    } catch (QString &e) {
        QMessageBox::information(this,"ERRO",e);
    }
}

void MainWindow::on_pushButtonLISTAR_CLIENTE_clicked()
{
    int q= listaDeCliente.getQuantidade();
    QString saida("");

    for(int x=0; x<q; x++){
        if(typeid (Caio::PessoaFisica) == typeid(*(listaDeCliente[x]))){
            saida+=dynamic_cast<Caio::PessoaFisica*>(listaDeCliente[x])->toString()+"\n\n\n";
        }
        else{
            saida+=dynamic_cast<H::PessoaJuridica*>(listaDeCliente[x])->toString()+"\n\n\n";
        }
    }

    ui->textEditCLIENTES->setText(saida);
    ui->stackedWidgetCLIENTE->setCurrentIndex(0);
}






