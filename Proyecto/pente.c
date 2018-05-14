/* @file pente.c
*  @brief Este programa se encarga de crear la parte 
*  gráfica de el juego de pente
*  @author Guillermo Ortega y Mateo Larralde
*  @date 14/05/2018
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<gtk/gtk.h>

//estructura de jugador
typedef struct _node{
  char nombre[20];
  GtkWidget *entry;
  int fila4;
  int comidas;
}Jug;

//estructura de turnos
typedef struct _node3{
  struct _node3 *sig;
  int X;
  int Y;
}Jugadas;


//estructura de datos generales, esta es la que se pasa a las funciones y tiene apuntadores a las otras estructuras.
typedef struct _node2{
  GtkWidget *entry,*entry2;
  GtkWidget *ventana;
  GtkWidget *label1,*label2,*labelt;
  GtkWidget *buttons[20][20];
  Jugadas *turnos_l;
  int X1;
  int Y1;
  int turno;
  Jug *Jugador1;
  Jug *Jugador2;
  char archivo[20];
  char tablero[20][20];
  int ganador;
}Lista;

//funciones de graficos//
GtkWidget *AddButton(GtkWidget *theBox, const gchar *buttonText,gpointer CallBackFunction, Lista *EntryBox);
GtkWidget *AddButton1(GtkWidget *window,GtkWidget *theBox,const gchar *buttonText, gpointer CallBackFunction,Lista *EntryBox);
GtkWidget *Addlabel(GtkWidget *theBox, const gchar *buttonText);
static gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer *data);
void StopTheApp(GtkWidget *window, gpointer data);
void Nuevo(GtkWidget *window, gpointer data);
void Cargar(GtkWidget *window, gpointer data);
void NOMBRES(GtkWidget *window, gpointer data);
void quick_message (gchar *message, GtkWidget *parent);
void close_window(GtkWidget *window, gpointer data);
GtkWidget *create_pad();
//funciones de graficos//

//funciones de funcionamiento//
void CARGAR(GtkWidget *window, gpointer data);
void Cargarjugs(GtkWidget *window, gpointer data);
void Guardar(GtkWidget *window, gpointer data);
void command(int y);
void callback(GtkWidget *widget, gpointer data);
void ComeFichas(GtkWidget *widget, gpointer data);
void FilasDe4(GtkWidget *widget, gpointer data);
void Ganador(GtkWidget *window, gpointer data);
void GUARDAR(GtkWidget *window, gpointer data);
void obtener_coordenada(GtkWidget *button, gpointer data);
void insertar_turno(Jugadas **inicio,int x,int y);
//funciones de funcionamiento//


#include "funcion.h"

/**
*  Esta función recibe un caracter en el primer argumento y si
*  este es una letra minuscula lo convierte a mayuscula y regresa 
*  elnuevo valor en el segundo argumento.
*  Regresa un 1 si pudo convertir a mayuscula el caracter
*  y 0 si no pudo hacerlo.
*  @author Iggy Pop
*  @param chrData     El caracter a convertir (minuscula a mayuscula)
*  @param *may        El caracter convertido en mayuscula
*  @return int
*/
gint main ( gint argc, gchar *argv[]){

  GtkWidget *window1;
  GtkWidget *button;
  GtkWidget *box,*label,*verticalbox;
  Lista *Inicio;
  Jug Jugador1,Jugador2;
  
  Inicio=(Lista*)malloc(sizeof(Lista));
 


  /*
  Jugador1=(Jug*)malloc(sizeof(Jug));
  Jugador2=(Jug*)malloc(sizeof(Jug));
  */
  
  strcpy(Jugador1.nombre, "\0");
  strcpy(Jugador2.nombre, "\0");
  
  Inicio->turnos_l=NULL;
  Jugador1.comidas=0;
  Jugador1.fila4=0;
  Jugador2.comidas=0;
  Jugador2.fila4=0;
  
  strcpy(Inicio->archivo, "\0");
  Inicio->Jugador1=&Jugador1;
  Inicio->Jugador2=&Jugador2;
  Inicio->turno=3;
  Inicio->X1=-1;
  Inicio->Y1=-1;


  //Ventana de nuevo juego o cargar  
  gtk_init(&argc, &argv);

  window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window1),320,200);
  gtk_container_border_width(GTK_CONTAINER(window1),25);

  verticalbox = gtk_vbox_new(TRUE,5);
  Inicio->ventana = window1;
  label = gtk_label_new ("¡Bienvenidos al juego de Pente!");
  gtk_box_pack_start(GTK_BOX(verticalbox),label,TRUE,TRUE,5);
  
  box = gtk_hbox_new(TRUE,30);
  button = AddButton1(window1,box,"Juego Nuevo",Nuevo,Inicio);
  button = AddButton1(window1,box,"Cargar",Cargar,Inicio);
  gtk_box_pack_start(GTK_BOX(verticalbox),box,TRUE,TRUE,5);

  gtk_container_add(GTK_CONTAINER(window1),verticalbox);
  
  /*
  verticalbox = gtk_vbox_new(TRUE,5);
  entrybox = gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(verticalbox),entrybox,TRUE,TRUE,5);
  */

  gtk_signal_connect(GTK_OBJECT(window1),"destroy",GTK_SIGNAL_FUNC(StopTheApp),NULL);
  gtk_widget_show_all(window1);
  gtk_main();
  
  return 0;
}

