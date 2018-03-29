/****************************************************************
 *								*
 * Archivo:	cajero.c					*
 * Descripcion: Codigo Fuente para implementar el programa	*
 *		de maquina de estados.			 	*
 *								*
 ****************************************************************/

/*************** ARCHIVOS DE INCLUSION ***************/ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>//libreria para stdin
#include <termios.h>
#include<time.h>

#include "tables.h"

/*************** VARIABLES GLOBALES ***************/ 
EVENT event;
int state;
char buf[BUFFER];

user_t *inicio_u;
admin_t *inicio_a;
moves_t *inicio_m;

char argumento[L_EVENT_ARGS];
char u_cuenta[L_EVENT_ARGS];

char u_nombre[L_EVENT_ARGS];
char u_contra[L_EVENT_ARGS];
char u_n[L_EVENT_ARGS];
char u_money[128];
char u_estado[L_EVENT_ARGS];

char m_accion[20];
char m_money[128];
char m_date[200];

char a_nombre[L_EVENT_ARGS];
char a_contra[L_EVENT_ARGS];

int inten=0;

#include"lista.h"
#include"administrador.h"

/*************** PROTOTIPOS DE FUNCION ***************/
void initialise(void);
void getevent(void);

void leer_admin();
void leer_usu();
void leer_mov();
void creditos();
void buscar_cuenta(int);
int exist_u(void);
int intentos(void);
int msg_ret(void);
int msg_dep(void);
int msg_cons(void);
int msg_cambio(void);
int msg_salida(void);
int retiro_exi(void);
int deposito_exi(void);
int msg_saldo(void);
int msg_mov(void);
int cambio(void);

int msg_nexist(void);
int msg_contra(void);
int msg_bloq(void);
int val_contra(void);
int msg_acceso(void);
int msg_c_incorr(void);
int val_bloqueo(void);
int msg_bloqueado(void);

int nul(void);

/*************** FUNCION PRINCIPAL ***************/ 
int main(int argc, char *argv[]){
    int actx, auxx, outcome;

    inicio_u=(user_t*)calloc(1,sizeof(user_t));
    inicio_a=(admin_t*)calloc(1,sizeof(admin_t));
    inicio_m=(moves_t*)calloc(1,sizeof(moves_t));

    inicio_u=NULL;
    inicio_a=NULL;
    inicio_m=NULL;

    creditos();
    
    initialise();

    //CLS;

    if(argc>1 && strcmp(argv[1],"-c")==0){
      administrador();
      return 0;
    }
    
    printf("\nBienvenido al cajero automático\n\n");
    printf("Ingresa tu número de cuenta [U:número]\n");
    
    while (1) {    /* loop infinito para la MFE */
        getevent();

        for ((actx = state_table[state].start);(action_table[actx].event != event.etype) && (actx < state_table[state].end);actx++)
            ;
        outcome = (*(action_table[actx].action))();
            if(action_table[actx].moreacts == -1)
                state = action_table[actx].nextstate;
            else {
                auxx = action_table[actx].moreacts + outcome;
                while (auxx != -1){
                    outcome = (*(aux_table[auxx].action))();
                    if (aux_table[auxx].moreacts == -1 ){
                        state = aux_table[auxx].nextstate;
                        auxx = -1;
                    }
                    else
                        auxx = aux_table[auxx].moreacts + outcome;
		}
        }
    } /* while(1) */
}

void initialise(void){
    state = 0;
    leer_admin();
    leer_usu();    
}

