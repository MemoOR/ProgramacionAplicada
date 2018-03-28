/************************************************************************
 *									*
 * Archivo:	tables.h						*
 * Descripcion: Tablas para la maquina de estados y funciones externas	*
 *		Aqui se definen todos las tablas que se utilizan	*
 *		en el programa						*
 *									*
 ************************************************************************/

/*************** ARCHIVOS DE INCLUSION ***************/ 
#include "define.h"
#include <stdio.h>


/*************** FUNCIONES EXTERNAS *********************
 * En esta seccion se declaran los encabezados de 	*
 * todas las funciones que se utilizan en las     	*
 * tablas del programa. Todas las funciones deben 	*
 * ser de tipo entero y no deben recibir parametros	*
 ********************************************************/ 
extern int exist_u(void);
extern int intentos(void);
extern int msg_ret(void);
extern int msg_dep(void);
extern int msg_cons(void);
extern int msg_cambio(void);
extern int msg_salida(void);
extern int retiro_exi(void);
extern int deposito_exi(void);
extern int msg_saldo(void);
extern int msg_mov(void);
extern int cambio(void);

extern int msg_nexist(void);
extern int msg_contra(void);
extern int msg_bloq(void);
extern int val_contra(void);
extern int msg_acceso(void);
extern int msg_c_incorr(void);
extern int val_bloqueo(void);
extern int msg_bloqueado(void);

extern int nul(void);

/******************** TABLAS ********************
 * En esta seccion se declaran las tablas	*
 * que se van a usar en el programa		*
 ************************************************/ 
 
/*************** TABLA DE ACCION ***************/  
ACTION_TAB action_table[]={
     /*etype    accion/funcion   bandera       sigEdo. */    
    { ENTRADA_U,  exist_u,  	  0,    	AST},
    { AST,        nul,  	  AST,    	INICIO},
    { ENTRADA_P,  intentos,  	  0,    	AST},
    { AST,        nul,  	  AST,    	CONTRASENA},
    { ENTRADA_R,  msg_ret,  	  AST,    	RETIRO},
    { ENTRADA_D,  msg_dep,  	  AST,    	DEPOSITO},
    { ENTRADA_C,  msg_cons,  	  AST,    	CONSULTA},
    { ENTRADA_W,  msg_cambio,  	  AST,    	CAMBIO},
    { ENTRADA_S,  msg_salida,  	  AST,    	INICIO},
    { AST,        nul,  	  AST,    	ESPERA_U},
    { ENTRADA_T,  retiro_exi,  	  AST,    	ESPERA_U},
    { AST ,       nul,  	  AST,    	ESPERA_U},
    { ENTRADA_G,  deposito_exi,   AST,    	ESPERA_U},
    { AST,        nul,  	  AST,    	ESPERA_U},
    { ENTRADA_A,  msg_saldo,  	  AST,    	ESPERA_U},
    { ENTRADA_M,  msg_mov,        AST,    	ESPERA_U},
    { AST,        nul,  	  AST,    	ESPERA_U},
    { ENTRADA_X,  cambio,  	  AST,    	ESPERA_U},
    { AST,        msg_saldo,  	  AST,    	ESPERA_U},
};

/*************** TABLA AUXILIAR ***************/  
    AUX_TAB aux_table[]={        
/*    accion       bandera        sigEdo */
    { msg_nexist,     AST,         INICIO},
    { msg_contra,     AST,         CONTRASENA},
    { msg_bloq,       AST,         INICIO},
    { val_contra,      0,          AST},
    { msg_c_incorr,   AST,         CONTRASENA},
    { val_bloqueo,     0,          ESPERA_U},
    { msg_bloqueado,  AST,         ESPERA_U},
    { msg_acceso,     AST,         ESPERA_U},
    };

/*************** TABLA DE ESTADOS ***************/  
STATE_TAB state_table[]={
   /*estado      inicio   fin */
    {INICIO,       0,       1},
    {CONTRASENA,   2,       3},
    {ESPERA_U,     4,       9},
    {RETIRO,       10,      11},
    {DEPOSITO,     12,      13},
    {CONSULTA,     14,      16},
    {CAMBIO,       17,      18},
};