/**
*  Esta función recibe los datos de un evento dentro de 
*  una ventana y regresa un valor FALSE.
*  @author Guillermo Ortega
*  @param widget       La ventana
*  @param event        El evento
*  @param data         La estructura inicial
*  @return gboolean
*/
static gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer *data) {
  return FALSE;
}

/**
*  Esta función recibe los datos para crear un botón
*  y regresa el botón creado.
*  @author Guillermo Ortega
*  @param *Box       Caja contenedora
*  @param *Text      Texto del boton
*  @param *CallBack  funcion a llamar
*  @param *List      lista principal
*  @return GtkButton
*/
GtkWidget *AddButton(GtkWidget *Box, const gchar *Text,
		     gpointer CallBack, Lista *List){
  GtkWidget *button;
  button = gtk_button_new_with_label(Text);
  gtk_box_pack_start(GTK_BOX(Box),button,FALSE,TRUE,10);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(CallBack),List);
  gtk_widget_show(button);
  return button;
}

/**
*  Esta fucnión recibe los datos para crear un botón
*  y regresa el botón creado.
*  @author Guillermo Ortega
*  @param *window    ventana que se va a ocultar
*  @param *Box       Caja contenedora
*  @param *Text      Texto del boton
*  @param *CallBack  función a llamar
*  @param *List      lista principal
*  @return GtkButton
*/
GtkWidget *AddButton1(GtkWidget *window, GtkWidget *Box,
		      const gchar *Text, gpointer CallBack,Lista *List){
  GtkWidget *button;
  button = gtk_button_new_with_label(Text);
  gtk_box_pack_start(GTK_BOX(Box),button,FALSE,TRUE,10);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(CallBack),List);
  g_signal_connect_swapped (G_OBJECT (button), "clicked",
			    G_CALLBACK (gtk_widget_hide), G_OBJECT (window));
  gtk_widget_show(button);
  return button;
}

/**
*  Esta función recibe un caracter en el primer argumento y si
*  este es una letra minuscula lo convierte a mayuscula y regresa 
*  elnuevo valor en el segundo argumento.
*  Regresa un 1 si pudo convertir a mayuscula el caracter
*  y 0 si no pudo hacerlo.
*  @author Guillermo Ortega
*  @param chrData     El caracter a convertir (minuscula a mayuscula)
*  @param *may        El caracter convertido en mayuscula
*  @return int
*/
GtkWidget *Addlabel(GtkWidget *theBox, const gchar *buttonText){
  GtkWidget *label;
  label = gtk_label_new(buttonText);
  gtk_box_pack_start(GTK_BOX(theBox),label,FALSE,FALSE,0);
  gtk_widget_show(label);
  return label;
}

