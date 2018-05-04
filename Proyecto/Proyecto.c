#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<gtk/gtk.h>

typedef struct _node{

  char nombre[20];
  GtkWidget *entry;
  int fila4;
  int comidas;
  
}Jug;

typedef struct _node2{

  GtkWidget *entry;
  struct _node2 *sig;
  int X;
  int Y;
  Jug Jugador1;
  Jug Jugador2;
  
  
}Lista;




GtkWidget *AddButton(GtkWidget *theBox, const gchar *buttonText, gpointer CallBackFunction, GtkWidget *EntryBox);

void StopTheApp(GtkWidget *window, gpointer data);
void Nuevo(GtkWidget *window, gpointer data);
void Cargar(GtkWidget *window, gpointer data);



gint main ( gint argc, gchar *argv[])
{

  GtkWidget *window1;
  GtkWidget *button;
  GtkWidget *box;
  Lista *Inicio;
  Jug One,Two;

  // Inicio=(Lista*)malloc(sizeof(Lista));
  
  Inicio->sig=NULL;
  Inicio->Jugador1=One;
  Inicio->Jugador2=Two;

  //Ventana de nuevo juego o cargar

  
  gtk_init(&argc, &argv);

  window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window1),320,200);
  gtk_container_border_width(GTK_CONTAINER(window1),5);




  
  box = gtk_hbox_new(TRUE,5);

  button = AddButton(box,"Juego Nuevo",Nuevo,&Inicio);
  button = AddButton(box,"Cargar",Cargar,Inicio);




  

  gtk_container_add(GTK_CONTAINER(window1),box);

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

GtkWidget *AddButton(GtkWidget *theBox, const gchar *buttonText, gpointer CallBackFunction, GtkWidget *EntryBox)
{
    GtkWidget *button;
    button = gtk_button_new_with_label(buttonText);
    gtk_box_pack_start(GTK_BOX(theBox),button,FALSE,TRUE,0);
    gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(CallBackFunction),EntryBox);
    gtk_widget_show(button);
    return button;
    

}



void StopTheApp(GtkWidget *window, gpointer data)
{
    gtk_main_quit();
}


void Nuevo(GtkWidget *window, gpointer data){
  GtkWidget *Entrybox;
  GtkWidget *windownombres;
  GtkWidget *verticalbox;
  GtkWidget *entrybox;
  Lista *Movimientos;
  

  
  //Pedir nombres

  
  windownombres = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(windownombres),320,200);
  gtk_container_border_width(GTK_CONTAINER(windownombres),5);
  
  verticalbox = gtk_vbox_new(TRUE,5);
  
  entrybox = gtk_entry_new();
  
  gtk_box_pack_start(GTK_BOX(verticalbox),entrybox,TRUE,TRUE,5);
  gtk_signal_connect(GTK_OBJECT(windownombres),"destroy",GTK_SIGNAL_FUNC(StopTheApp),NULL);

  gtk_container_add(GTK_CONTAINER(windownombres),verticalbox);

  gtk_widget_show_all(windownombres);

  
}

void Cargar(GtkWidget *window, gpointer data){
}
