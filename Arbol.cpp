#include <iostream>
#include <stdlib.h>

using namespace std;


typedef struct nodo{
     int nro;
     struct nodo *izq, *der;
}*ABB;

int numNodos = 0; // nummero de nodos del arbol 
int numK = 0, k;    



struct nodoCola{
    ABB ptr;
    struct nodoCola *sgte;
};
struct cola{
    struct nodoCola *delante;
    struct nodoCola *atras;
};

void inicializaCola(struct cola &q)
{
    q.delante = NULL;
    q.atras = NULL;
}

void encola(struct cola &q, ABB n)
{
     struct nodoCola *p;
     p = new(struct nodoCola);
     p->ptr = n;
     p->sgte = NULL;
     if(q.delante==NULL)
         q.delante = p;
     else
         (q.atras)->sgte = p;
     q.atras = p;
}

ABB desencola(struct cola &q)
{
    struct nodoCola *p;
    p = q.delante;
    ABB n = p->ptr;
    q.delante = (q.delante)->sgte;
    delete(p);
    return n;
}

ABB crearNodo(int x)
{
     ABB nuevoNodo = new(struct nodo);
     nuevoNodo->nro = x;
     nuevoNodo->izq = NULL;
     nuevoNodo->der = NULL;

     return nuevoNodo;
}
void Agregar(ABB &arbol, int x)
{
     if(arbol==NULL)
     {
           arbol = crearNodo(x);
           cout<<"\n\t  Agregado"<<endl<<endl;
     }
     else if(x < arbol->nro)
          Agregar(arbol->izq, x);
     else if(x > arbol->nro)
          Agregar(arbol->der, x);
}


void mostrar(ABB arbol, int n)
{
     if(arbol==NULL)
          return;
     mostrar(arbol->der, n+1);

     for(int i=0; i<n; i++)
         cout<<"   ";

     numNodos++;
     cout<< arbol->nro <<endl;

     mostrar(arbol->izq, n+1);
}

bool buscar(ABB arbol, int dato)
{
     int r=0;   // 0 indica que lo encontre

     if(arbol==NULL)
        return r;

     if(dato<arbol->nro)
         r = buscar(arbol->izq, dato);

     else if(dato> arbol->nro)
         r = buscar(arbol->der, dato);

     else
        r = 1;   // son iguales, lo encontre

     return r;
}

ABB unirABB(ABB izq, ABB der)
{
    if(izq==NULL) return der;
    if(der==NULL) return izq;

    ABB centro = unirABB(izq->der, der->izq);
    izq->der = centro;
    der->izq = izq;
    return der;
}

void eliminar(ABB &arbol, int x)
{
     if(arbol==NULL) return;

     if(x<arbol->nro)
         eliminar(arbol->izq, x);
     else if(x>arbol->nro)
         eliminar(arbol->der, x);

     else
     {
         ABB p = arbol;
         arbol = unirABB(arbol->izq, arbol->der);
         delete p;
     }
}






void menu()
{
     //system("cls");
     cout << "ARBOL BINARIO DE BUSQUEDA \n\n";
     cout << "\t 1. Insertar elemento                  \n";
     cout << "\t 2. Mostrar arbol                      \n";
   
     cout << "\t 3. Buscar elemento                    \n";
     cout << "\t 4. Eliminar elemento                  \n";
   
     cout << "\t 5. SALIR                              \n";

     cout << "\n\t Ingrese opcion : ";
}


int main()
{
    ABB arbol = NULL;
    int x;
    int op, op2;

    do
    {
          menu();  cin>> op;
          cout << endl;

          switch(op)
          {
               case 1:
                    cout << " Ingrese valor : ";  cin>> x;
                    Agregar( arbol, x);
                    break;

               case 2:
                    mostrar(arbol, 0);
                    break;

               
               case 3:
                    bool band;

                    cout<<" Valor a buscar: "; cin>> x;

                    band = buscar(arbol,x);

                    if(band==1)
                       cout << "\n\tLocalizado";
                    else
                       cout << "\n\tNo Localizado";
                    break;

               case 4:
                    cout<<" Valor a eliminar: "; cin>> x;
                    eliminar(arbol, x);
                    cout << "\n\tEliminado";
                    break;

               
          }

          cout<<"\n\n\n";
         
    }while(op!=5);

}

