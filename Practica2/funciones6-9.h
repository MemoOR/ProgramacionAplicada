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
 
void buscar(nodo_t *root, char *code, int nivel, char **codes) {
  if (root == NULL)
    return;

  // aloca el espacio de memoria para el codigo
  if (code == NULL)
    code = (char *) calloc(64, sizeof(char));

  // es una hoja del arbol, guarda el codigo
  if (root->der == NULL && root->izq == NULL)
    codes[root->simbolo] = strdup(code);

  // concatena un 0 al codigo
  nivel++;
  strcat(code, "0");
  buscar(root->izq, code, nivel, codes);

  // borra "level - 1" caracteres y concatena un 1 al codigo
  code[nivel - 1] = 0;
  strcat(code, "1");
  buscar(root->der, code, nivel, codes);
}

void codificar(float *frec, char **codes) {
  // generar nuevos codigos
  char texto[1024],nombre[100];
  int len, error = 0;
  FILE *archivo;

  printf("Ingresa el nombre del archivo que quieres codificar:\n\n");
  scanf("%s",nombre);
  getchar();
  archivo=fopen(nombre,"rt");

  if(archivo==NULL){
    printf("Ese archivo no existe\n\n");
    return;
  }else{
    fgets(texto,1023,archivo);
  }
  fclose(archivo);

  len = strlen(texto) - 1;
  texto[len] = 0;

  // verifica que todos los carcteres del mensaje tengan asociado una frecuencia
  for (int i = 0; i < len; i++) {
    if (frec[texto[i]] == 0) {
      printf("El caracter %c no se encuentra guardado\n", texto[i]);
      error = 1;
    }
  }

  limpiar();

  if (error)
    printf("Para generar los codigos, favor de corregir los errores\n");

  else {
    printf("Mensaje codificado:\n");
    for (int i = 0; i < len; i++)
      printf("%s", codes[texto[i]]);

    printf("\n");
  }
  strcat(nombre,"_codificado");
  archivo=fopen(nombre,"w");
  for (int i = 0; i < len; i++)
    fprintf(archivo,"%s", codes[texto[i]]);
  fclose(archivo);

  printf("\nPresiona enter para continuar\n");
  getchar();

  return;
}

void limpiar() {
  char c;
  while ((c = getchar()) != '\n' && c != EOF);
}

void decodificar(float *freq, char **codes) {
  // generar nuevos codigos
  char texto[2048], actual, code[16],nombre[100];
  int len, code_index = 0;

  nodo_t *raiz, *temp;

  temp = raiz;

  FILE *archivo;

  printf("Ingresa el nombre del archivo que quieres codificar:\n\n");
  scanf("%s",nombre);
  getchar();
  archivo=fopen(nombre,"rt");

  if(archivo==NULL){
    printf("Ese archivo no existe\n\n");
    return;
  }else{
    fgets(texto,1023,archivo);
  }
  fclose(archivo);

  len = strlen(texto) - 1;
  texto[len] = 0;

  // para cada 1 o 0 en el mensaje introducido por el usuario
  printf("\nMensaje decodificado:\n");
  for (int i = 0; i <= len; i++) {
    actual = texto[i];

    // si el nodo actual no es nulo
    if (temp != NULL) {
      if (temp->izq == NULL && temp->der == NULL) {
	// imprime el simbolo actual
	printf ("%c", temp->simbolo);
	temp = raiz;

	code_index = 0;
      }

      // recorre a la derecha el arbol
      if (actual == '1') {
	temp = temp->der;
	code[code_index++] = '1';
      }

      // recorre a la izquierda el arbol
      else {
	temp = temp->izq;
	code[code_index++] = '0';
      }
    }
    else {
      code[code_index] = 0;

      printf("Error, el codigo %s no se encuentra registrado\n", code);
      code_index = 0;
    }
  }
  printf("\n");
  strcat(nombre,"_decodificado");
  archivo=fopen(nombre,"w");
  for (int i = 0; i < len; i++)
    fprintf(archivo,"%s", codes[texto[i]]);
  fclose(archivo);

  printf("\nPresiona enter para continuar\n");
  getchar();
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
