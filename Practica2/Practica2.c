/*
 * @Practica2.c
 *
 * @Práctica 2:Códigos de longitud variable mediante el algoritmo de Greedy 
 *
 * @author Guillermo Ortega,Sergio Sarabia
 * @date 25/01/18
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>//libreria para stdin
#include <termios.h>

#define CLS system("clear")

typedef struct nodo_t{
  char simbolo;
  float probabilidad;
  int codigo;
  struct nodo_t *padre,*izq,*der;
}nodo_t;

typedef struct lista_t{
  int sim;
  float prob;
  struct lista_t *sig,*ant,*pos;
}lista_t;

#include"define.h"//fichero para declarar las funciones 
#include"funciones1-5.h"//fichero con primeras cinco opciones del menú
#include"funciones6-9.h"//fichero con las funciones para generar el código

void menu(int *opcion){
  printf("[1]Ingresar símbolo\n");
  printf("[2]Listar símbolos\n");
  printf("[3]Borrar símbolo\n");
  printf("[4]Guardar símbolos y probabilidades en archivo\n");
  printf("[5]Leer  símbolos y probabilidades de archivo\n");
  printf("[6]Generar código\n");
  printf("[7]Codificar mensaje\n");
  printf("[8]Decodificar mensaje\n");
  printf("[9]Salir\n");
  scanf("%d",opcion);
  getchar();
  CLS;
  }

int main(){
  creditos();

  lista_t *primero_lista=NULL;
  nodo_t *raiz;
  int opcion;
  char simbolo,eliminar,*codes[255];
  float probabilidad,frec[255];

  for(int i=0;i<255;i++){
    frec[i]=0;
  }
  
  do{
  menu(&opcion);

  switch(opcion){
  case 1:
    printf("Ingresa el símbolo: ");
    scanf("%c",&simbolo);
    printf("Ingresa la probabilidad: ");
    scanf("%f",&probabilidad);
    insertar_lista(&primero_lista,simbolo,probabilidad);
    break;
  case 2:
    imprimir_lista(primero_lista);
    break;
  case 3:
    printf("Ingresa el símbolo que quieres borrar:");
    scanf("%c",&eliminar);
    getchar();
    borrar_simbolo(&primero_lista,eliminar);
    break;
  case 4:
    Guardar_lista(primero_lista);
    break;
  case 5:
    Leer_lista(&primero_lista);
    break;
  case 6:
    codigos_arbol(&primero_lista,raiz,codes,frec);
    break;
  case 7:
    codificar(frec,codes);
    break;
  case 8:
    decodificar(frec,codes);
    break;
  default:
    Borrar_lista(primero_lista);
    Borrar_arbol(raiz);
    break;
  }
  }while(opcion!=9);
  return 0;
}