void getevent(void){
    char *ptmp;
    ptmp = &buf[2];
    
#ifdef DEBUG
    printf("wait event \n");
#endif

    fgets(buf,128,stdin);

    switch (buf[0]){
    case 'U':
      event.etype=ENTRADA_U;
      strcpy(event.args,ptmp);   // Esta instruccion se debera hacer en caso de que ademas de la letra
                                 // para indicar la entrada, se pase informacion adicional, por ejemplo
                                 // C:info_adicional
      strcpy(argumento,event.args);
      strtok(argumento,"\n");
      strcpy(u_cuenta,argumento);
#ifdef DEBUG
      printf("---> %s \n",event.args);
#endif      
      break;
    case 'P':
      event.etype=ENTRADA_P;
      strcpy(event.args,ptmp);   // Esta instruccion se debera hacer en caso de que ademas de la letra
                                 // para indicar la entrada, se pase informacion adicional, por ejemplo
                                 // C:info_adicional
      strcpy(argumento,event.args);
      strtok(argumento,"\n");
#ifdef DEBUG
      printf("---> %s \n",event.args);
#endif      
      break;
    case 'R':
      event.etype=ENTRADA_R;
      break;
    case 'D':
      event.etype=ENTRADA_D;
      break;
    case 'C':
      event.etype=ENTRADA_C;
      break;
    case 'W':
      event.etype=ENTRADA_W;
      break;
    case 'S':
      event.etype=ENTRADA_S;
      break;
    case 'T':
      event.etype=ENTRADA_T;
      strcpy(event.args,ptmp);   // Esta instruccion se debera hacer en caso de que ademas de la letra
                                 // para indicar la entrada, se pase informacion adicional, por ejemplo
                                 // C:info_adicional
      strcpy(argumento,event.args);
      strtok(argumento,"\n");
#ifdef DEBUG
      printf("---> %s \n",event.args);
#endif      
      break;
    case 'G':
      event.etype=ENTRADA_G;
      strcpy(event.args,ptmp);   // Esta instruccion se debera hacer en caso de que ademas de la letra
                                 // para indicar la entrada, se pase informacion adicional, por ejemplo
                                 // C:info_adicional
      strcpy(argumento,event.args);
      strtok(argumento,"\n");
#ifdef DEBUG
      printf("---> %s \n",event.args);
#endif      
      break; 
    case 'A':
      event.etype=ENTRADA_A;
      break;
    case 'M':
      event.etype=ENTRADA_M;
      break;
    case 'X':
      event.etype=ENTRADA_X;
      strcpy(event.args,ptmp);   // Esta instruccion se debera hacer en caso de que ademas de la letra
                                 // para indicar la entrada, se pase informacion adicional, por ejemplo
                                 // C:info_adicional
      strcpy(argumento,event.args);
      strtok(argumento,"\n");
#ifdef DEBUG
      printf("---> %s \n",event.args);
#endif      
      break;
    default:
      event.etype=AST;
      break;
    }//switch
}// getevent
 

/* FUNCIONES DE IMPLEMENTACION */
int exist_u(void){
  char op;
  
  validar_usuario(&op);
  if(op=='s')
    return 1;
  if(op=='n')
    return 0;
}//valida existencia del usuario

int intentos(void){
  inten++;
  if(inten<=3)
    return 3;
  else
    inten=0;
    return 2;
}//valida que los intentos de ingresar la contraeña
 //sean menores a 3

int msg_ret(void){
  printf("\nPara retirar [T:cantidad]\n");
}//mensaje de ingreso al estado de retiro

int msg_dep(void){
  printf("\nPara depositar [G:cantidad]\n");
}//mensaje de ingreso al estado de depósito


int msg_cons(void){
  printf("\nConsulta de saldo o movimientos [A, M]\n");
}//mensaje de ingreso al estado de consulta


int msg_cambio(void){
  printf("\nCambio de contraseña [X]\n");
}//mensaje de ingreso al estado de cambio de contraseña

int msg_salida(void){
  Guardar_usu();
  Guardar_admin();
  printf("\nHas cerrado la cuenta con éxito\n\n");
  usleep(1999999);
  CLS;
  printf("Bienvenido al cajero automático\n\n");
  printf("Ingresa tu número de cuenta [U:número]\n");
}//mensaje de salida de la cuenta

int retiro_exi(void){
  int op=1;
  buscar_cuenta(op);
  agregar_mov(op);
}//retirar dinero

