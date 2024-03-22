#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "Cliente.h"
#include "Prestamo.h"
#include "Fecha.h"
#include "Pago.h"
#define TML 5
using namespace std;

int menu(){
    int op;
    cout<< "MENU DE OPCIONES\n";
    cout<< "1. AGREGAR CLIENTE A LA LISTA.\n";
    cout<< "2. AGREGAR PRESTAMO A LA LISTA.\n";
    cout<< "3. HACER PAGOS DE PRESTAMOS.\n";
    cout<< "4. MOSTRAR LISTA DE CLIENTES.\n";
    cout<< "5. MOSTRAR LISTA DE PRESTAMOS.\n";
    cout<< "6. MOSTRAR DETALLES DEL PRESTAMO.\n";
    cout<< "7. SALIR\n";
    cout<< "DIGITE UNA OPCION: \n";
    cin>>op;

    return op;
}
Cliente *agregarCliente(){
    int id;
    string n,a;
    Cliente *cli;
    cout<< "Ingrese el id del cliente: ";
    cin>>id;
    cout<< "Ingrese el nombre del cliente: ";
    cin>>n;
    cout<< "Ingrese el apellido del cliente: ";
    cin>>a;
    cli=new Cliente(id, n, a);
    return cli;
}
Cliente *BuscarCliente(Cliente *lst[],int cont,int db){
    bool Encontrado = false;
    int contador=0;
    Cliente *cli = NULL;
    while(contador < cont && !Encontrado){
        if (lst[contador]->getIdCliente() == db){
            Encontrado = true;
            cli=lst[contador];
        }
        else{
            contador++;
        }
    }
    return cli;
}
Prestamo *agregarPrestamo(Cliente *cli){
    int np;
    int d, m, a;
    Fecha *fa;
    float ma;
    Prestamo *ptmo;
    cout <<  "Digite el numero del prestamo : ";
    cin >>np;
    cout <<  "Digite la echa de aprobacion (DD/MM/AA) : \n";
    cin >> d;
    cin >> m;
    cin >> a;
    fa = new Fecha(d,m,a);
    cout <<  "Digite el monto del cliente : ";
    cin >> ma;
    ptmo = new Prestamo(np, cli, fa, ma);
    return ptmo;
}
void registrarPago(Prestamo *ptmo){
    int d,m,a;
    Fecha *fp;
    float mp;
    Pago *pg;
    cout << "Digite la fecha del pago (DD/MM/AA) : ";
    cin >> d;
    cin >> m;
    cin >> a;
    cout << "Digite el monto del pago : ";
    cin >> mp;
    fp = new Fecha(d,m,a);
    pg = new Pago(fp, mp);
    ptmo->hacerPago(pg);
}
void verDetalles(Prestamo *ptmo){
    cout << "El numero : " << ptmo->getNumeroPrestamo()<<endl;
    cout << "Cliente : " << ptmo->getCliente()->getNombre()<< "" << ptmo->getCliente()->getApellido()<<endl;
    cout << "Fecha : ";
    ptmo->getFechaAprobacion()->mostrarFecha();
    cout << "\nMonto aprobado : " << ptmo->getMontoAprobado() << endl;
    cout << "Saldo pendiente : " << ptmo->getSaldoPendiente() << endl;
    if (ptmo->getContadorPagos() == 0){
        cout << "no tiene pagos registrados\n";
    }
    else{
        Pago **lista = ptmo->getLstPagos();
        cout << "no\tFECHA\tMONTO\n";
        for (int i=0;i<ptmo->getContadorPagos();i++){
            cout << (i+1) << "\t";
            lista[i]->getFechaPago()->mostrarFecha();
            cout << "\t" << lista[i]->getMontoPago() << endl;
        }
    }
}
Prestamo *BuscarPrestamo(Prestamo *lst[],int cont,int db){
    bool Encontrado = false;
    int contador=0;
    Prestamo *ptmo = NULL;
    while(contador < cont && !Encontrado){
        if(lst[contador]->getNumeroPrestamo()==db){
            Encontrado = true;
            ptmo=lst[contador];
        }
        else{
            contador++;
        }
    }
    return ptmo;
}
int main(){
    Cliente *lstCliente[TML];
    Prestamo *lstPrestamo[TML];
    Cliente *cli=NULL;
    Prestamo *ptmo = NULL;
    int contCli=0, contPtmo=0, idCli, idPtmo;
    int opc;
    do
    {
        system("cls");
        opc=menu();
        switch(opc)
        {
        case 1:
            if(contCli < TML){
                lstCliente[contCli]=agregarCliente();
                contCli++;
                cout << "El cliente se registro correctamente" <<endl;
            }
            else
            {
                cout<< "La lista de clientes esta llena."<<endl;
            }
            break;
        case 2:
            if (contPtmo < TML){
                cout << "Digite el id del cliente : ";
                cin >> idCli;
                cli = BuscarCliente(lstCliente, contCli, idCli);
                if (cli){
                    lstPrestamo[contPtmo] = agregarPrestamo(cli);
                    contPtmo++;
                    cout << "El prestamo se registro con exito\n";
                }
                else{
                    cout<< "El cliente no existe.";
                }
            }
            break;

        case 3:
            cout << "Digite el numero del prestamo: ";
            cin >> idPtmo;
            ptmo = BuscarPrestamo(lstPrestamo, contPtmo, idPtmo);
            if (ptmo){
                registrarPago(ptmo);
                cout << "El pago se realizo con exito\n";
            }
            else{
                cout << "El prestamo no existe";
            }
        break;

        case 4:
            if(contCli == 0){
                cout<< "La lista esta vacia\n";
            }
            else{
                cout << "ID\tNOMBRE\tAPELLIDO\n";
                for (int i=0;i<contCli;i++){
                    cout << lstCliente[i]->getIdCliente() << "\t";
                    cout << lstCliente[i]->getNombre() << "\t";
                    cout << lstCliente[i]->getApellido() << "\t";
                }

            }
            break;
        case 5:
            if(contPtmo == 0){
                cout << "La lista esta vacia\n";
            }
            else{
                cout << "NO\tCLIENTE\tFECHA\tMONTO\tSALDO\n";
                for (int i=0;i<contPtmo;i++){
                    cout << lstPrestamo[i]->getNumeroPrestamo() << "\t";
                    cout << lstPrestamo[i]->getCliente()->getNombre() << " " <<lstPrestamo[i]->getCliente()->getApellido()<< "\t";
                    lstPrestamo[i]->getFechaAprobacion()->mostrarFecha();
                    cout << "\t" << lstPrestamo[i]->getMontoAprobado() << "\t";
                    cout << lstPrestamo[i]->getSaldoPendiente() << endl;
                }
            }
            break;
        case 6:
                cout << "Digite el numero del prestamo: ";
                cin >> idPtmo;
                ptmo = BuscarPrestamo(lstPrestamo, contPtmo, idPtmo);
                if(ptmo){
                    verDetalles(ptmo);
                }
                else{
                    cout << "El prestamo no existe";
                }
            break;
        case 7:
            cout << "Salir" << endl;
            break;
        default:
            cout<< "Eroro opcion no valida."<<endl;
            break;
        }

        system("pause");
    }while(opc!=7);

    return 0;
}
