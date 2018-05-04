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
  GtkWidget *ventana;
  struct _node2 *sig;
  int X;
  int Y;
  Jug Jugador1;
  Jug Jugador2;
  char archivo[20];
  
}Lista;




GtkWidget *AddButton(GtkWidget *theBox, const gchar *buttonText, gpointer CallBackFunction, GtkWidget *EntryBox);

void StopTheApp(GtkWidget *window, gpointer data);
void Nuevo(GtkWidget *window, gpointer data);
void Cargar(GtkWidget *window, gpointer data);
void Tablero(GtkWidget *window, gpointer data);
void CARGAR(GtkWidget *window, gpointer data);





gint main ( gint argc, gchar *argv[])
{

  GtkWidget *window1;
  GtkWidget *button;
  GtkWidget *box;
  Lista *Inicio;
  Jug One,Two;

  Inicio=(Lista*)malloc(sizeof(Lista));
  
  Inicio->sig=NULL;
  Inicio->Jugador1=One;
  Inicio->Jugador2=Two;

  //Ventana de nuevo juego o cargar

  
  gtk_init(&argc, &argv);

  window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window1),320,200);
  gtk_container_border_width(GTK_CONTAINER(window1),5);


  Inicio->ventana = window1;

  
  box = gtk_hbox_new(TRUE,5);

  /* button = AddButton(box,"Juego Nuevo",Nuevo,&Inicio);
  button = AddButton(box,"Cargar",Cargar,Inicio);

  */

  
    button = gtk_button_new_with_label("Juego Nuevo");
    gtk_box_pack_start(GTK_BOX(box),button,FALSE,TRUE,0);
    gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(Nuevo),&Inicio);
    gtk_widget_show(button);


    button = gtk_button_new_with_label("Cargar");
    gtk_box_pack_start(GTK_BOX(box),button,FALSE,TRUE,0);
    gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(Cargar),&Inicio);
    gtk_widget_show(button);

    

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
  GtkWidget *verticalbox,*button;
  GtkWidget *entrybox,*label1,*label2;
  Lista *Movimientos= (Lista *)data;


  

  
  //Armar ventana y Pedir nombres

  
  windownombres = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(windownombres),320,200);
  gtk_container_border_width(GTK_CONTAINER(windownombres),5);
  
  verticalbox = gtk_vbox_new(TRUE,5);

  label1 = gtk_label_new ("Jugador 1:");
  gtk_box_pack_start(GTK_BOX(verticalbox),label1,TRUE,TRUE,5);
  
  entrybox = gtk_entry_new();
  
  gtk_box_pack_start(GTK_BOX(verticalbox),entrybox,TRUE,TRUE,5);
  gtk_signal_connect(GTK_OBJECT(windownombres),"destroy",GTK_SIGNAL_FUNC(StopTheApp),NULL);

  label2 = gtk_label_new ("Jugador 2:");

  gtk_box_pack_start(GTK_BOX(verticalbox),label2,TRUE,TRUE,5);

  Entrybox = gtk_entry_new();

  gtk_box_pack_start(GTK_BOX(verticalbox),Entrybox,TRUE,TRUE,5);



    button = gtk_button_new_with_label("Continuar");
    gtk_box_pack_start(GTK_BOX(verticalbox),button,FALSE,TRUE,0);
    gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(Tablero),&Movimientos);
    gtk_widget_show(button);

    //Cuando se apriete el boton, que guarde entrybox y Entrybox en Lista->Jug1 y Lista->Jug2
  
  
  gtk_container_add(GTK_CONTAINER(windownombres),verticalbox);

  gtk_widget_show_all(windownombres);


  //Cerrar ventana anterior

  gtk_widget_destroy(GTK_WIDGET (Movimientos->ventana));
  
  
}

void Cargar(GtkWidget *window, gpointer data){

  GtkWidget *Entrybox;
  GtkWidget *windownombres;
  GtkWidget *verticalbox,*button;
  GtkWidget *entrybox,*label1,*label2;
  Lista *Movimientos= (Lista *)data;


  
  //Armar ventana y Pedir nombre de archivo

  
  windownombres = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(windownombres),320,200);
  gtk_container_border_width(GTK_CONTAINER(windownombres),5);
  
  verticalbox = gtk_vbox_new(TRUE,5);

  label1 = gtk_label_new ("Como se llama el archivo que quiere cargar:");
  gtk_box_pack_start(GTK_BOX(verticalbox),label1,TRUE,TRUE,5);
  
  entrybox = gtk_entry_new();
  
  gtk_box_pack_start(GTK_BOX(verticalbox),entrybox,TRUE,TRUE,5);
  gtk_signal_connect(GTK_OBJECT(windownombres),"destroy",GTK_SIGNAL_FUNC(StopTheApp),NULL);


  button = gtk_button_new_with_label("Continuar");
  gtk_box_pack_start(GTK_BOX(verticalbox),button,FALSE,TRUE,0);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(CARGAR),&Movimientos);
  gtk_widget_show(button);

  //Cuando se de click en continuar debe guardar lo que este en la entrybox

  
  gtk_container_add(GTK_CONTAINER(windownombres),verticalbox);

  gtk_widget_show_all(windownombres);


  
  //Cerrar ventana anterior
  //  gtk_widget_destroy(Movimientos->ventana);

  
}


void Tablero(GtkWidget *window, gpointer data){}



void CARGAR(GtkWidget *window, gpointer data){

  const gchar *text;
  char text2[20];
  int x,i=0;
  Lista *Movimientos=(Lista *)data;
  
  
  //  text =gtk_entry_get_text(GTK_ENTRY(datos->entry));

}
