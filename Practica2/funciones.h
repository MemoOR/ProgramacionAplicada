
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
  lista_t *temp,*ant,*pos;
  
  temp=(lista_t* ) malloc(sizeof(lista_t));
  temp->sim=simbolo;
  temp->prob=prob;

  if(*inicio==NULL){
    temp->sig=*inicio;
    *inicio=temp;
  }else{
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
    }
    else{
      temp->sig=*inicio;
      *inicio=temp;
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
    printf("Simbolo: %c\n",temp->sim);
    printf("Probabilidad: %.3f%c \n\n",temp->prob,'%');
    temp=temp->sig;
  }
}

void borrar_simbolo(lista_t **inicio,char sim){
  lista_t *temp;
  temp=*inicio;

  if(temp==NULL){
    printf("No se han ingresado símbolos\n");
    return;
  }
  
  while((temp!=NULL)&&(temp->sim != sim))
    temp=temp->sig;

  if(temp!=NULL){
    if(temp==*inicio){
      *inicio=temp->sig;
      free(temp);
    }
    else if(temp->sig!=NULL){
      temp->ant->sig=temp->sig;
      temp->sig->ant=temp->ant;
      free(temp);
    }
    else if(temp->sig==NULL){
      
      free(temp);
    }
  }
}




