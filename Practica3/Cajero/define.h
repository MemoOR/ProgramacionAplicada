/****************************************************************
 *								*
 * Archivo:	define.h					*
 * Descripcion: Archivo de encabezado para maquina de estados	*
 *		Aqui se definen todos los tipos de datos y 	*
 *		constantes que se utilizan en el programa	*
 *								*
 ****************************************************************/

/******************* CONSTANTES *******************
 * En esta seccion se declaran todas las 	  *
 * las constantes que se necesiten en el programa *
 **************************************************/ 
#define BUFFER        128
#define L_EVENT_ARGS  21
#define CLS system("clear")

/****************** ESTRUCTURAS *****************
 * En esta seccion se declaran todas las	*
 * estructuras que se necesiten en el programa	*
 ************************************************/ 

// Este tipo de datos se utiliza para leer la informacion
// que teclea el usuario 
struct event_s
{
    int etype;
    char args[L_EVENT_ARGS];
};
typedef struct event_s EVENT;

// Este tipo de datos se utiliza para implementar 
// la tabla auxiliar
struct aux_table_s 
{
    int (*action)();
    int moreacts;
    int nextstate;
};
typedef struct aux_table_s AUX_TAB;

// Este tipo de datos se utiliza para implementar
// la tabla de accion
struct action_tab_s 
{
    int event;
    int (*action)();
    int moreacts;
    int nextstate;
};
typedef struct action_tab_s ACTION_TAB;

// Este tipo de datos se utiliza para implementar
// la tabla de estados
struct state_tab_s 
{
    int state;
    int start;
    int end;
};
typedef struct state_tab_s STATE_TAB;

//estructura de la lista de datos del usuario
typedef struct user_t{
  char nombre[100];
  char contrasena[50];
  char cuenta[20];
  char money[50];
  char movimiento[20];
  char estado[20];

  struct user_t *sig,*ant;
}user_t;

//estructura de datos de administrador
typedef struct admin_t{
  char nombre[100];
  char contrasena[100];
  
  struct admin_t *sig,*ant;
}admin_t;

/********************* GLOBALES ***********************
 * En esta seccion se pueden declarar todas	      *
 * variables globales que se necesiten en el programa *
 ******************************************************/ 
FILE *a_admin,*a_user,*a_moves;

/********************* EVENTOS *******************
 * En esta seccion se declarar como constantes	 *
 * los eventos (entradas) que recibe el programa *
 *************************************************/ 
#define ENTRADA_U   0
#define ENTRADA_P   1
#define ENTRADA_R   2
#define ENTRADA_D   3
#define ENTRADA_C   4
#define ENTRADA_S   5
#define ENTRADA_T   6
#define ENTRADA_G   7
#define ENTRADA_A   8
#define AST  -1

/********************* ESTADOS ******************
 * En esta seccion se declarar como constantes	*
 * los estados de que consta el programa 	*
 ************************************************/ 
#define INICIO      0
#define CONTRASENA  1
#define ESPERA_U    2     
#define RETIRO      3
#define DEPOSITO    4
#define CONSULTA    5


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
