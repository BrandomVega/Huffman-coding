/*
AUTHOR: BRANDOM VEGA ENCISO
IIA
22/01/2023
*/



#include "huff.h"

void main(){
    int ascii[100]={0}; //Character ascii needed
    int codigo[32]={0}; //Where binary are gonna be stored
    int suma[2] = {0}; //cost
    int i,e;

    FILE *file = fopen("archivo.txt","r"); //read file   
    if(file==NULL){printf("\nEl archivo no se puede abrir");}
    FILE *result = fopen("resultadoBinario.txt","w+");      //result 
    if(result==NULL){printf("\nEl archivo no se puede abrir");}

    Cola cola = crearCola(&e);
    Dato caracter;
    Arbol nodo_caracter, raiz;
    
    //Save frequency of the characters in the file
    while(!feof(file)){
        ascii[fgetc(file)-' ']++;   
    }   
    //chars with at least one of frequency are gonna be separated
    for (int i = 0; i < 100; i++){
        if(ascii[i]!=0){
            caracter.caracter = i+' ';
            caracter.frecuencia = ascii[i];
            nodo_caracter = crearNodo(caracter);    //create a tree type node
            encolar(&cola, &e, nodo_caracter);    
        }
    }
    printf("\nCARACETERES Y SU FRECUENCIA:");
    imprimeCola(&cola, &e);


    raiz = huffman(&cola);  

    calculoBits(raiz, 0, suma); //Cost


    printf("\n\nARBOL EN PREORDEN:\n");
    preOrden(raiz);

    rewind(file);
    printf("\n\nBINARIO GUARDADO:\n");
    while(!feof(file)){
        asignaCodigo(raiz, codigo, 0, fgetc(file), result);   
    } 

    //decodification
    //Note: When read the file we got an extra bit '1' so i had to put it out of the array
    int* dataToDecode = (int*)malloc(sizeof(int)*suma[0]);  
    if(dataToDecode==NULL)exit(-1);
    //Read bit by bit and save it in the array
    char buffer;
    i=0;
    rewind(result);
    while(!feof(result)){
        fread(&buffer, sizeof(buffer), 1, result);  
        dataToDecode[i] = buffer;
        i++;
    }

    printf("\n\nDECODIFICACION:\n");
    int n=0;
    while(n<suma[0]){
        leerCodigo(raiz, dataToDecode, &n);
    }

    //Analysis of reduction percentage
    printf("\n\nANALISIS:\n");
    printf("Paso de %dbits a %dbits(costo) -> %d%% de reduccion\n\n", suma[1], suma[0], 100-((suma[0]*100)/suma[1]));
    printf("CODEWORDS:");
    showCodeword(raiz, codigo, 0);

    
   // fclose(file);
   // fclose(result);

    printf("\n\nFin");
}

