/*
AUTHOR: BRANDOM VEGA ENCISO
IIA
22/01/2023
*/


#include "huff.h"


//==============QUEUE===================
Cola crearCola(int *e){
    Cola cola = (Cola)malloc(sizeof(Elemento_cola)); 
    if(cola == NULL){
        *e=-4;
        puts("Couldn't allocate the queue");
    }
    cola->cabecera = NULL; 
    cola->final = NULL;
    cola->cursor = 0;
    *e=0;
    return cola;
}

//Add a element to queue
void encolar(Cola *cola, int* e, Arbol datoIngreso){
    struct Nodo* nodoUsuario = (struct Nodo*)malloc(sizeof(struct Nodo));
    if(nodoUsuario == NULL){
        *e=-6;
        puts("Memory is filled");
    }else if(estaVacia(*cola, e)){ //New queue and there's no elements in there
        nodoUsuario->dato = datoIngreso;
        nodoUsuario->siguiente = NULL;
        (*cola)->cabecera = nodoUsuario;
        (*cola)->final=nodoUsuario;
    }else{ //Case when there's elements 
        nodoUsuario->dato = datoIngreso;
        nodoUsuario->siguiente = NULL;
        (*cola)->final->siguiente = nodoUsuario;
        (*cola)->final = nodoUsuario;
    }
    (*cola)->cursor++;
    *e=0;
}

//Delete node from header
void desencolar(Cola* cola, int* e, Arbol *datoExtraido){

    struct Nodo* nodoAuxiliar=(struct Nodo*)malloc(sizeof(struct Nodo));

    if(estaVacia(*cola,e)){
        printf("\nLa cola se ha vaciado\n");
        return;
    } else if((*cola)->cursor>1){ //When it has elements
        nodoAuxiliar->siguiente = NULL;
        nodoAuxiliar=(*cola)->cabecera;
        (*cola)->cabecera=(*cola)->cabecera->siguiente;
    } else if((*cola)->cursor==1){ //When its the last element
        nodoAuxiliar=(*cola)->cabecera;
        (*cola)->cabecera=NULL;
        (*cola)->final=NULL;
    }
    (*cola)->cursor--;
    *datoExtraido=nodoAuxiliar->dato;
    free(nodoAuxiliar); //Once the node is unlinked we deleted it
    *e=0;
}

//Empty queue
bool estaVacia(Cola cola,int *e){
    if(cola->cabecera == NULL && cola->final== NULL && cola->cursor == 0){
        *e=-1;
        return true;
    }else{
        *e=0;
        return false;
    }
}
//Delete queue
void borrarCola(Cola* cola, int *e){
    if(!estaVacia(*cola, e)){
        struct Nodo* nodoAuxiliar, *nodoAuxiliarRespaldo;
        nodoAuxiliar = (*cola)->cabecera;
        while(nodoAuxiliar != NULL){
            nodoAuxiliarRespaldo = nodoAuxiliar->siguiente;
            free(nodoAuxiliar);
            nodoAuxiliar=nodoAuxiliarRespaldo;
        }
        (*cola)->cabecera = NULL;
        (*cola)->final = NULL;
        (*cola)->cursor = 0;
        *e=0;
        free(*cola);
        printf("\nQueue has been deleted successfully");
    }else{
        printf("\nQueue is already empty");
    }
}
//Print queue
void imprimeCola(Cola* cola, int* e){
    struct Nodo* nodoAuxiliar;
    nodoAuxiliar = (*cola)->cabecera;
    while(nodoAuxiliar != NULL){
        printf("\nCaracter: %c - Freq: %d",nodoAuxiliar->dato->info.caracter, nodoAuxiliar->dato->info.frecuencia); //Char with its frequency
        nodoAuxiliar=nodoAuxiliar->siguiente;
    }
    free(nodoAuxiliar);
}
//Copy queue, i think i didnt use it :p
void copyCola(Cola *var, Cola constt){
    struct Nodo* nodoAuxiliar = (*constt).cabecera;
    Arbol nodo;
    int e;
    while(nodoAuxiliar!=NULL){
        nodo = nodoAuxiliar->dato;
        encolar(var, &e, nodo);
        nodoAuxiliar = nodoAuxiliar->siguiente;
    }
}

//==============Sorting=============
//Selection sort
void  selectionSort (Cola* cola) //In order to improve algorithm complexity you can use a better sorting algorithm
{
    struct Nodo *auxiliar = (*cola)->cabecera;
    struct Nodo *temp = NULL;
    struct Nodo *nodo = NULL;
    // Execute linked list nodo
    while(auxiliar != NULL){
        nodo = auxiliar;
        temp = auxiliar->siguiente;
        // Find the minimum nodo
        while(temp != NULL){
            if (nodo->dato->info.frecuencia > temp->dato->info.frecuencia){
                nodo = temp;
            }
            // Visit to next nodo
            temp = temp->siguiente;
        }
        if (auxiliar->dato->info.frecuencia > nodo->dato->info.frecuencia){
            // Transfer minimum value to initial position
            // Swap the nodo value
            swap(auxiliar, nodo);
        }
        // Visit to next nodo
        auxiliar = auxiliar->siguiente;
    }
}

