

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
  Jug *Jugador1;
  Jug *Jugador2;
  char archivo[20];
  
}Lista;




GtkWidget *AddButton(GtkWidget *theBox, const gchar *buttonText, gpointer CallBackFunction, Lista *EntryBox);

void StopTheApp(GtkWidget *window, gpointer data);
void Nuevo(GtkWidget *window, gpointer data);
void Cargar(GtkWidget *window, gpointer data);
void Tablero(GtkWidget *window, gpointer data);
void NOMBRES(GtkWidget *window, gpointer data);
void CARGAR(GtkWidget *window, gpointer data);
void Cargarjugs(GtkWidget *window, gpointer data);


gint main ( gint argc, gchar *argv[])
{

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
  
  Inicio->sig=NULL;
  strcpy(Inicio->archivo, "\0");
  Inicio->Jugador1=&Jugador1;
  Inicio->Jugador2=&Jugador2;

  //Ventana de nuevo juego o cargar

  
  gtk_init(&argc, &argv);

  window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window1),320,200);
  gtk_container_border_width(GTK_CONTAINER(window1),25);


  verticalbox = gtk_vbox_new(TRUE,5);

  Inicio->ventana = window1;

  label = gtk_label_new ("¡Bienvenidos al juego de Penta!");

  gtk_box_pack_start(GTK_BOX(verticalbox),label,TRUE,TRUE,5);
  
  
  box = gtk_hbox_new(TRUE,30);
  
  
  button = AddButton(box,"Juego Nuevo",Nuevo,Inicio);
  button = AddButton(box,"Cargar",Cargar,Inicio);

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

GtkWidget *AddButton(GtkWidget *theBox, const gchar *buttonText, gpointer CallBackFunction, Lista *EntryBox)
{
  GtkWidget *button;
  button = gtk_button_new_with_label(buttonText);
  gtk_box_pack_start(GTK_BOX(theBox),button,FALSE,TRUE,10);
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
  Lista *Inicio= (Lista *)data;
  
  //Armar ventana y Pedir nombres
  
  
  windownombres = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(windownombres),320,200);
  gtk_container_border_width(GTK_CONTAINER(windownombres),5);
  
  verticalbox = gtk_vbox_new(TRUE,5);
  
  
  label1 = gtk_label_new ("Jugador 1:");
  gtk_box_pack_start(GTK_BOX(verticalbox),label1,TRUE,TRUE,5);
  
  entrybox = gtk_entry_new();
  Inicio->Jugador1->entry = entrybox;
  
  
  gtk_box_pack_start(GTK_BOX(verticalbox),entrybox,TRUE,TRUE,5);
  gtk_signal_connect(GTK_OBJECT(windownombres),"destroy",GTK_SIGNAL_FUNC(StopTheApp),NULL);
  
  label2 = gtk_label_new ("Jugador 2:");
  
  gtk_box_pack_start(GTK_BOX(verticalbox),label2,TRUE,TRUE,5);

  Entrybox = gtk_entry_new();
  Inicio->Jugador2->entry = Entrybox;
  
  
  
  gtk_box_pack_start(GTK_BOX(verticalbox),Entrybox,TRUE,TRUE,5);

  
  
  button = AddButton(verticalbox,"Continuar",NOMBRES,Inicio);
  
  //Cuando se apriete el boton, que guarde entrybox y Entrybox en Lista->Jug1 y Lista->Jug2
  
  
  gtk_container_add(GTK_CONTAINER(windownombres),verticalbox);

  gtk_widget_show_all(windownombres);
  

  //Cerrar ventana anterior
  
  // gtk_widget_destroy(GTK_WIDGET (Movimientos->ventana));
  
  
}

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

  label1 = gtk_label_new ("Como se llama el archivo que quiere cargar:");
  gtk_box_pack_start(GTK_BOX(verticalbox),label1,TRUE,TRUE,5);
  
  entrybox = gtk_entry_new();

  Inicio->entry = entrybox;

  
  gtk_box_pack_start(GTK_BOX(verticalbox),entrybox,TRUE,TRUE,5);
  gtk_signal_connect(GTK_OBJECT(windownombres),"destroy",GTK_SIGNAL_FUNC(StopTheApp),NULL);


  button = AddButton(verticalbox,"Continuar",CARGAR,Inicio);

  //Cuando se de click en continuar debe guardar lo que este en la entrybox

  
  gtk_container_add(GTK_CONTAINER(windownombres),verticalbox);

  gtk_widget_show_all(windownombres);


  
  //Cerrar ventana anterior
  //  gtk_widget_destroy(Movimientos->ventana);

  
}


void Tablero(GtkWidget *window, gpointer data){}



void NOMBRES(GtkWidget *window, gpointer data){

  const gchar *text;
  char text2[20],text3[20];

  Lista *Inicio=(Lista *)data;


  
  //Guarda los nobres en la memoria
 
  text =gtk_entry_get_text(GTK_ENTRY(Inicio->Jugador1->entry));
  strcpy(text2, text);

  
  text =gtk_entry_get_text(GTK_ENTRY(Inicio->Jugador2->entry));
  strcpy(text3,text);
  if((text2[0]!='\0')&&(text3[0]!='\0')){
    strcpy(Inicio->Jugador1->nombre,text2);
    strcpy(Inicio->Jugador2->nombre, text3);
  }
}


void CARGAR(GtkWidget *window, gpointer data){
  
  const gchar *text;
  char text2[20];
  Lista *Inicio=(Lista *)data;
  Lista *temp,*temp2;
  FILE *Archivo;
  
  
  //Guarda el nombre del archivo en la memoria
 
  text = gtk_entry_get_text(GTK_ENTRY(Inicio->entry));
  strcpy(text2, text);
  if(text[0]!='\0'){
    strcpy(Inicio->archivo,text2);
    strcat(text2,"txt");
    Archivo=fopen(text2,"rt");
    if(Archivo==NULL){
      //Mostrar una ventana que diga que ese archivo no existe
    }

    
    else{
      //Leer los nombres y luego jugada por jugada
      
      fgets(Inicio->Jugador1->nombre, 19, Archivo);
      fgets(Inicio->Jugador2->nombre, 19, Archivo);
      fscanf(Archivo,"%d",&Inicio->X);
      fscanf(Archivo,"%d",&Inicio->Y);
      temp=(Lista *)malloc(sizeof(Lista));
      Inicio->sig=temp;


      

    
  
}