/**
*  Esta función recibe un caracter en el primer argumento y si
*  este es una letra minuscula lo convierte a mayuscula y regresa 
*  elnuevo valor en el segundo argumento.
*  Regresa un 1 si pudo convertir a mayuscula el caracter
*  y 0 si no pudo hacerlo.
*  @author Iggy Pop
*  @param chrData     El caracter a convertir (minuscula a mayuscula)
*  @param *may        El caracter convertido en mayuscula
*  @return int
*/
void close_window(GtkWidget *window, gpointer data){
  gtk_widget_destroy(window);
}

/**
*  Esta funcion termina la aplicacion
*  
*/
void StopTheApp(GtkWidget *window, gpointer data){
  gtk_main_quit();
}

/**
*  Esta funcion crea la ventana en donde se piden los nombres de los
*  jugadores.
*  @author Guillermo Ortega y Mateo Larralde
*  @param *window     Ventana Gtk
*  @param  data       Inicio-Estructura tipo Lista con toda la info del programa
*  @return void
*/
void Nuevo(GtkWidget *window, gpointer data){
  GtkWidget *Entrybox;
  GtkWidget *windownombres;
  GtkWidget *verticalbox,*button;
  GtkWidget *entrybox,*label1,*label2;
  Lista *Inicio = (Lista *)data;


  
  windownombres = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(windownombres),320,200);
  gtk_container_border_width(GTK_CONTAINER(windownombres),5);

  verticalbox = gtk_vbox_new(TRUE,5);
  label1 = Addlabel(verticalbox,"Jugador 1:");
  
  entrybox = gtk_entry_new();
  Inicio->Jugador1->entry = entrybox;
  gtk_box_pack_start(GTK_BOX(verticalbox),entrybox,TRUE,TRUE,5);
    
  label2 = Addlabel(verticalbox,"Jugador 2:");
  
  Entrybox = gtk_entry_new();
  Inicio->Jugador2->entry = Entrybox;
  gtk_box_pack_start(GTK_BOX(verticalbox),Entrybox,TRUE,TRUE,5);

  gtk_signal_connect(GTK_OBJECT(windownombres),
		     "destroy",GTK_SIGNAL_FUNC(StopTheApp),NULL);

  
  button = gtk_button_new_with_label("Continuar");
  gtk_box_pack_start(GTK_BOX(verticalbox),button,FALSE,TRUE,10);
  g_signal_connect_swapped (G_OBJECT (button),
			    "clicked",G_CALLBACK (gtk_widget_hide), G_OBJECT (windownombres));
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(NOMBRES),Inicio);
  gtk_widget_show(button);
  

 
  Inicio->ventana = windownombres;
  

  gtk_container_add(GTK_CONTAINER(windownombres),verticalbox);
  gtk_widget_show_all(windownombres);
}

/*********************************************************/

/**
*  Esta funcion despliega una ventana en donde se pide el nombre del
*  archivo que se desea cargar. 
*  @author Mateo Larrale
*  @param *window     ventana Gtk
*  @param data        Inicio
*  @return 
*/
void Cargar(GtkWidget *window, gpointer data){

  GtkWidget *windownombres;
  GtkWidget *verticalbox,*button;
  GtkWidget *entrybox,*label1;
  Lista *Inicio= (Lista *)data;
  
  //Armar ventana y Pedir nombre de archivo
  
  windownombres = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(windownombres),320,200);
  gtk_container_border_width(GTK_CONTAINER(windownombres),5);
  
  verticalbox = gtk_vbox_new(TRUE,5);
  label1 = Addlabel(verticalbox,"Escriba el nombre del archivo que quiere cargar:");
  
  entrybox = gtk_entry_new();
  Inicio->entry = entrybox;
  gtk_box_pack_start(GTK_BOX(verticalbox),entrybox,TRUE,TRUE,5);

  gtk_signal_connect(GTK_OBJECT(windownombres),"destroy",GTK_SIGNAL_FUNC(StopTheApp),NULL);

  button = AddButton1(windownombres,verticalbox,"Continuar",CARGAR,Inicio);

  //Cuando se de click en continuar debe guardar lo que este en la entrybox

  gtk_container_add(GTK_CONTAINER(windownombres),verticalbox);
  gtk_widget_show_all(windownombres);
  Inicio->ventana=windownombres;

}

