//Este fichero tendrá las funciones para trabajar con la lista
//y el archivo que almavenará los números bloqueados

//inserta el número a la lista de bloqueo
void insertar_usuario(){
  user_t *temp,*ant,*pos;

  temp=(user_t* ) calloc(1,sizeof(user_t));

  strcpy(temp->nombre,u_nombre);
  strcpy(temp->contrasena,u_contra);
  strcpy(temp->cuenta,u_n);
  temp->money=0;
  strcpy(temp->estado,"Desbloqueado");
  
  if(inicio_u==NULL){
    temp->sig=inicio_u;
    inicio_u=temp;
    inicio_u->ant=NULL;
  }else{
    pos=inicio_u;
    while(pos!=NULL && strcmp(pos->nombre,temp->nombre)<0){
      pos=pos->sig;
    }

    if(pos!=inicio_u){
      ant=inicio_u;
      while(ant->sig!=pos){
	ant=ant->sig;
      }
      ant->sig=temp;
      temp->sig=pos;
      temp->ant=ant;
    }
    else{
      temp->sig=inicio_u;
      inicio_u=temp;
      inicio_u->ant=NULL;
    }
  }
}

//inserta el número a la lista de bloqueo
void insertar_admin(){
  admin_t *temp,*ant,*pos;

  temp=(admin_t* ) calloc(1,sizeof(admin_t));

  strcpy(temp->nombre,a_nombre);
  strcpy(temp->contrasena,a_contra);
  
  if(inicio_a==NULL){
    temp->sig=inicio_a;
    inicio_a=temp;
    inicio_a->ant=NULL;
  }else{
    pos=inicio_a;
    while(pos!=NULL && strcmp(pos->nombre,temp->nombre)<0){
      pos=pos->sig;
    }

    if(pos!=inicio_a){
      ant=inicio_a;
      while(ant->sig!=pos){
	ant=ant->sig;
      }
      ant->sig=temp;
      temp->sig=pos;
      temp->ant=ant;
    }
    else{
      temp->sig=inicio_a;
      inicio_a=temp;
      inicio_a->ant=NULL;
    }
  }
}

//valida que el número ingresado no este bloqueado
void validar_usuario(char *op){
  user_t *temp;
  temp=inicio_u;
  *op='n';
  if(temp==NULL){
    return;
  }
  while(temp->sig!=NULL){
    if(strcmp(temp->cuenta,argumento)==0){
      *op='s';
      return;
    }
    temp=temp->sig;
  }
}

//valida que el número ingresado no este bloqueado
void validar_contrasena(char *op){
  user_t *temp;
  temp=inicio_u;
  *op='n';
  if(temp==NULL){
    return;
  }
  while(temp->sig!=NULL){
    if(strcmp(temp->contrasena,argumento)==0){
      *op='s';
      return;
    }
    temp=temp->sig;
  }
}

//valida que el número ingresado no este bloqueado
void validar_bloqueo(char *op){
  user_t *temp;
  temp=inicio_u;
  *op='n';
  if(temp==NULL){
    return;
  }
  while(temp->sig!=NULL){
    if(strcmp(temp->estado,"Bloqueado")==0){
      *op='s';
      return;
    }
    temp=temp->sig;
  }
}

void consultar(){
  user_t *temp;
  temp=inicio_u;
  
  printf("\n");
  while(temp->sig!=NULL && strcmp(temp->cuenta,u_cuenta)!=0){
    temp=temp->sig;
  }
  printf("%f\n",temp->money);
  printf("\n");
}

void borrar_usuario(){
  user_t *temp;
  temp=inicio_u;

  if(temp==NULL){
    printf("\nNo se han ingresado símbolos\n\n");
    return;
  }

  while((temp!=NULL)&&(strcmp(temp->nombre,argumento)!=0))
    temp=temp->sig;

  if(temp!=NULL){
    if(temp==inicio_u){
      inicio_u=temp->sig;
      free(temp);
    }else if(temp->sig==NULL){
      temp->ant->sig=NULL;
      free(temp);
    }else{
      temp->ant->sig=temp->sig;
      temp->sig->ant=temp->ant;
      free(temp);
    }
  }
}

void borrar_admin(){
  admin_t *temp;
  temp=inicio_a;

  if(temp==NULL){
    printf("\nNo se han ingresado símbolos\n\n");
    return;
  }

  while((temp!=NULL)&&(strcmp(temp->nombre,argumento)!=0))
    temp=temp->sig;

  if(temp!=NULL){
    if(temp==inicio_a){
      inicio_a=temp->sig;
      free(temp);
    }else if(temp->sig==NULL){
      temp->ant->sig=NULL;
      free(temp);
    }else{
      temp->ant->sig=temp->sig;
      temp->sig->ant=temp->ant;
      free(temp);
    }
  }
}

//Guarda en un archivo los datos de los usuarios
void Guardar_usu(){
  user_t *temp;
  temp=inicio_u;

  char nombre[] ={"Usuario.txt"};
  a_user=fopen(nombre,"r");

  if(a_user==NULL){
    a_user=fopen(nombre,"wt");
    while(temp!=NULL){
      fprintf(a_user,"%s %s %s %.2f %s\n",temp->nombre,temp->contrasena,temp->cuenta,temp->money,temp->estado);
      printf("%s %s %s %.2f %s\n",temp->nombre,temp->contrasena,temp->cuenta,temp->money,temp->estado);
      temp=temp->sig;
    }
  }else{
    fclose(a_user);
    a_user=fopen(nombre,"wt");
    while(temp!=NULL){
      fprintf(a_user,"%s\n%s\n%s\n%.2f\n%s\n\n",temp->nombre,temp->contrasena,temp->cuenta,temp->money,temp->estado);
      printf("%s %s %s %.2f %s\n",temp->nombre,temp->contrasena,temp->cuenta,temp->money,temp->estado);
      temp=temp->sig;
    }
  }
  fclose(a_user);
}

//funcion para guardar en archivo los datos de administradores
void Guardar_admin(){
  admin_t *temp;
  temp=inicio_a;

  char nombre[] ={"Administrador.txt"};
  a_admin=fopen(nombre,"r");

  if(a_admin==NULL){
    a_admin=fopen(nombre,"wt");
    while(temp!=NULL){
      fprintf(a_admin,"%s %s\n",temp->nombre,temp->contrasena);
      temp=temp->sig;
    }
  }else{
    fclose(a_admin);
    a_admin=fopen(nombre,"wt");
    while(temp!=NULL){
      fprintf(a_admin,"%s %s\n",temp->nombre,temp->contrasena);
      temp=temp->sig;
    }
  }
  fclose(a_admin);
}
