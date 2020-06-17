#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "pessoafisica.h"
#include "pessoajuridica.h"
#include "item.h"
#include "llde.h"
#include "pedido.h"
#include "produto.h"
#include<QInputDialog>
#include<QMessageBox>
#include <QDateTime>
#include <QStringListModel>
#include"produto_persistencia.h"
#include "clientepersistencia.h"
#include "pedido_persistencia.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButtonCADASTRAR_PROD_clicked();

    void on_pushButtonCADASTRAR_PRODUTO_clicked();

    void on_lineEditCODIGO_returnPressed();

    void on_lineEditDESCRICAO_returnPressed();

    void on_lineEditPRECO_returnPressed();

    void on_lineEditQUANTIDADE_returnPressed();

    void on_pushButtonCONSULTAR_PRODUTO_clicked();

    void on_pushButtonLISTAR_PRODUTOS_clicked();

    void on_pushButtonREMOVER_PRODUTO_clicked();

    void on_pushButtonCADASTRAR_PEDIDO_clicked();

    void on_pushButtonCONSULTAR_PEDIDO_clicked();

    void on_pushButtonLISTAR_PEDIDO_clicked();

    void on_pushButtonREMOVER_PEDIDO_clicked();

    void on_tabWidget_tabBarClicked(int index);

    void on_pushButtonConcluirCadastro_clicked();

    void on_pushButtonConcluirConsulta_clicked();

    void on_pushButtonRemoverPedido_clicked();


    void on_pushButtonCADASTRAR_CLIENTE_clicked();

    void on_pushButtonREALIZAR_CADASTRO_clicked();

    void on_pushButtonCONSULTAR_CLIENTE_clicked();

    void on_pushButtonREMOVER_CLIENTE_clicked();

    void on_pushButtonLISTAR_CLIENTE_clicked();

    void on_pushButtonVerificaCodigo_clicked();

    void on_pushButtonIncluiItem_clicked();

private:
    Ui::MainWindow *ui;
    QStringListModel *retornamodelpedido (Caio::LLDE<tp2::Item> *lista)const;
    void limparPedido();
    void bloquearLineEdits_Cliente();
    void desbloquearLineEdits_Cliente();
    void limparLineEdits_Cliente();
    H::Produto produto;
    Caio::LLDE<H::Produto> listaDeProdutos;
    Caio::LLDE<tp2::Pedido> listaDePedidos;
    Caio::LLDE<Caio::Cliente*> listaDeCliente;
    Caio::Cliente **pont_cliente;
    bool pf, pj;
    Produto_Persistencia lista();
};
#endif // MAINWINDOW_H
