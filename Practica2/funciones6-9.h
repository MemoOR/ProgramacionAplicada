void codigos_arbol(lista_t **inicio){
  lista_t *temp;
  nodo_t *nodo1,*nodo2,*nodo_padre=NULL;
  int suma_prob=0, suma_arbol,n_elementos,i=0;
  float menor,mayor;
  char sim_men,sim_may;
  temp=*inicio;

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
  if(suma_prob!=100){
    printf("\nLa suma de probabilidades es diferente a 100%c\n\n",'%');
    return;
  }

  
  //Comienza a crear el arbol

  while((temp = pop(inicio)) != NULL && (temp = pop(inicio)) != NULL){
    nodo1->codigo=0;
    nodo2->codigo=1;

    suma_arbol=nodo1->probabilidad+nodo2->probabilidad;

    nodo_padre=crear_nodo(';',0,suma_arbol,nodo1,nodo2,NULL);

    nodo1->padre=nodo_padre;
    nodo2->padre=nodo_padre;

    insertar_lista(inicio,0,suma_arbol);
  }
}
			  
nodo_t *crear_nodo(char letra, char code, float prob,
        nodo_t *izq, nodo_t *der, nodo_t *padre) {

    // crea un nuevo nodo para el arbol
    nodo_t *nuevo = (nodo_t *) malloc(sizeof(nodo_t));

    nuevo->simbolo = letra;
    nuevo->codigo = code;
    nuevo->probabilidad = prob;

    nuevo->izq = izq;
    nuevo->der = der;
    nuevo->padre = padre;

    return nuevo;
}


lista_t *pop(lista_t **inicio){
  lista_t *temp;
  lista_t *elemento;

  // checa que haya objetos
  if (*inicio == NULL)
    return NULL;
  // obtiene el ultimo elemento del stack 
  temp = *inicio; 
  elemento = temp;
  *inicio = (*inicio)->sig;
  free(temp);
  printf("%c",(*inicio)->sim);
  return elemento;
}


void generar_codigo(){
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
