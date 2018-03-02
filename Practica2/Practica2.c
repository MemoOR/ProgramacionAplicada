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
  
}nodo_t;

typedef struct lista_t{
  int sim;
  float prob;
  struct lista_t *sig,*ant,*pos;
}lista_t;

#include"define.h"//fichero para declarar las funciones 
#include"funciones.h"//fichero con algunas funciones utilizadas


void menu(int *opcion){
  printf("[1]Ingresar símbolo\n");
  printf("[2]Listar símbolos\n");
  printf("[3]Borrar símbolo\n");
  printf("[4]Guardar símbolos y probabilidades en archivo\n");
  printf("[5]Leer  símbolos y probabilidades de archivo\n");
  printf("[6]Generar código\n");
  printf("[7]Codificar mensaje\n");
  printf("[8]Decodificar mensaje\n");
  printf("Para salir pulsa cualquier otro número\n");
  scanf("%d",opcion);
  getchar();
  CLS;
  }

int main(){
  creditos();

  lista_t *primero=NULL;
  int opcion;
  char simbolo,eliminar;
  float probabilidad;
  
  do{
  menu(&opcion);

  switch(opcion){
  case 1:
    printf("Ingresa el símbolo: ");
    scanf("%c",&simbolo);
    printf("Ingresa la probabilidad: ");
    scanf("%f",&probabilidad);
    insertar_lista(&primero,simbolo,probabilidad);
    break;
  case 2:
    imprimir_lista(primero);
    break;
  case 3:
    printf("Ingresa el símbolo que quieres borrar:");
    scanf("%c",&eliminar);
    getchar();
    borrar_simbolo(&primero,eliminar);
    break;
  case 4:
    break;
  case 5:
    break;
  case 6:
    break;
  case 7:
    break;
  case 8:
    break;
  default: break;
  }
  }while(opcion==1 || opcion==2 || opcion==3);
  return 0;
}


