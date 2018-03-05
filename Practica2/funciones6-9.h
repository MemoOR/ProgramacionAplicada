void codigos(lista_t *inicio){
  lista_t *temp,*temp2;
  int suma_prob=0, suma_arbol;
  int menor,mayor;
  temp=inicio;

  //valida que existan símbolos ingresados y que la suma de
  //probabilidades sea igual a 100%
  if(temp==NULL){
    printf("No se han ingresado símbolos\n");
    return;
  }
  while(temp!=NULL){
    suma_prob+=temp->prob;
    temp=temp->sig;
  }
  if(suma!=100){
    printf("\nLa suma de probabilidades es diferente a 100%c\n\n",'%');
    return;
  }

  //Comienza a crear el arbol

  while(temp!=NULL){
    menor=temp->sim;
    mayor=temp->sig->sim;
    *inicio=temp->sig;
    free(temp);
    *inicio=temp->sig;
    free(temp);
    
    struct nodo_t *hojas_1=(struct nodo_t*)calloc(1,sizeof(struct nodo_t));
    hojas_1->izq=NULL;
    hojas_1->der=NULL;
    hojas_1->sim=menor;
    struct nodo_t *hojas_2=(struct nodo_t*)calloc(1,sizeof(struct nodo_t));
    hojas_2->izq=NULL;
    hojas_2->der=NULL;
    hojas_2->sim=mayor;
    
    insertar_arbol(hojas_1,hojas_2);
  }
}

void insertar_arbol(){
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
