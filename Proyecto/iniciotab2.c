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

typedef struct _node3{
  struct _node3 *sig;

  int X;
  int Y;

}Jugadas;

typedef struct _node4{

  int X;
  int Y;

}Coordenadas;



typedef struct _node2{
  GtkWidget *entry;
  GtkWidget *ventana;
  Jugadas *sig;
  int X;
  int Y;
  Coordenadas *Coor;
  int turno;
  Jug *Jugador1;
  Jug *Jugador2;
  char archivo[20];
  char *tablero[20][20];
}Lista;






GtkWidget *AddButton(GtkWidget *theBox, const gchar *buttonText,gpointer CallBackFunction, Lista *EntryBox);
GtkWidget *AddButton1(GtkWidget *window,GtkWidget *theBox,const gchar *buttonText, gpointer CallBackFunction,Lista *EntryBox);
GtkWidget *Addlabel(GtkWidget *theBox, const gchar *buttonText);
void StopTheApp(GtkWidget *window, gpointer data);
void Nuevo(GtkWidget *window, gpointer data);
void Cargar(GtkWidget *window, gpointer data);
void NOMBRES(GtkWidget *window, gpointer data);
void CARGAR(GtkWidget *window, gpointer data);
void Cargarjugs(GtkWidget *window, gpointer data);
void Guardar(GtkWidget *window, gpointer data);
void command(int y);
void callback(GtkWidget *widget, gpointer data);
GtkWidget *create_pad();
void ComeFichas(GtkWidget *widget, gpointer data);
void FilasDe4(GtkWidget *widget, gpointer data);
void quick_message (gchar *message, GtkWidget *parent);
void close_window(GtkWidget *window, gpointer data);

gint main ( gint argc, gchar *argv[]){

  GtkWidget *window1;
  GtkWidget *button;
  GtkWidget *box,*label,*verticalbox;
  Lista *Inicio;
  Jug Jugador1,Jugador2;
  Coordenadas Lugares;
  
  
  Inicio=(Lista*)malloc(sizeof(Lista));
  
  /*
  Jugador1=(Jug*)malloc(sizeof(Jug));
  Jugador2=(Jug*)malloc(sizeof(Jug));
  */
  
  strcpy(Jugador1.nombre, "\0");
  strcpy(Jugador2.nombre, "\0");
  
  Inicio->sig=NULL;
  Jugador1.comidas=0;
  Jugador2.comidas=0;
  
  strcpy(Inicio->archivo, "\0");
  Inicio->Jugador1=&Jugador1;
  Inicio->Jugador2=&Jugador2;
  Inicio->turno=3;
  Inicio->X=-1;
  Inicio->Y=-1;
  Inicio->Coor=&Lugares;
 

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

GtkWidget *AddButton(GtkWidget *theBox, const gchar *buttonText,
		     gpointer CallBackFunction, Lista *EntryBox){
  GtkWidget *button;
  button = gtk_button_new_with_label(buttonText);
  gtk_box_pack_start(GTK_BOX(theBox),button,FALSE,TRUE,10);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(CallBackFunction),EntryBox);
  gtk_widget_show(button);
  return button;
}

GtkWidget *AddButton1(GtkWidget *window, GtkWidget *theBox,const gchar *buttonText, gpointer CallBackFunction,Lista *EntryBox){
  GtkWidget *button;
  button = gtk_button_new_with_label(buttonText);
  gtk_box_pack_start(GTK_BOX(theBox),button,FALSE,TRUE,10);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(CallBackFunction),EntryBox);
  g_signal_connect_swapped (G_OBJECT (button), "clicked",G_CALLBACK (gtk_widget_hide), G_OBJECT (window));
  gtk_widget_show(button);
  return button;
}

GtkWidget *Addlabel(GtkWidget *theBox, const gchar *buttonText){
    GtkWidget *label;
    label = gtk_label_new(buttonText);
    gtk_box_pack_start(GTK_BOX(theBox),label,FALSE,FALSE,0);
    gtk_widget_show(label);
    return label;
}

void close_window(GtkWidget *window, gpointer data){
  gtk_widget_destroy(window);
}

void StopTheApp(GtkWidget *window, gpointer data){
  gtk_main_quit();
}

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

  gtk_signal_connect(GTK_OBJECT(windownombres),"destroy",GTK_SIGNAL_FUNC(StopTheApp),NULL);

  
  button = gtk_button_new_with_label("Continuar");
  gtk_box_pack_start(GTK_BOX(verticalbox),button,FALSE,TRUE,10);
  g_signal_connect_swapped (G_OBJECT (button), "clicked",G_CALLBACK (gtk_widget_hide), G_OBJECT (windownombres));
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(NOMBRES),Inicio);
  gtk_widget_show(button);
  
  //button = AddButton(verticalbox,"Continuar",NOMBRES,Inicio);
 
  Inicio->ventana = windownombres;
  
  //button = AddButton(verticalbox,"Continuar",NOMBRES,Inicio);
  
  //Cuando se apriete el boton, que guarde entrybox y Entrybox en Lista->Jug1 y Lista->Jug2

  gtk_container_add(GTK_CONTAINER(windownombres),verticalbox);
  gtk_widget_show_all(windownombres);
}