/**
*  En esta ventana se valida que los nombres introducidos no sean los mismos,
*  y también que si se hayan introducido ambos nombres. Si si son validos,
*  se guardan en la memoria, se inicializa el tablero y comienza el juego.
*  @author Guillermo Ortega y Mateo Larralde
*  @param window      ventana Gtk
*  @param data        Inicio
*  @return 
*/
void NOMBRES(GtkWidget *window, gpointer data){
  const gchar *text;
  char text2[50],text3[50];

  Lista *Inicio=(Lista *)data;
  GtkWidget *window_tab,*verticalbox;
  GtkWidget *row_t, *box_t,*button,*box2,*box3;
  GtkWidget *box,*box4,*label,*label1,*label2,*bigbox;
  char turno[30], comid1[30], comid2[30];
  


  //Guarda los nombres en la memoria
  text = gtk_entry_get_text(GTK_ENTRY(Inicio->Jugador1->entry));
  strcpy(text2, text);
  
  text = gtk_entry_get_text(GTK_ENTRY(Inicio->Jugador2->entry));
  strcpy(text3,text);
  
  if(text2[0]=='\0' || text3[0]=='\0'){
    quick_message("Escribe el nombre de ambos jugadores",Inicio->ventana);
    return;
  }
    
  if(text2[0]!='\0' && text3[0]!='\0'){ 
    strcpy(Inicio->Jugador1->nombre, text2);
    strcpy(Inicio->Jugador2->nombre, text3);
  }
  
  if(Inicio->Jugador1->nombre[0]!='\0' && Inicio->Jugador2->nombre[0]!='\0'){
    
    if(strcmp(Inicio->Jugador1->nombre,Inicio->Jugador2->nombre)==0){
      quick_message("Los nombres de los jugadores no pueden ser iguales",Inicio->ventana);
      return;
    }
    
    //Aqui termina la validacion y se empieza a crear el tablero
    
    window_tab = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_signal_connect(GTK_OBJECT(window_tab),"destroy",GTK_SIGNAL_FUNC(StopTheApp),NULL);
    
    box_t = gtk_vbox_new(TRUE, 0);
    
    row_t = gtk_hbox_new(TRUE, 5);
    
    gtk_box_pack_start(GTK_BOX(box_t), create_pad(Inicio), FALSE, FALSE, 0);

    verticalbox=gtk_vbox_new(TRUE,30);
  
    box2 = gtk_hbox_new(FALSE,50);
    strcpy(text2,"Turno de: ");
    strcat(text2,Inicio->Jugador1->nombre);
      
    label = Addlabel(box2,text2);
    Inicio->labelt = label;
    gtk_box_pack_start(GTK_BOX(verticalbox),box2,FALSE,FALSE,20);


    strcpy(comid1,"Fichas comidas por ");
    strcat(comid1,Inicio->Jugador1->nombre);
    strcat(comid1," :");
        
    box3 = gtk_hbox_new(FALSE,50);
    
    label1 = Addlabel(box3,comid1);
    Inicio->label1 = label1;
    gtk_box_pack_start(GTK_BOX(verticalbox),box3,FALSE,FALSE,20);
    
    strcpy(comid2,"Fichas comidas por ");
    strcat(comid2,Inicio->Jugador2->nombre);
    strcat(comid2," :");
        
    box4 = gtk_hbox_new(FALSE,50);
    label2 = Addlabel(box4,comid2);
    Inicio->label2 = label2;
    gtk_box_pack_start(GTK_BOX(verticalbox),box4,FALSE,FALSE,20);

    box = gtk_hbox_new(TRUE,10);
    button = AddButton1(window_tab,box," Guardar ",GUARDAR,Inicio);
    gtk_box_pack_start(GTK_BOX(verticalbox),box,FALSE,FALSE,50);

    box = gtk_hbox_new(TRUE,10);

    button = AddButton1(window_tab,box,">>>",NULL,Inicio);
    gtk_box_pack_start(GTK_BOX(verticalbox),box,FALSE,FALSE,5);
    
    //gtk_box_pack_start(GTK_BOX(row_t),verticalbox,TRUE,TRUE,5);

    bigbox=gtk_hbox_new(FALSE,10);


    g_signal_connect(window_tab, "delete-event", G_CALLBACK(delete_event), NULL);
    g_signal_connect(window_tab, "destroy", G_CALLBACK(StopTheApp), NULL);

    
    //gtk_container_add(GTK_CONTAINER(windownombres),verticalbox);

    gtk_container_add(GTK_CONTAINER(bigbox), box_t);
    gtk_box_pack_start(GTK_BOX(bigbox),verticalbox,TRUE,TRUE,60);
    gtk_container_add(GTK_CONTAINER(window_tab), bigbox);
    
    gtk_widget_show_all(window_tab);
    
    gtk_main(); 
  }
}

