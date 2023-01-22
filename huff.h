#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

//=============
typedef struct{
    int frecuencia;
    char caracter;
} Dato;

typedef struct nodo{
    Dato info;
    struct nodo *izq,*der;
} Elemento_De_Arbol_Binario; 

typedef Elemento_De_Arbol_Binario* Arbol;

struct Nodo{
    Arbol dato;
    struct Nodo* siguiente;
};

typedef struct {
    int cursor; 
    struct Nodo* cabecera;
    struct Nodo* final;
}Elemento_cola;

typedef Elemento_cola* Cola;


//======FUNCTIONS========
Cola crearCola(int *e);
void encolar(Cola *cola, int* e, Arbol datoIngreso);
void desencolar(Cola* cola, int* e, Arbol *datoExtraido);
bool estaVacia(Cola cola,int *e);
void borrarCola(Cola* cola, int *e);
void imprimeCola(Cola* cola, int* e);
void copyCola(Cola *var, Cola constt);
//==========TREE======
Arbol crearNodo(Dato valor); //Genera al nodo raiz de un árbol
void nuevoArbol(Arbol* raiz, Arbol Hizq, Arbol Hder, Dato valorRaiz);
void preOrden(Arbol raiz);
//==========SORTING=========
void  selectionSort (Cola* cola);
void swap(struct Nodo *a, struct Nodo *b);
//========HUFFMAN===========
Arbol huffman(Cola* cola);
void asignaCodigo(Arbol r, int codigo[], int n, char x, FILE* file);
void calculoBits(Arbol r, int n, int* suma);
void leerCodigo(Arbol r, int *code, int* n);
void showCodeword(Arbol r, int codigo[], int n);

//========tests========