/*********************************************************/

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

}

void NOMBRES(GtkWidget *window, gpointer data){

  const gchar *text;
  char text2[50],text3[50];

  Lista *Inicio=(Lista *)data;
  GtkWidget *window_tab;
  GtkWidget *row_t, *box_t;
  
  //Guarda los nombres en la memoria
 
  text = gtk_entry_get_text(GTK_ENTRY(Inicio->Jugador1->entry));
  strcpy(text2, text);
  
  text = gtk_entry_get_text(GTK_ENTRY(Inicio->Jugador2->entry));
  strcpy(text3,text);
  
  if(text2[0]=='\0' || text3[0]=='\0'){
    quick_message("Escribe el nombre de ambos juagdores",Inicio->ventana);
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
    
    window_tab = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
    gtk_signal_connect(GTK_OBJECT(window_tab),"destroy",GTK_SIGNAL_FUNC(StopTheApp),NULL);
    
    box_t = gtk_vbox_new(TRUE, 0);
    
    row_t = gtk_hbox_new(TRUE, 5);
    
    gtk_box_pack_start(GTK_BOX(box_t), create_pad(Inicio), TRUE, FALSE, 0);
    
    gtk_signal_connect(GTK_OBJECT(window_tab),"destroy",GTK_SIGNAL_FUNC(StopTheApp),NULL);
    
    gtk_container_add(GTK_CONTAINER(window_tab), box_t);
    
    gtk_widget_show_all(window_tab);
    
    gtk_main(); 
  }
  
}

void quick_message (gchar *message, GtkWidget *parent) {
  GtkWidget *window, *button, *box;

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window),300,50);
  gtk_container_border_width(GTK_CONTAINER(window),5);
  
  box = gtk_vbox_new(TRUE,0);
  
  button = gtk_button_new_with_label(message);
  gtk_box_pack_start(GTK_BOX(box),button,FALSE,TRUE,10);
  
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(gtk_widget_hide_all),window);
  
  g_signal_connect_swapped(GTK_OBJECT(button),"clicked",G_CALLBACK(gtk_widget_show),GTK_OBJECT(parent));
  gtk_widget_show(button);

  gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(gtk_widget_show),parent);
  
  gtk_container_add (GTK_CONTAINER (window),box);
  gtk_widget_show_all (window);
}

void CARGAR(GtkWidget *window, gpointer data){
  
  const gchar *text;
  char text2[20];
  Lista *Inicio=(Lista *)data;
  Jugadas *temp,*temp2;
  FILE *Archivo;
  int a=1,b;
  
  //Guarda el nombre del archivo en la memoria
 
  text = gtk_entry_get_text(GTK_ENTRY(Inicio->entry));
  strcpy(text2, text);
  
  if(text[0]!='\0'){
    strcpy(Inicio->archivo,text2);
    strcat(text2,".txt");
    
    Archivo=fopen(text2,"rt");
    
    if(Archivo==NULL){
      quick_message("No existe ese archivo",NULL);
      gtk_main_quit();
    }
    else{
      //Leer los nombres y luego jugada por jugada
      
      fgets(Inicio->Jugador1->nombre, 19, Archivo);
      b=strlen(Inicio->Jugador1->nombre);
      Inicio->Jugador1->nombre[b-1]='\0';
      fgets(Inicio->Jugador2->nombre, 19, Archivo);
      b=strlen(Inicio->Jugador2->nombre);
      Inicio->Jugador2->nombre[b-1]='\0';
      fscanf(Archivo,"%d",&Inicio->X);
      fscanf(Archivo,"%d",&Inicio->Y);
      
      while(!feof(Archivo)){
	
	temp=(Jugadas *)malloc(sizeof(Jugadas));
	temp->sig=NULL;
	if(a==1){
	  Inicio->sig=temp;
	  a=2;
	}
	else{
	  temp2->sig=temp;
	}
	
	fscanf(Archivo,"%d",&temp->X);
	fscanf(Archivo,"%d",&temp->Y);
	Inicio->turno++;
	temp2=temp;
	a++;
	
      }
      
      fclose(Archivo);
    }
  }  
}

//---------------------------------------------------//***********************************************************//
//---------------------------------------------------//***********************************************************//
//---------------------------------------------------//***********************************************************//
//---------------------------------------------------//***********************************************************//
//---------------------------------------------------//***********************************************************//

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

void callback(GtkWidget *widget, gpointer data) {
  gchar *label;
  GdkPixbuf *pix1, *pix2;
  Lista *Inicio=(Lista *)data;
  

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
  Inicio->turno++;
  
  g_free(label);
}