int deposito_exi(void){
  int op=2;
  buscar_cuenta(op);
  agregar_mov(op);
}//depositar dinero

int msg_saldo(void){
  consultar();
}//consultar saldo

int msg_mov(void){
  char archivo[50];
  strcpy(archivo,"Movimientos_");
  strcat(archivo,u_cuenta);
  strcat(archivo,".txt");

  moves_t *temp;
  temp=inicio_m;
 
  if(temp==NULL){
    printf("\nNo existen movimientos\n");
  }
  while(temp!=NULL){
    printf("%s: $%s %s\n",temp->accion,temp->monto,temp->fecha);
    temp=temp->sig;
  }
 
  printf("\n");
}//consultar movimientos

int cambio(void){
  user_t *temp;
  temp=inicio_u;
  while(temp->sig!=NULL && strcmp(temp->cuenta,u_cuenta)!=0)
    temp=temp->sig;
  strcpy(temp->contrasena,argumento);
  printf("\nHas cambiado la contraseña con éxito\n");
  Guardar_usu();
}//cambiar contraseña

int msg_nexist(void){
  printf("\nEl número de cuenta ingresado no existe\n");
}//mensaje de inexistecia de usuario

int msg_contra(void){
  printf("\nIngresa tu contraseña [P:contraseña]:\n");
}//mensaje de ingreso al estado de contraseña

int msg_bloq(void){
  printf("\nHas ingresado demasiadas veces una contraseña incorrecta\n");
  printf("tu cuenta ha sido bloqueada por cuestiones de seguridad.\n");
  printf("Para desbloquearla contacta con un administrador\n");
  inten=0;
  bloquear_usu();
}//mensaje de cuenta bloqueada

int val_contra(void){
  char op;
  validar_contrasena(&op);
  if(op=='s')
    return 5;
  if(op=='n')
    return 4;
}//valida que la contraseña sea correcta

int msg_c_incorr(void){
  printf("\nContraseña incorrecta. Ingresala de nuevo\n");
}//mensaje de contraseña incorrecta

int val_bloqueo(void){
  char op;
  validar_bloqueo(&op);
  if(op=='s')
    return 6;
  if(op=='n')
    return 7;
}//valida que el usuario no este bloqueado

int msg_bloqueado(void){
  printf("\nEsta cuenta esta bloqueada\n");
}//mensaje de cuenta boqueada

int msg_acceso(void){
  printf("\nAcceso correcto.[R,D,C,W,S]\n");
  leer_mov();
}//mensaje de acceso al estado de espera de usuario

int nul(void){
}//nul

//lee administradores existentes
void leer_admin(){
  a_admin=fopen("Administrador.txt","rt");
  if(a_admin==NULL){
    fclose(a_admin);
    return;
  }
    
  //if(inicio!=NULL){
  while (!feof(a_admin)) {
    fscanf(a_admin,"%s %s\n",a_nombre,a_contra);
    insertar_admin();
  }
  fclose(a_admin);
  return;
}

//lee usuarios existentes
void leer_usu(){
  a_user=fopen("Usuario.txt","rt");
  if(a_user==NULL){
    fclose(a_user);
    return;
  }
      
  while (!feof(a_user)){
    fscanf(a_user,"%s\n%s\n%s\n%s\n%s\n\n",u_nombre,u_contra,u_n,u_money,u_estado);
    insertar_usuario();
  }
  fclose(a_user);
  return;
}

//lee los movimientos del usuario
void leer_mov(){
  char archivo[50];
  strcpy(archivo,"Movimientos_");
  strcat(archivo,u_cuenta);
  strcat(archivo,".txt");
  
  a_moves=fopen(archivo,"rt");
  
  if(a_moves==NULL){
    a_moves=fopen(archivo,"wt");
    return;
  }
  
  while (!feof(a_moves)){
    fscanf(a_moves,"%s %s %s\n",m_accion,m_money,m_date);
    insertar_mov();
  }
  fclose(a_moves);
  return;
}