/**
*  Esta funcion es la que despliega los mensajes de error, ya sea cuando
*  se eligieron nombres iguales, no se lleno uno de los nombres, no se escogio
*  el nombre del archivo a cargar o el nombre del archivo no existe.
*  @author Guillermo Ortega
*  @param 
*  @param        
*  @return 
*/
void quick_message (gchar *message, GtkWidget *parent) {
  GtkWidget *window, *button, *box;

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window),300,50);
  gtk_container_border_width(GTK_CONTAINER(window),5);
  
  box = gtk_vbox_new(TRUE,0);
  
  button = gtk_button_new_with_label(message);
  gtk_box_pack_start(GTK_BOX(box),button,FALSE,TRUE,10);
  
  g_signal_connect_swapped(GTK_OBJECT(button),"clicked",
			   G_CALLBACK(gtk_widget_hide),GTK_OBJECT(window));
  g_signal_connect_swapped(GTK_OBJECT(button),"clicked",
			   G_CALLBACK(gtk_widget_show),GTK_OBJECT(parent));
  gtk_widget_show(button);

  gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(StopTheApp),NULL);
  
  gtk_container_add (GTK_CONTAINER (window),box);
  gtk_widget_show_all (window);
}



//---------------------------------------------------//***********************************************************//
//---------------------------------------------------//***********************************************************//
//---------------------------------------------------//***********************************************************//
//---------------------------------------------------//***********************************************************//
//---------------------------------------------------//***********************************************************//

/**
*  Esta función recibe un caracter en el primer argumento y si
*  este es una letra minuscula lo convierte a mayuscula y regresa 
*  elnuevo valor en el segundo argumento.
*  Regresa un 1 si pudo convertir a mayuscula el caracter
*  y 0 si no pudo hacerlo.
*  @author Iggy Pop
*  @param chrData     El caracter a convertir (minuscula a mayuscula)
*  @param *may        El caracter convertido en mayuscula
*  @return int
*/
void command(int y) {
  
  switch(y){
  case 0:
    
    break;
  case 1:
    
    break;
    
  case 2:
    
    break;

  default:
    break;
  }
}