GtkWidget *create_pad(gpointer data) {
  Lista *Inicio=(Lista *)data;
  int x=0,y=0;
  

  for(int i=0;i<20;i++)
    for(int j=0;j<20;j++)
      Inicio->tablero[i][j]=0;

  GtkWidget *container;
  GtkWidget *row, *button;

  container = gtk_vbox_new(FALSE, 3);
  
  for (int i = 0; i < 20; i++) {
    
    row = gtk_hbox_new(TRUE, 0);
    gtk_box_pack_start(GTK_BOX(container), row, FALSE, TRUE, 0);
    
    for(int j = 0; j < 20; j++){
   
      button = gtk_button_new_with_label(Inicio->tablero[i][j]);

      
      
      
      gtk_widget_set_size_request(button, 35, 35);
      g_signal_connect(button, "clicked", G_CALLBACK(callback), Inicio);

      
      gtk_box_pack_start(GTK_BOX(row), button, FALSE, TRUE, 2);
      gtk_widget_show(button);
    }
  }
  return container;
}

//arreglar oculatar mensahes
//arreglar cerrar aplicacion desde tablero
/*

void ComeFichas(GtkWidget *widget, gpointer data){

  Lista *Inicio=(Lista *)data;

  //Valida derecha
  
  if(x<=17)
    {	
      if(casilla!="vacio" && casilla==j){
	x++;
	if(casilla!="vacio" && casilla!=j)
	  {
	    x++;
	    if(casilla!="vacio" && casilla!=j)
	      {
		x++;
		if(casilla!="vacio" && casilla==j)
		  {
		    j.comidas+2;
		    x--;
		    casilla=vacio;
		    x--;
		    casilla=vacio;
		  }
	      }
	  }
      }
    }
  
  //valida diagonal abajo derecha
  if(x<=17 && y<=17)
    {
      if(casilla!="vacio" && casilla==j)
	{
	  x++; 
	  y++;
	  if(casilla!="vacio" && casilla!=j)
	    {
	      x++;
	      y++;
	      if(casilla!="vacio" && casilla!=j)
		{
		  x++;
		  y++;
		  if(casilla!="vacio" && casilla==j)
		    {
		      j.comidas+2;
		      x--;
		      casilla=vacia;
		      x--;
		      casilla=vacia;
		    }
		}
	    }
	}
    }
  
  //valida abajo
  if(y<=17)
    {
      if(casilla!="vacio" && casilla==j)
	{
	  y++;
	  if(casilla!="vacio" && casilla!=j)
	    {
	      y++;
	      if(casilla!="vacio" && casilla==j)
		{
		  y++;
		  if(casilla!="vacio" && casilla!=j)
		    {
		      j.comidas+2;
		      y--;
		      casilla=vacia;
		      y--;
		      casilla=vacia;
		    }
		}
	    }
	}
    }
  
  //valida diagonal abajo izquierda
  if(x<=3 && y<=17)
    {
      if(casilla!="vacio" && casilla==j)
	{
	  x--; 
	  y++;
	  if(casilla!="vacio" && casilla!=j)
	    {
	      x--;
	      y++;
	      if(casilla!="vacio" && casilla!=j)
		{
		  x--;
		  y++;
		  if(casilla!="vacio" && casilla==j)
		    {
		      j.comidas+2;
		      x--;
		      casilla=vacia;
		      x--;
		      casilla=vacia;
		    }
		}
	    }
	}
    }
}


void FilasDe4(GtkWidget *widget, gpointer callback_data)
{
  int x, y, i; //variables del tablero
  var jugador=j; //j será el jugador en turno
  
  //valida derecha
  if(x<=17)
    {
      while(casilla!="vacio" && casilla==j && i<=3)
	{
	  i++;
	  x++;
	}
      if(i==3)
	{
	  j.filas=j.filas++;
	}
    }
  
  //valida diagonal derecha
  if(x<=17 && y<=17)
    {
      while(casilla!="vacio" && casilla==j && i<=3)
	{
	  i++;
	  x++;
	  y++;
	}
      if(i==3)
	{
	  j.filas=j.filas++;
	}
    }
  
  //valida abajo
  if(y<=17)
    {
      while(casilla!="vacio" && casilla==j && i<=3)
	{
	  i++;
	  y++;
	}
      if(i==3)
	{
	  j.filas=j.filas++;
	}
    }
  
  //valida diagonal derecha abajo
  if(x>3 && y<=17)
    {
      while(casilla!="vacio" && casilla==j && i<=3)
	{
	  i++;
	  x--;
	  y++;
	}
      if(i==3)
	{
	  j.filas=j.filas++;
	}
    }
}



  
void Guardar(GtkWidget *window, gpointer data){
  Lista *Inicio = (Lista *) data;
  Lista *temp, temp2;
  FILE *Archivo;

  Archivo = fopen (nombre);

  fputs(Inicio->Jugador1->nombre);
  fputs(Inicio->Jugador2->nombre);

  temp=Inicio;
  
  while (temp->sig !=NULL){
    fprintf("%d", temp->X);
    fprintf("%d", temp->Y);
    temp=temp->sig;
  }

  fclose(Archivo);
}

*/
