void codigos_arbol(lista_t **inicio, nodo_t *raiz){
  lista_t *temp,*temp2;
  nodo_t *nodo1 = (nodo_t *) malloc(sizeof(nodo_t));
  nodo_t *nodo2 = (nodo_t *) malloc(sizeof(nodo_t));
  nodo_t *nodo_padre=NULL;
  int suma_prob=0, suma_arbol,n_elementos,x=0,encontrar=0;
  float menor,mayor;
  char sim_men,sim_may,aux[50];

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
    n_elementos++;
    temp=temp->sig;
  }
  
  char simbolos[n_elementos];
  int codigos[n_elementos];
  
   while(temp2!=NULL){
     simbolos[x]=temp2->sim;
     x++;
     temp2=temp2->sig;
   }
   for(int i=0;i<n_elementos-1;i++){
     printf("%c ",simbolos[i]);
   }
   
   if(suma_prob!=100){
     printf("\nLa suma de probabilidades es diferente a 100%c\n\n",'%');
     return;
   }

  //crea el arbol
  while((temp = pop(inicio)) != NULL && (temp = pop(inicio)) != NULL){  
    nodo1->codigo=0;
    nodo2->codigo=1;
     
    suma_arbol=nodo1->probabilidad+nodo2->probabilidad;
    
    nodo_padre=crear_nodo(';',0,suma_arbol,nodo1,nodo2,NULL);
    
    nodo1->padre=nodo_padre;
    nodo2->padre=nodo_padre;

    insertar_lista(inicio,0,suma_arbol);
  }
  raiz=nodo_padre;

  for(int i=0;i<n_elementos;i++){
    buscar(0,&encontrar,raiz,aux,simbolos[i]);
  }
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

void buscar(int nivel, int *encontrar, nodo_t *hoja,char *aux, char buscado){

  if(hoja!=NULL && buscado==hoja->simbolo){
    *encontrar=1;
  }
  
  if(*encontrar==0 && hoja!=NULL){
    aux[nivel]='0';
    buscar(nivel+1, encontrar, hoja->izq,aux, buscado);
    if(*encontrar==0 && hoja!=NULL){
      aux[nivel]='1';
      aux[nivel+1]='\0';
      buscar(nivel+1, encontrar, hoja->der,aux, buscado);
    }
  }
  else if(hoja==NULL){
    aux[nivel]='\0';
  }
  else if(*encontrar==1){
    aux[nivel]='\0';
  }
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
