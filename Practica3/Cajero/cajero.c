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

#include "tables.h"

/*************** VARIABLES GLOBALES ***************/ 
EVENT event;
int state;
char buf[BUFFER];
user_t *inicio_u;
admin_t *inicio_a;

char argumento[L_EVENT_ARGS];
char u_cuenta[L_EVENT_ARGS];

char u_nombre[L_EVENT_ARGS];
char u_contra[L_EVENT_ARGS];
char u_n[L_EVENT_ARGS];
char u_money[50];
char u_blq[L_EVENT_ARGS];

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
void creditos();
void buscar_cuenta(int);
int exist_u(void);
int intentos(void);
int msg_ret(void);
int msg_dep(void);
int msg_cons(void);
int msg_salida(void);
int retiro_exi(void);
int deposito_exi(void);
int msg_saldo(void);

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
int main(int argc, char *argv[])
{
    int actx, auxx, outcome;
    inicio_u=(user_t*)calloc(1,sizeof(user_t));
    inicio_a=(admin_t*)calloc(1,sizeof(admin_t));

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
    char num[L_EVENT_ARGS];
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
}
int intentos(void){
  inten++;
  if(inten<=3)
    return 3;
  else
    return 2;
}
int msg_ret(void){
  printf("\nPara retirar [T:cantidad]\n");
}
int msg_dep(void){
  printf("\nPara depositar [G:cantidad]\n");
}
int msg_cons(void){
  printf("\nConsulta de saldo [A]\n");
}
int msg_salida(void){
  Guardar_usu();
  Guardar_admin();
  printf("\nHas cerrado la cuenta con éxito\n\n");
  usleep(1999999);
  CLS;
  printf("Bienvenido al cajero automático\n\n");
  printf("Ingresa tu número de cuenta [U:número]\n");
    
}
int retiro_exi(void){
  int op=1;
  buscar_cuenta(op);
}
int deposito_exi(void){
  int op=2;
  buscar_cuenta(op);
}
int msg_saldo(void){
  printf("\nTu saldo actual es de: ");
}
int msg_nexist(void){
  printf("\nEl número de cuenta ingresado no existe\n");
}
int msg_contra(void){
  printf("\nIngresa tu contraseña [P:contraseña]:\n");
}
int msg_bloq(void){
  printf("\nHas ingresado demasiadas veces una contraseña incorrecta\n");
  printf("tu cuenta ha sido bloqueada por cuestiones de seguridad.\n");
  printf("Para desbloquearla contacta con un administrador\n");
}
int val_contra(void){
  char op;
  validar_contrasena(&op);
  if(op=='s')
    return 5;
  if(op=='n')
    return 4;
}
int msg_c_incorr(void){
  printf("\nContraseña incorrecta. Ingresala de nuevo\n");
}
int val_bloqueo(void){
  char op;
  validar_bloqueo(&op);
  if(op=='s')
    return 6;
  if(op=='n')
    return 7;
}
int msg_bloqueado(void){
  printf("\nEsta cuenta esta bloqueada\n");
}
int msg_acceso(void){
  printf("\nAcceso correcto.[R,D,C,S]\n");
}

int nul(void){
}//nul

void leer_admin(){
  a_admin=fopen("Administrador.txt","r");
  if(a_admin==NULL)
    return;
      
  //if(inicio!=NULL){
  while (!feof(a_admin)) {
    fscanf(a_admin,"%s %s\n",a_nombre,a_contra);
    printf("%s %s\n",a_nombre,a_contra);
    insertar_admin();
  }
  fclose(a_admin);
  return;
}

void leer_usu(){
  a_user=fopen("Usuario.txt","r");
  if(a_user==NULL)
    return;
      
  //if(inicio!=NULL){
  while (!feof(a_user)) {
    fscanf(a_user,"%s\n%s\n%s\n%s\n%s\n\n",u_nombre,u_contra,u_n,u_money,u_blq);
    printf("%s %s %s %s %s\n",u_nombre,u_contra,u_n,u_money,u_blq);
    insertar_usuario();
  }
  fclose(a_user);
  return;
}