/* function to swap data of two nodes a and b*/
void swap(struct Nodo *a, struct Nodo *b){
    Arbol temp = a->dato;
    a->dato = b->dato;
    b->dato = temp;
}

//==================TREE==================
Arbol crearNodo(Dato valor){
    Arbol arbol=(Arbol) malloc(sizeof(Elemento_De_Arbol_Binario));
    if(arbol==NULL){
        perror("Memory for the node has been filled");
    } else{
        arbol->izq=arbol->der=NULL;
        arbol->info=valor;
    }
    return arbol;
}
//Create a new tree
void nuevoArbol(Arbol* raiz, Arbol Hizq, Arbol Hder, Dato valorRaiz){ 
    (*raiz)=crearNodo(valorRaiz);
    (*raiz)->der=Hder;
    (*raiz)->izq=Hizq;
}
//Pre order to see if the tree has been created successfully
void preOrden(Arbol raiz){ 
    if(raiz){
		printf("letra:%c-frec:%d   ",raiz->info.caracter, raiz->info.frecuencia);
		preOrden(raiz->izq);
		preOrden(raiz->der);
	}
}
//Codification 
Arbol huffman(Cola* cola){
    //We sort the nodes and create a tree that mix the smalles frequency until 
    Arbol z;
    Dato nueva_raiz;    //Where are gona be stored the mixed nodes
    Arbol freq_x, freq_y;   //The smalles frequency x, y that are gonna be mixed
    int n=(*cola)->cursor;  //How many elements are left
    int i=0, e=0;   

    for(i=0; i<n-1; i++){   
        selectionSort(cola);    //Sort the queue with the nodes 
        //printf("\nCuya cabecera es: %c", (*cola)->cabecera->dato->info.caracter);
        desencolar(cola, &e, &freq_x);  //Put out two elements and save it in the node
        desencolar(cola, &e, &freq_y);

    
        nueva_raiz.caracter = 'z';  //Any character you want to save
        nueva_raiz.frecuencia = freq_x->info.frecuencia + freq_y->info.frecuencia; //Add frequency
    
        nuevoArbol(&z, freq_x, freq_y,nueva_raiz);    //create a new tree with the data

        encolar(cola, &e, z);       //Store it inside the queue again

    }
    return z;   //Once we got one tree left
}


//========================HUFFMAN CODIFICATION==================



void asignaCodigo(Arbol r, int codigo[], int n, char x, FILE* file){
    int i;                                  
    if((r->izq==NULL) && (r->der==NULL)){   //If the leaf is not the caracter we want to read, we dont use it
        if(r->info.caracter==x){            //We take the character
            for(i=0; i< n; i++){            //n indicate the number of bits used
                printf("%d", codigo[i]);
                fputc(codigo[i], file);     //Write the n code in the array to the file
            }
            printf("");
        }
    } else{
        codigo[n]=0; //We suppose its gonna start by the left
        n++;
        asignaCodigo(r->izq,codigo,n,x, file);
        codigo[n-1]=1; //In case we are gonna go the right
        asignaCodigo(r->der,codigo,n,x, file);
    }
}


void calculoBits(Arbol r, int n, int* suma){
    if((r->izq==NULL) && (r->der==NULL)){
        suma[0] = (n*r->info.frecuencia)+suma[0];   //cost after the reduction
        suma[1] = (8*r->info.frecuencia)+suma[1];   //cost before the reduction
    } else{
        n++;                                        
        calculoBits(r->izq,n,suma);
        calculoBits(r->der,n,suma);
    }
}
//Uncode, read code
void leerCodigo(Arbol r, int *code, int* n){
    if((r->izq==NULL) && (r->der==NULL)){
        printf("%c", r->info.caracter);
    } else{
        if(code[*n]==0){
            (*n)++;
            leerCodigo(r->izq,code,n);   
        }else{
            (*n)++;
            leerCodigo(r->der,code,n);
        }
    }
}
//In case you want to see what is the codeword
void showCodeword(Arbol r, int codigo[], int n){
    int i;
    if((r->izq==NULL) && (r->der==NULL)){
        printf("\n\t%c Codigo: ",r->info.caracter);
        for(i=0; i< n; i++)
            printf("%d", codigo[i]);
    } else{
        codigo[n]=0; //Suponemos que siempre ira por la izquierda
        n++;
        showCodeword(r->izq,codigo,n);
        codigo[n-1]=1; //Por si el recorrido tuvo que ser por la derecha
        showCodeword(r->der,codigo,n);
    }
}