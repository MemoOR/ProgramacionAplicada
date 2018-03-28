//fichero que contiene las funciones para iniciar
//el programa como administrador

//valida la existecia del administrador
int buscar_ad(){
  admin_t *temp;
  temp=inicio_a;
  while(temp!=NULL){
    if(strcmp(temp->nombre,a_nombre)==0){
      return 0;
    }
    temp=temp->sig;
  }
  return 1;
}

//valida que la contraseña del administrador sea correcta
int buscar_cad(){
  admin_t *temp;
  temp=inicio_a;
  while(temp!=NULL){
    if(strcmp(temp->contrasena,a_contra)==0){
      return 0;
    }
    temp=temp->sig;
  }
  return 1;
}

//bloquea a un usuario
void bloquear_usu(){
  user_t *temp;
  temp=inicio_u;
  while(temp!=NULL && strcmp(temp->cuenta,u_cuenta)!=0)
    temp=temp->sig;
  strcpy(temp->estado,"Bloqueado");
  Guardar_usu();
}

//desbloquea un usuario
void desbloquear_usu(){
    user_t *temp;
  temp=inicio_u;
  while(temp!=NULL && strcmp(temp->cuenta,u_cuenta)!=0)
    temp=temp->sig;
  strcpy(temp->estado,"Desbloqueado");
  Guardar_usu();
}

//funciones princicipales de administrador
void administrador(){
  int opcion,validar=1,x=0,y=0;

  printf("\nBienvenido al menú de administrador\n");
  do{
    printf("\nIngresa tu usuario:");
    fgets(a_nombre,98,stdin);
    strtok(a_nombre,"\n");
    validar=buscar_ad();
    y++;
    //valida la existencia del administrador
    if(validar!=0)
      printf("\nUsuario no existente");
    if(y>25){
      //si se ingresan muchos nombres incorrectos se cierra el programa
      printf("\nHas ingresado usuarios incorrectos demasiadas veces\n");
      printf("El programa se cerrará por cuestiones de seguridad\n");
      exit(0);
    }
  }while(validar!=0 && y<=25);

  if(validar==0){
    validar=1;
    do{
      //valida la contraseña del administrador
      printf("\nIngresa tu contraseña:");
      fgets(a_contra,98,stdin);
      strtok(a_contra,"\n");
      validar=buscar_cad();
      x++;
      if(validar!=0 && x<=3)
	printf("\nContraseña incorrecta\n");
      if(x>3){
	printf("\nHas ingresado tres veces la contraseña incorrectamente\n");
	printf("El programa se cerrara por cuestiones de seguridad\n");
	exit(0);
      }
    }while(validar!=0 && x<=3);
  }
  
  printf("Has ingresado correctamente\n");

  //menu principal de administrador
  do{
    printf("[1]Alta de cuenta\n");
    printf("[2]Baja de cuenta\n");
    printf("[3]Bloquear cuenta\n");
    printf("[4]Desbloquear cuenta\n");
    printf("[5]Añadir administrador\n");
    printf("[6]Quitar administrador\n");
    printf("[7]Salir\n");
    do{
      printf("\nOpción: ");
      scanf("%d",&opcion);
      getchar();
    }while(opcion<0 || opcion>8);
    switch(opcion){
    case 1:
      printf("\nEscribe el nombre de usuario:");
      fgets(u_nombre,98,stdin);
      strtok(u_nombre,"\n");
      
      printf("\nEscribe la contraseña:");
      fgets(u_contra,48,stdin);
      strtok(u_contra,"\n");
      
      printf("\nEscribe el número de cuenta:");
      fgets(u_n,18,stdin);
      strtok(u_n,"\n");

      strcpy(u_money,"0.00");
      
      insertar_usuario();
      Guardar_usu();
    break;
    case 2:
      printf("\nEscribe el nombre de usuario:");
      fgets(u_nombre,98,stdin);
      strtok(u_nombre,"\n");
      borrar_usuario();
      break;
    case 3:
      printf("\nEscribe el número de cuenta:");
      fgets(u_cuenta,98,stdin);
      strtok(u_cuenta,"\n");
      bloquear_usu();
      Guardar_usu();
      break;
    case 4:
      printf("\nEscribe el número de cuenta:");
      fgets(u_cuenta,98,stdin);
      strtok(u_cuenta,"\n");
      desbloquear_usu();
      Guardar_usu();
      break;
    case 5:
      printf("\nEscribe el nombre de usuario:");
      fgets(a_nombre,98,stdin);
      strtok(a_nombre,"\n");
      printf("\nEscribe la contraseña:");
      fgets(a_contra,98,stdin);
      strtok(a_contra,"\n");
      insertar_admin();
      Guardar_admin();
      break;
    case 6:
      printf("\nEscribe el nombre de usuario:");
      fgets(a_nombre,98,stdin);
      strtok(a_nombre,"\n");
      borrar_admin();
      break;
    default:
      break;
    }
  }while(opcion!=7);
}
