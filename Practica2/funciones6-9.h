void codigos_arbol(lista_t **inicio, nodo_t *raiz,char **codes,float *frec){
  lista_t *temp,*temp2;
  nodo_t *nodo_padre=NULL;
  int suma_prob=0, suma_arbol;
  float menor,mayor;
  char sim_men,sim_may;

  temp=*inicio;
  temp2=*inicio;

  //valida que existan símbolos ingresados y que la suma de
  //probabilidades sea igual a 100%
  if(temp==NULL){
    printf("No se han ingresado símbolos\n");
    return;
  }
  while(temp!=NULL){
    suma_prob+=temp->prob;
    frec[temp->sim]=temp->prob;
    temp=temp->sig;
  }

  if(suma_prob!=100){
    printf("\nLa suma de probabilidades es diferente a 100%c\n\n",'%');
    return;
  }

  //crea el arbol
  while((temp = pop(inicio)) != NULL && (temp = pop(inicio)) != NULL){
    nodo_t *nodo1 = (nodo_t *) malloc(sizeof(nodo_t));
    nodo_t *nodo2 = (nodo_t *) malloc(sizeof(nodo_t));
    nodo1->codigo=0;
    nodo2->codigo=1;
     
    suma_arbol=nodo1->probabilidad+nodo2->probabilidad;
    
    nodo_padre=crear_nodo(';',0,suma_arbol,nodo1,nodo2,NULL);
    
    nodo1->padre=nodo_padre;
    nodo2->padre=nodo_padre;
    
    insertar_lista(inicio,0,suma_arbol);
  }
  raiz=nodo_padre;
  getchar();
  
  buscar(raiz,NULL,0,codes);

  for (int i = 0; i < 255; i++)
    if (frec[i] != 0)
      printf("Simbolo %c: %s\n", i, codes[i]);
  return;
}

//crea un nuevo nodo padre para el arbol
nodo_t *crear_nodo(char letra, char code, float prob,
        nodo_t *izq, nodo_t *der, nodo_t *padre){

    nodo_t *nuevo = (nodo_t *) malloc(sizeof(nodo_t));

    nuevo->simbolo = letra;
    nuevo->codigo = code;
    nuevo->probabilidad = prob;

    nuevo->izq = izq;
    nuevo->der = der;
    nuevo->padre = padre;

    return nuevo;
}

//elimina los elementos ya leidos de la lista para
//insertarlos en el arbol
lista_t *pop(lista_t **inicio){
  lista_t *temp;

  // checa que haya objetos
  if ((*inicio) == NULL)
    return NULL;
  
  // obtiene valor mas pequeño y lo regresa 
  temp = *inicio;
  if((*inicio)->sig==NULL){
    while(*inicio!=NULL){
      *inicio=(*inicio)->sig;
      free(temp);
      return temp;
    }
  }
  *inicio=(*inicio)->sig;
  free(temp);
  
  return temp;
}
 
void buscar(nodo_t *raiz, char *buscado,int nivel,char **codes){
  if (raiz == NULL)
      return;

  // aloca el espacio de memoria para el codigo
  if (buscado == NULL)
    buscado = (char *) calloc(64, sizeof(char));

  // si es una hoja del arbol, guarda el codigo
  if (raiz->der == NULL && raiz->izq == NULL){
    codes[raiz->simbolo] = strdup(buscado);
  }

  // agrega un 0 al codigo
  nivel++;
  strcat(buscado, "0");
  buscar(raiz->izq, buscado, nivel, codes);
  // borra "nivel-1" caracteres y agrega un 1 al codigo
  buscado[nivel - 1] = 0;
  strcat(buscado, "1");
  buscar(raiz->der, buscado, nivel, codes);
}
void guardar_codigo(){
}

void codificar(){
}

void decodificar(){
}

int Borrar_lista(lista_t *inicio){
 lista_t *temp;
  temp=inicio;
  while(temp!=NULL){
    inicio=temp->sig;
    free(temp);
    temp=inicio;
  }
  return 0;
}

void Borrar_arbol(struct nodo_t *p){
  if(p!=NULL){
    Borrar_arbol(p->izq);
    Borrar_arbol(p->der);
    free(p);
  }
}
