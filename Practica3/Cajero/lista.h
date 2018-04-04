//Este fichero tendrá las funciones para trabajar con la lista
//y el archivo que almavenará los números bloqueados

//Guarda en un archivo los datos de los usuarios
void Guardar_usu(){
  user_t *temp;
  temp=inicio_u;

  char nombre[] ={"Usuario.txt"};
  a_user=fopen(nombre,"r");

  if(a_user==NULL){
    a_user=fopen(nombre,"wt");
    while(temp!=NULL){
      fprintf(a_user,"%s %s %s %s %s\n",temp->nombre,temp->contrasena,temp->cuenta,temp->money,temp->estado);
      temp=temp->sig;
    }
  }else{
    fclose(a_user);
    a_user=fopen(nombre,"wt");
    while(temp!=NULL){
      fprintf(a_user,"%s\n%s\n%s\n%s\n%s\n\n",temp->nombre,temp->contrasena,temp->cuenta,temp->money,temp->estado);
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

//inserta usuarios
void insertar_usuario(){
  user_t *temp,*ant,*pos;

  temp=(user_t* ) calloc(1,sizeof(user_t));

  strcpy(temp->nombre,u_nombre);
  strcpy(temp->contrasena,u_contra);
  strcpy(temp->cuenta,u_n);
  strcpy(temp->money,u_money);
  strcpy(temp->estado,u_estado);
  
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

//inserta administradores
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

//inserta los movimientos del usuario
void insertar_mov(){
  moves_t *temp,*ant,*pos;

  temp=(moves_t* ) calloc(1,sizeof(moves_t));

  strcpy(temp->accion,m_accion);
  strcpy(temp->monto,m_money);
  strcpy(temp->fecha,m_date);
  strcpy(temp->hora,m_hora);
  
  if(inicio_m==NULL){
    temp->sig=inicio_m;
    inicio_m=temp;
    inicio_m->ant=NULL;
  }else{
    pos=inicio_m;
    while(pos!=NULL && strcmp(pos->fecha,temp->fecha)<0){
      pos=pos->sig;
    }

    if(pos!=inicio_m){
      ant=inicio_m;
      while(ant->sig!=pos){
	ant=ant->sig;
      }
      ant->sig=temp;
      temp->sig=pos;
      temp->ant=ant;
    }
    else{
      temp->sig=inicio_m;
      inicio_m=temp;
      inicio_m->ant=NULL;
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
  while(temp!=NULL){
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
  while(temp!=NULL){
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
  
  while(temp!=NULL){
    if(strcmp(temp->cuenta,u_cuenta)==0){
      if(strcmp(temp->estado,"Bloqueado")==0){
	*op='s';
	return;
      }
    }
    temp=temp->sig;
  }
}

//imprime el saldo actual del usuario
void consultar(){
  user_t *temp;
  temp=inicio_u;
  
  printf("\n");
  while(temp!=NULL && strcmp(temp->cuenta,u_cuenta)!=0){
      temp=temp->sig;
  }
  printf("\nTu saldo actual es: %s\n",temp->money);
  printf("\n");
}

//elimina aun usuariode la base de datos
void borrar_usuario(){
  user_t *temp;
  temp=inicio_u;

  while((temp!=NULL)&&(strcmp(temp->nombre,u_nombre)!=0))
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
  Guardar_usu();
}

//elimina un administrador de la base de datos
void borrar_admin(){
  admin_t *temp;
  temp=inicio_a;

  if(temp==NULL){
    printf("\nNo hay datos que borrar\n");
    return;
  }
  
  while((temp!=NULL)&&(strcmp(temp->nombre,a_nombre)!=0))
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
  Guardar_admin();
}

//valida el deposito o retiro del usuario
void buscar_cuenta(int op){
  user_t *temp;
  temp=inicio_u;
  //busca el usuario actual
  while(temp!=NULL && strcmp(temp->cuenta,u_cuenta)!=0){
    temp=temp->sig;
  }

  //convierte strings a floats para poder
  //utilizar operaciones
  const char s[2] = "-";
  char *token,*token1;
  float arg,u_M,resultado;
  token = strtok(argumento, s);
  sscanf(token,"%f",&arg);
  
  token1 = strtok(temp->money, s);
  sscanf(token1,"%f",&u_M);
  
  if(op==1 && arg>u_M)
    printf("\nNo puedes retirar mas de lo que tienes en tu cuenta\n");
  else if(op==1)
    resultado=u_M-arg;  
  if(op==2)
    resultado=u_M+arg;

  printf("\nTu saldo final es de: %.2f\n\n",resultado);

  //regresa el float al strig oara guardarlo en el archivo
  sprintf(temp->money,"%.2f",resultado);

  Guardar_usu();
}

//agrega nuevos movimientos del usuario la lista y los guarda
//en un archivo con el numero de cuenta del usuario
void agregar_mov(int op){ 
  char archivo[50];
  //genera el nomnre del archivo donde se guardan
  //los movimientos del usuario
  strcpy(archivo,"Movimientos_");
  strcat(archivo,u_cuenta);
  strcat(archivo,".txt");

  char accion[20];

  //accion del usuario
  if(op==1){
    strcpy(accion,"Retiro");
  }
  if(op==2){
    strcpy(accion,"Depósito");
  }

  //obtiene la fecha y hora actuales
  time_t tiempo = time(0);
  struct tm *tlocal = localtime(&tiempo);
  char output[128],output1[128];
  strftime(output,128,"%d/%m/%y",tlocal);
  strftime(output1,128,"%H:%M:%S",tlocal);

  strcpy(m_money,argumento);
  strcpy(m_accion,accion);
  strcpy(m_date,output);
  strcpy(m_hora,output1);

  //inserta los movimientos en la lista
  insertar_mov();
  
  moves_t *temp;
  temp=inicio_m;

  a_moves=fopen(archivo,"r");

  //guarda los movimientos en el archivo
  if(a_moves==NULL){
    a_moves=fopen(archivo,"wt");
    while(temp!=NULL){ 
      fprintf(a_moves,"%s %s %s %s\n",temp->accion,temp->monto,temp->fecha,temp->hora);
      temp=temp->sig;
    }
  }else{
    fclose(a_moves);
    a_moves=fopen(archivo,"wt");
    while(temp!=NULL){
      fprintf(a_moves,"%s %s %s %s\n",temp->accion,temp->monto,temp->fecha,temp->hora);
      temp=temp->sig;
    }
  }
  fclose(a_moves);
}