/**
*  Esta funcion cambia el color de los botones al ser apretados. Dependiendo
*  del turno, lo cambia a azul (Jugador1) o rojo (2). También llama a las 
*  funciones de validacion para revisar si se hizo una linea de 4 o de 5,
*  o si se comieron fichas. También avanza el turno. 
*  @author Guillermo Ortega y Mateo Larralde
*  @param widget      GtkWidget
*  @param data        Inicio
*  @return 
*/
void callback(GtkWidget *widget, gpointer data) {
  gchar *label;
  GdkPixbuf *pix1, *pix2;
  Lista *Inicio=(Lista *)data;

  GtkWidget *button;
  char turn1[30],turn2[30];
  
  if(Inicio->turno%2==1){

    strcpy(turn2,"Turno de: ");
    strcat(turn2,Inicio->Jugador2->nombre);
    gtk_label_set_text (GTK_LABEL(Inicio->labelt), turn2);
  }
  if(Inicio->turno%2==0){
    strcpy(turn1,"Turno de: ");
    strcat(turn1,Inicio->Jugador1->nombre);
    gtk_label_set_text (GTK_LABEL(Inicio->labelt), turn1);
  }
  

  int  y=0;
  
  g_object_get(G_OBJECT(widget), "label", &label, NULL);

  pix1=gdk_pixbuf_new_from_file("red.png",NULL);
  pix2=gdk_pixbuf_new_from_file("blue.png",NULL);
  
  pix1=gdk_pixbuf_scale_simple(pix1,25,25,GDK_INTERP_BILINEAR);
  pix2=gdk_pixbuf_scale_simple(pix2,25,25,GDK_INTERP_BILINEAR);
    
  GtkWidget *img_r = gtk_image_new_from_pixbuf(pix1);
  GtkWidget *img_b = gtk_image_new_from_pixbuf(pix2);

  if (label == 0 && (Inicio->turno)%2 == 1){
    gtk_button_set_image (GTK_BUTTON (widget), img_b);

    command(y);
  }
  else if (label == 0 && (Inicio->turno)%2 == 0){
    gtk_button_set_image (GTK_BUTTON (widget), img_r);

    y=1;
    command(y);
  }

  //  ComeFichas(button,Inicio);
  //FilasDe4(button,Inicio);

  
  Inicio->turno++;
  
   g_free(label);
}

/**
*  Esta función recibe la estructura con los datos generales
*  y genera el tablero de juego.
*  @author Guillermo Ortega
*  @param data    Inicio
*  @return GtkWidget
*/
GtkWidget *create_pad(gpointer data) {
  Lista *Inicio=(Lista *)data;
  GtkWidget *container;
  GtkWidget *row;

  for(int i=0;i<20;i++)
    for(int j=0;j<20;j++)
      Inicio->tablero[i][j]=0;

  container = gtk_vbox_new(FALSE, 3);
  
  for (int i = 0; i < 20; i++) {
    
    row = gtk_hbox_new(TRUE, 0);
    gtk_box_pack_start(GTK_BOX(container), row, FALSE, TRUE, 0);
    
    for(int j = 0; j < 20; j++){
   
      Inicio->buttons[i][j] = gtk_button_new_with_label(Inicio->tablero[i][j]);
      
      gtk_widget_set_size_request(Inicio->buttons[i][j], 35, 35);
    
      g_signal_connect(Inicio->buttons[i][j], "clicked", G_CALLBACK(callback), Inicio);
      g_signal_connect_swapped(GTK_OBJECT(Inicio->buttons[i][j]),"clicked",
			   G_CALLBACK(obtener_coordenada),GTK_OBJECT(Inicio));
   
      gtk_box_pack_start(GTK_BOX(row), Inicio->buttons[i][j], FALSE, TRUE, 2);
      gtk_widget_show(Inicio->buttons[i][j]);
    }
  }  
  return container;
}

/**
*  Esta función recibe la estructura con los datos generales
*  y genera el tablero de juego.
*  @author Guillermo Ortega
*  @param data    Inicio
*  @return GtkWidget
*/
void obtener_coordenada(GtkWidget *button, gpointer data){
  Lista *Inicio=(Lista *)data;

  for(int i=0;i<20;i++){
    for(int j=0;j<20;j++){
      if(Inicio->buttons[i][j]==button){
	if(Inicio->turno==3){
	  Inicio->X1=i;
	  Inicio->Y1=j;
	}
	else{
	  insertar_turno(&Inicio->turnos_l,i,j);
	}
	return;
      }
    }
  }
}


/**
*  Esta función recibe la estructura con los datos generales
*  y genera el tablero de juego.
*  @author Guillermo Ortega
*  @param data    Inicio
*  @return GtkWidget
*/
void insertar_turno(Jugadas **inicio,int x,int y){
  Jugadas *temp,*temp2;
  
  temp=( Jugadas* ) malloc(sizeof(Jugadas));
  temp->X=x;
  temp->Y=y;
  
  temp->sig=NULL;
  
  if(*inicio != NULL){
    temp2 = *inicio;
    while(temp2->sig != NULL){
      temp2 = temp2->sig;
    }
    temp2->sig=temp;
  }
  else{
    *inicio = temp;
  }
}	