// Esta función deshabilita el modo canónico en la terminal,
// con el fin de evitar que se tenga que presionar enter
// en la pantalla principal.
struct termios original_f, modified_f;
void disable_canonical() {
    setbuf(stdout, NULL);
    tcgetattr(STDIN_FILENO, &original_f);

    modified_f = original_f;
    modified_f.c_lflag &= ~(ICANON|ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &modified_f);
}

// Esta función habilita el modo canónico en la terminal
void enable_canonical() {
    tcgetattr(STDIN_FILENO, &original_f);

    original_f.c_lflag |= (ICANON|ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &original_f);
}

//funcion para los creditos del programa
void creditos() { 
    CLS;

    printf("Universidad Iberoamericana\n");
    printf("Programación Aplicada\n\n");

    printf("Este programa fue desarrollado por:\n");
    printf("\tGuillermo Ortega\n");
    printf("\tSerio Sarabia\n");

    printf("\n\nPresiona enter para entrar al sistema...");

    disable_canonical();
    getchar();
    enable_canonical();

    CLS;
}

void insertar_lista(lista_t **inicio,char simbolo,int prob){
  lista_t *temp,*temp2,*ant,*pos;
  
  temp=(lista_t* ) calloc(1,sizeof(lista_t));
  temp->sim=simbolo;
  temp->prob=prob;

  if(*inicio==NULL){
    temp->sig=*inicio;
    *inicio=temp;
    (*inicio)->ant=NULL;
  }else{
    
    //valida que no se haya ingresado el símbolo anteriormente
    temp2=*inicio;
    while(temp2!=NULL){
      if(temp2->sim==simbolo){
	printf("\nSímbolo ya ingresado\n\n");
	return;
      }
      temp2=temp2->sig;
    }
    
    pos=*inicio;
    while(pos!=NULL && pos->prob < temp->prob){
      pos=pos->sig;
    }
    
    if(pos!=*inicio){
      ant=*inicio;
      while(ant->sig!=pos){
	ant=ant->sig;
      }
      ant->sig=temp;
      temp->sig=pos;
      temp->ant=ant;
    }
    else{
      temp->sig=*inicio;
      *inicio=temp;
      (*inicio)->ant=NULL;
    }
  }
}

void imprimir_lista(lista_t *inicio){
  lista_t *temp;
  temp=inicio;
  if(temp==NULL){
    printf("No se han ingresado símbolos\n");
    return;
  }
  while(temp!=NULL){
    printf("Símbolo: %c\n",temp->sim);
    printf("Probabilidad: %.2f%c \n\n",temp->prob,'%');
    temp=temp->sig;
  }
}

void borrar_simbolo(lista_t **inicio,char sim){
  lista_t *temp;
  temp=*inicio;

  if(temp==NULL){
    printf("\nNo se han ingresado símbolos\n\n");
    return;
  }
  
  while((temp!=NULL)&&(temp->sim != sim))
    temp=temp->sig;

  if(temp!=NULL){
    if(temp==*inicio){
      *inicio=temp->sig;
      free(temp);
    }else if(temp->sig==NULL){
    temp->ant->sig=temp->sig;
    free(temp);
    }else{
      temp->ant->sig=temp->sig;
      temp->sig->ant=temp->ant;
      free(temp);
    }
  }
}

void Guardar_lista(lista_t *inicio){
  lista_t *temp,*temp2;
  temp=inicio;
  temp2=inicio;
  int suma=0,total=0;

  //valida que existan símbolos ingresados y que la suma de
  //probabilidades sea igual a 100%
  if(temp==NULL){
    printf("No se han ingresado símbolos\n");
    return;
  }
  while(temp!=NULL){
    suma+=temp->prob;
    total++;
    temp=temp->sig;
  }
  if(suma!=100){
    printf("\nLa suma de probabilidades es diferente a 100%c\n\n",'%');
    return;
  }

  //Guarda el archivo si se cumplen las condiciones anteriores
  FILE *archivo;
  char filename[]={"Simbolos.txt"};

  archivo=fopen(filename,"r");

  if(archivo==NULL){
    archivo=fopen(filename,"wt");
    while(temp2!=NULL){
      fprintf(archivo, "%c ",temp2->sim);
      fprintf(archivo, "%.2f\n",temp2->prob);
      temp2=temp2->sig;
    }
  }else{
    fclose(archivo);
    char opcion;
    printf("\nYa existe un archivo de símbolos, ¿deseas sobreescribirlo? [s/n]\n");
    
    do{
      scanf("%c",&opcion);
    }while(opcion!='s' && opcion!='n');
    getchar();
    
    if(opcion=='s'){
      archivo=fopen(filename,"wt");
      while(temp2!=NULL){
      fprintf(archivo, "%c ",temp2->sim);
      fprintf(archivo, "%.2f\n",temp2->prob);
      temp2=temp2->sig;
      }
    }else{
      printf("\nNo se guardaron los símbolos\n\n");
      return;
    }
  }
  printf("\nGuardado correctamente en %s\n\n",filename);
  
  fclose(archivo);
}

void Leer_lista(lista_t **inicio){
  FILE *archivo;
  char filename[] = {"Simbolos.txt"};
  char opcion,simbolo;
  float probabilidad;

  archivo=fopen(filename,"r");
  if(archivo==NULL){
    printf("\nNo hay ningun archivo guardado\n\n");
    return;
  }

  if(*inicio!=NULL){
    printf("\nYa ingresaste símbolos, ¿deseas sobreescribirlos con los del archivo?[s/n]\n\n");
    do{
      scanf("%c",&opcion);
    }while(opcion!='s' && opcion!='n');
    getchar();

    if(opcion=='s'){
      Borrar_lista(*inicio);
      while (!feof(archivo)) {
	fscanf(archivo, "%c ",&simbolo);
	fscanf(archivo, "%f\n",&probabilidad);
	insertar_lista(inicio,simbolo,probabilidad);
      }
      fclose(archivo);
      return;
    }
    else{
      printf("\nNo se leyó el archivo\n\n");
      return;
    }
  }

  if(archivo!=NULL){
    while (!feof(archivo)) {
      fscanf(archivo, "%c ",&simbolo);
      fscanf(archivo, "%f\n",&probabilidad);
      insertar_lista(inicio,simbolo,probabilidad);
    }
  }
  fclose(archivo);
}

