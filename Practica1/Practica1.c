/*
 * @Practica1.c
 *
 * @Manejo de imagenes en formato PGM
 *
 * @author Guillermo Ortega
 * @date 25/01/18
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CLS system("clear")

typedef struct Imagen{
  int x, y, max;
  char tipo[3];
  unsigned int **pixeles;
}Imagen;

//funcion para los creditos del programa
void creditos() { 
    CLS;

    printf("Universidad Iberoamericana\n");
    printf("Programación Aplicada\n\n");

    printf("Este programa fue desarrollado por:\n");
    printf("\tGuillermo Ortega\n");

    printf("\n\nPresiona enter para entrar al sistema...");

    getchar();

    CLS;
}

//Valida si iexiste el archivo y lo abre
Imagen *Abrir_archivo(char *name){

  CLS;
  FILE *Foto;
  char datos[100];
  Imagen *Img=(Imagen*)malloc(sizeof(Imagen));
  
  Foto=fopen(name,"r");//abre el archivo PGM
  
  //valida si existe el archivo
  if(Foto==NULL){
    CLS;
    printf("\n No existe el archivo: %s\n\n",name);
    usleep(1000000);
    CLS;
    exit(0);
  }

  printf("\n Archivo encontrado...\n\n");

  //lee el encabezado del formato de la imagen
  fread(Img->tipo, 2, 1, Foto);
  fscanf(Foto,"%d %d %d ",&Img->x, &Img->y, &Img->max);
  fseek(Foto,1,SEEK_CUR);
  
  printf("\tMedidas: %s %d %d %d",Img->tipo,Img->x,Img->y,Img->max);

  //obtiene memoria para colimnas y renglones de la imagen
  Img->pixeles=(unsigned int**)malloc(sizeof(unsigned int**) * Img->y);
  for (int i=0; i<Img->y; i++){
    Img->pixeles[i] = (unsigned int*) malloc(sizeof(unsigned int*) * Img->x);
  }

  printf("\n Archivo cargado correctamente...\n\n");

  //lee los datos de cada pixel
  for (int i=0; i<(Img->y); i++) {
    for (int j=0; j<Img->x; j++) {
      fread(&Img->pixeles[i][j],1,1,Foto);
    }
  }
  
  fclose(Foto);

  return Img;//regresa un dato de tipo estructura imagen
}


void Borrar(Imagen **Img);//libera el espacio de la imagen
void Guardar(Imagen *Img);//guarda la imagen modificada
void Negativo(Imagen *Img);//obtiene el negativo de la imagen
void Ecualizar(Imagen *Img);//obtiene la imagen ecualizada
void Reducir(Imagen *Img);//reduce la imagen
void Ampliar(Imagen *Img);//amplia la imagen

//menu pincipal de operaciones del programa
void menu(int *opcion, Imagen *Img){

  printf("[1]Negativo\n");
  printf("[2]Ecualizar\n");
  printf("[3]Reducir\n");
  printf("[4]Ampliar\n");
  printf("Pulsa cualquier otra tecla para salir\n");
  scanf("%d",opcion);
  getchar();

  switch (*opcion){
  case 1: Negativo(Img); break;
  case 2: Ecualizar(Img); break;
  case 3: Reducir(Img); break;
  case 4: Ampliar(Img); break;
  default: break;
  }
  CLS;
}

//funcion principal
int main(){

  Imagen *Principal;
  char Nombre[50];
  int opcion;
  
  creditos();

  //repetir mientras el usiario no escoja salir del programa
  do{
  printf("\nIntroduce el nombre del archivo que deseas modificar: \n");
  printf("\tIntroduce cualquier caracter para salir del programa\n");

  scanf("%s",Nombre);//lee el nombre del archivo que se va a abrir

  Principal = Abrir_archivo(Nombre);//datos de la imagen 

  menu(&opcion,Principal);
  }while(opcion==1 || opcion==2 || opcion==3 || opcion==4);

  return 0;
}

//libera el espacio de memoria ocupado por la imagen
void Borrar(Imagen **Img){
  for (int i=0; i<(*Img)->y; i++){
    free((*Img)->pixeles[i]);
  }

  free((*Img)->pixeles);

  free(*Img);

  *Img = NULL;
}

//Guarda la imagen con el nombre que diga el usuario
void Guardar(Imagen *Img){

  FILE *Nueva_imagen;
  char Nuevo_nombre[100];
  char Primera_linea[100];
  
  printf("¿Qué nombre le quieres poner al nuevo archivo?\n\n");
  scanf("%s",Nuevo_nombre);

  printf("\nGuardando...\n");
  
  Nueva_imagen=fopen(Nuevo_nombre,"wb");//crea el nuevo archivo donde se guardara la imagen modificada

  //guarda el encabezado del formato de la imagen en el nuevo archivo
  sprintf(Primera_linea,"%s %d %d %d ",Img->tipo, Img->x, Img->y, Img->max);
  fwrite(Primera_linea,strlen(Primera_linea),1,Nueva_imagen);
 
  printf("\nGuardando...\n");

  //guarda los nuevos valores de pixeles
  for (int j=0; j<Img->y; j++){
    for (int i=0; i<Img->x; i++){
      fputc(Img->pixeles[j][i], Nueva_imagen);
    }
  }
  
  fclose(Nueva_imagen);

  printf("\nGuardando...\n");

  Borrar(&Img);

  printf("\nImagen guardada con éxito\n\n");
}

//obtiene el negativo de la imagen y la manda a la funcion guardar
void Negativo(Imagen *Img){
  for (int j = 0; j<Img->y; j++){
    for (int i = 0; i<Img->x; i++){
      Img->pixeles[j][i] = 255 - (Img->pixeles[j][i]);
    }
  }

  printf("\nNegativo obtenido con éxito\n");
  
  Guardar(Img);
}

//ecualiza la imagen y la manda a la funcion guardar
void Ecualizar(Imagen *Img){

  //crea un arreglo de intensidades de los pixeles
  unsigned long *frequencia = (unsigned long *) calloc(Img->max + 1,sizeof(unsigned long));

  int pixel = Img->x * Img->y;
  int n = 0;

  //recorre los valores de pixeles para la tabla de las frecuencias
  for (int y = 0; y < Img->y; y++) {
    for (int x = 0; x < Img->x; x++) {
      n = Img->pixeles[y][x];
      frequencia[n]++;
    }
  }

  //genera la tabla de frecuancias
  for (int i=1; i<Img->max+1; i++){
    frequencia[i] += frequencia[i-1];
  }

  //se obtienen los nuevos valores de los pixeles de la imagen
  for(int y=0; y<Img->y; y++) {
    for (int x=0; x<Img->x; x++) {
      n = Img->pixeles[y][x];
      Img->pixeles[y][x] = Img->max * ((float) frequencia[n] / (float) pixel);
    }
  }

  free(frequencia);

  printf("\nImagen ecualizada con éxito\n");
  
  Guardar(Img);
}

//Obtiene la imagen reducida y la envia a la funcion guardar
void Reducir(Imagen *Img){
  int x,y;
  //nuevos valores de altura y anchura del arreglo
  x=(Img->x)/2;
  y=(Img->y)/2;

  //genera una nueva estructura de imagen para almacenar la imagen reducida
  Imagen *New=(Imagen*)malloc(sizeof(Imagen));

  //se guardan los valores de formato en la nueva estructura
  New->x=x;
  New->y=y;
  New->max=Img->max;
  strcpy(New->tipo,Img->tipo);

  printf("%s %d %d %d\n",New->tipo,New->x,New->y,New->max);

  //aparta espacios de memoria para los pixeles de la nueva imagen
  New->pixeles=(unsigned int**)malloc(sizeof(unsigned int**) * New->y);
  for (int i=0; i<Img->y; i++){
    New->pixeles[i] = (unsigned int*) malloc(sizeof(unsigned int*) * New->x);
  }

  int suma;

  //obtiene el promedio de cuatro pixeles para asignarlos al pixel de la nueva imagen
  for (int j = 0; 2*j+1 < Img->y; j++){
    for (int i = 0; 2*i+1 < Img->x; i++){
      suma = Img->pixeles[2*j][2*i];
      suma = Img->pixeles[2*j][2*i+1];
      suma = Img->pixeles[2*j+1][2*i];
      suma = Img->pixeles[2*j+1][2*i+1];
      
      New->pixeles[j][i] = (suma/4);
    }
  }
  printf("\nImagen reducida con éxito\n");

  Guardar(New);

  Borrar(&Img);
}

//Obtiene la imagen ampliada y la envia a la funcion guardar
void Ampliar(Imagen *Img){
  int x,y;
  //nuevos valores de altura y anchura de la imagen
  x=(Img->x)*2;
  y=(Img->y)*2;

  //nueva estructura de tipo imagen para almacenar los valores de la nueva imagen
  Imagen *New=(Imagen*)malloc(sizeof(Imagen));

  //asigna valores de formato a la nueva imagen
  New->x=x;
  New->y=y;
  New->max=Img->max;
  strcpy(New->tipo,Img->tipo);

  //guarda memoria para los pixeles de la nueva imagen
  New->pixeles=(unsigned int**)malloc(sizeof(unsigned int**) * New->y);
  for (int i=0; i<Img->y; i++){
    New->pixeles[i] = (unsigned int*) malloc(sizeof(unsigned int*) * New->x);
  }

  printf("%s %d %d %d\n",New->tipo,New->x,New->y,New->max);

  //copia los valores de los renglones y columnas de la imagen original
  //en el nuevo arreglo de pixeles para la nueva imagen
  for (int j = 0; j < Img->y; j++){
    for (int i = 0; i < Img->x; i++){
      if(j < New->y && i < New->x){
	New->pixeles[j][i]=Img->pixeles[j][i];
	New->pixeles[j+1][i]=Img->pixeles[j][i];
	New->pixeles[j][i+1]=Img->pixeles[j][i];
	New->pixeles[j+1][i+1]=Img->pixeles[j][i];
      }
      i+=1;
    }
    j+=1;
  }

  printf("\nImagen aumentada con éxito\n");
  
  Guardar(New);

  free(Img);
}
