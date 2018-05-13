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
  int x,y;
}Coordenadas;

typedef struct _node2{
  GtkWidget *entry,*entry2;
  GtkWidget *ventana,*label1,*label2,*labelt;
  Jugadas *sig;
  int X1;
  int Y1;
  Coordenadas posicion[20][20];
  int turno;
  Jug *Jugador1;
  Jug *Jugador2;
  char archivo[20];
  char *tablero[20][20];
  int ganador;
}Lista;






GtkWidget *AddButton(GtkWidget *theBox, const gchar *buttonText,gpointer CallBackFunction, Lista *EntryBox);
GtkWidget *AddButton1(GtkWidget *window,GtkWidget *theBox,const gchar *buttonText, gpointer CallBackFunction,Lista *EntryBox);
GtkWidget *Addlabel(GtkWidget *theBox, const gchar *buttonText);
static gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer *data);
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
void Ganador(GtkWidget *window, gpointer data);
void GUARDAR(GtkWidget *window, gpointer data);




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
  
  Inicio->sig=NULL;
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

static gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer *data) {
  return FALSE;
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
  label1 = Addlabel(verticalbox,"Jugador 1 (Azul):");
  
  entrybox = gtk_entry_new();
  Inicio->Jugador1->entry = entrybox;
  gtk_box_pack_start(GTK_BOX(verticalbox),entrybox,TRUE,TRUE,5);
    
  label2 = Addlabel(verticalbox,"Jugador 2 (Rojo):");
  
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
  GtkWidget *window_tab,*verticalbox;
  GtkWidget *row_t, *box_t,*button,*box2,*box3,*box,*box4,*label,*label1,*label2,*bigbox;
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
    
    window_tab = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
    box_t = gtk_vbox_new(TRUE, 0);
    
    row_t = gtk_hbox_new(TRUE, 5);
    
    gtk_box_pack_start(GTK_BOX(box_t), create_pad(Inicio), TRUE, FALSE, 0);

    
    gtk_signal_connect(GTK_OBJECT(window_tab),"destroy",GTK_SIGNAL_FUNC(StopTheApp),NULL);

    verticalbox=gtk_vbox_new(FALSE,60);
    
    box = gtk_hbox_new(TRUE,50);
    
    button = AddButton1(window_tab,box,"Guardar",GUARDAR,Inicio);

 

    
    
    box2 = gtk_hbox_new(FALSE,50);
    strcpy(text2,"Turno de: ");
    strcat(text2,Inicio->Jugador1->nombre);
      
    label = Addlabel(box2,text2);
    Inicio->labelt = label;
    gtk_box_pack_start(GTK_BOX(verticalbox),box2,FALSE,TRUE,50);




    strcpy(comid1,"Fichas comidas por ");
    strcat(comid1,Inicio->Jugador1->nombre);
    
    
    box3 = gtk_hbox_new(FALSE,50);
    
    label1 = Addlabel(box3,comid1);
    Inicio->label1 = label1;
    gtk_box_pack_start(GTK_BOX(verticalbox),box3,FALSE,TRUE,50);
    
    strcpy(comid2,"Fichas comidas por ");
    strcat(comid2,Inicio->Jugador2->nombre);

    box4 = gtk_hbox_new(TRUE,50);
    label2 = Addlabel(box4,comid2);
    Inicio->label2 = label2;
    gtk_box_pack_start(GTK_BOX(verticalbox),box4,FALSE,TRUE,50);

    
    gtk_box_pack_start(GTK_BOX(verticalbox),box,FALSE,TRUE,50);
    //  gtk_box_pack_start(GTK_BOX(row_t),verticalbox,TRUE,TRUE,5);
    gtk_box_pack_start(GTK_BOX(box_t),row_t,TRUE,TRUE,3);

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

void quick_message (gchar *message, GtkWidget *parent) {
  GtkWidget *window, *button, *box;

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window),300,50);
  gtk_container_border_width(GTK_CONTAINER(window),5);
  
  box = gtk_vbox_new(TRUE,0);
  
  button = gtk_button_new_with_label(message);
  gtk_box_pack_start(GTK_BOX(box),button,FALSE,TRUE,10);
  
  g_signal_connect_swapped(GTK_OBJECT(button),"clicked",G_CALLBACK(gtk_widget_hide),GTK_OBJECT(window));
  g_signal_connect_swapped(GTK_OBJECT(button),"clicked",G_CALLBACK(gtk_widget_show),GTK_OBJECT(parent));
  gtk_widget_show(button);

  gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(StopTheApp),NULL);
  
  gtk_container_add (GTK_CONTAINER (window),box);
  gtk_widget_show_all (window);
}

void CARGAR(GtkWidget *window, gpointer data){
  
  char turn1[30],turn2[30];
  char text2[20];
  Lista *Inicio=(Lista *)data;
  Jugadas *temp,*temp2;
  FILE *Archivo;
  int a=1,b;
  const gchar *text;
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
      fscanf(Archivo,"%d",&Inicio->X1);
      fscanf(Archivo,"%d",&Inicio->Y1);
      
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
    label=1;
    command(y);
  }
  else if (label == 0 && (Inicio->turno)%2 == 0){
    gtk_button_set_image (GTK_BUTTON (widget), img_r);
    label=2;
    y=1;
    command(y);
  }

  //  ComeFichas(button,Inicio);
  //FilasDe4(button,Inicio);

  
  Inicio->turno++;
  
  // g_free(label);
}

GtkWidget *create_pad(gpointer data) {
  Lista *Inicio=(Lista *)data;
  

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

      Inicio->posicion[i][j].x=i+1; 
      Inicio->posicion[i][j].y=j+1;

      printf(" %d %d\n",Inicio->posicion[i][j].x,Inicio->posicion[i][j].y);
   
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


void ComeFichas(GtkWidget *widget, gpointer data){
  GtkWidget *button;
  Lista *Inicio=(Lista *)data;
  int x,y;
  char j;
  if (Inicio->turno%2 == 1)
    j = 1;
  if (Inicio->turno%2 == 0)
    j=2;
  
  //Valida derecha
  
  if(x<=17)
    {	
      if(Inicio->tablero[x][y]==j){
	
	if(Inicio->tablero[x+1][y]!=0 && Inicio->tablero[x+1][y]!=j)
	  {
	    
	    if(Inicio->tablero[x+2][y]!=0 && Inicio->tablero[x+2][y]!=j)
	      {
        
		if(Inicio->tablero[x+3][y]==j)
		  {
		  if (j==1)
		    Inicio->Jugador1->comidas++;
		  else
		    Inicio->Jugador2->comidas++;
		  
        
		  
		    Inicio->tablero[x+1][y]=0;
        
		    Inicio->tablero[x+2][y]=0;
		  }
	      }
	  }
      }
    }
  
  //valida diagonal abajo derecha
  if(x<=17 && y<=17)
    {
      if(Inicio->tablero[x][y]==j)
	{
	 
	  if(Inicio->tablero[x+1][y+1]!=0 && Inicio->tablero[x+1][y+1]==j)
	    {

	      if(Inicio->tablero[x+2][y+2]!=0 && Inicio->tablero[x+2][y+2]!=j)
		{
	        
		  if(Inicio->tablero[x+3][y+3]==j)
		    {
		      if (j==1)
			Inicio->Jugador1->comidas++;
		      else
			Inicio->Jugador2->comidas++;
			  
		      
		      
		      Inicio->tablero[x+1][y+1]=0;
		     
		      Inicio->tablero[x+2][y+2]=0;
		    }
		}
	    }
	}
    }
  
  //valida arriba
  if(y<=17)
    {
      if(Inicio->tablero[x][y]==j)
	{
        
	  if(Inicio->tablero[x][y+1]!=0  && Inicio->tablero[x][y+1]!=j)
	    {
	   
	      if(Inicio->tablero[x][y+2]!=0 && Inicio->tablero[x][y+2]==j)
		{
		 
		  if(Inicio->tablero[x][y+3]==j)
		    {
		      if(j==1)
			Inicio->Jugador1->comidas++;
		      else
			Inicio->Jugador2->comidas++;
	        
		      
		      Inicio->tablero[x][y+1]=0;
		      
		      Inicio->tablero[x][y+2]=0;
		    }
		}
	    }
	}
    }
  
  //valida diagonal abajo izquierda
  if(x<=3 && y<=17)
    {
      if(Inicio->tablero[x][y]==j)
	{
	   
	  
	  if(Inicio->tablero[x-1][y+1]!=0 && Inicio->tablero[x-1][y+1]!=j)
	    {
	    
	      if(Inicio->tablero[x-2][y+2]!=0 && Inicio->tablero[x-2][y+2]!=j)
		{
        
		  if(Inicio->tablero[x-3][y+3]==j)
		    {
		      if (j==1)
			Inicio->Jugador1->comidas++;
		      else
			Inicio->Jugador2->comidas++;
        
		      
		      Inicio->tablero[x-1][y+1]=0;
		      
		      Inicio->tablero[x-2][y+2]=0;
		    }
		}
	    }
	}
    }
  if (Inicio->Jugador1->comidas>4){
    Inicio->ganador=1;
    Ganador(button,Inicio);
  }
  if(Inicio->Jugador2->comidas>4){
    Inicio->ganador=2;
    Ganador(button, Inicio);
  }
}

void FilasDe4(GtkWidget *widget, gpointer data)
{
  int x, y, i=0,j=0; //variables del tablero
  //j será el jugador en turno
  int cont=1;
  int com1;
  int com2;
  char jug;
  GtkWidget *button;
  Lista *Inicio=(Lista *)data;
  
  com1=0;
  

  if(Inicio->turno %2 == 1)
    jug=1;
  if (Inicio->turno %2 ==0)
    jug=2;

  
    while(i<20){
      while(j<20){
	
	while(Inicio->tablero[i][j]==jug && i<20)
	  {
	    i++;
	    cont++;
	  }
	if(cont==5){

	  Ganador(button,Inicio);
	}
	if(cont==4){

	    com1++;

	}
	j++;
      }
      i++;
    }
    
  
    //valida diagonal derecha

    i=0;
    j=0;
    while(i<20){
      x=i;
      while(j<20){
	y=j;
	while(Inicio->tablero[i][j]==jug && i<20 && j<20)
	  {
	    i++;
	    j++;
	    cont++;
	  }
	if(cont==5){
	 
	  Ganador(button,Inicio);
	}
	if(cont==4){

	    com1++;

	}
	j=y+1;
      }
      i=x+1;
    }
  
    //valida abajo

    i=0;
    j=0;
    while(i<20){
      while(j<20){
	

	while(Inicio->tablero[i][j]==jug && i<20 && j<20)
	  {
	    cont++;
	    j++;
	  }
	if(cont==5){
        
	  Ganador(button, Inicio);
	}
	if(cont==4){

	    com1++;

	}
	j++;
      }
      i++;
    }
  
  //valida diagonal derecha abajo

    i=3;
    j=0;
    
    while(i<20){
      x=i;
      while(j<20){
	y=j;
	while(Inicio->tablero[i][j]==jug && i<20 && j<20 && i>-1)
	  {
	    cont++;
	    i--;
	    j++;
	  }
	if(cont==5){

	  Ganador(button, Inicio);
	}
	if(cont==4){

	    com1++;

	  }
	j=y+1;
      }
      i=x+1;
    }
    
  
    if(jug==1)
      Inicio->Jugador1->comidas=com1;
    if(jug==2)
      Inicio->Jugador2->comidas=com1;
  
  if(com1>4)
    Ganador(button, Inicio);
  
}
 
 
void Guardar(GtkWidget *window, gpointer data){
  Lista *Inicio = (Lista *) data;
  Jugadas *temp;
  FILE *Archivo;
  char text2[20];
  const gchar *text;

  text = gtk_entry_get_text(GTK_ENTRY(Inicio->entry2));
  strcpy(text2, text);
  strcat(text2,".txt");
  Archivo = fopen (text2,"wt");

  fputs(Inicio->Jugador1->nombre,Archivo);
  fputs(Inicio->Jugador2->nombre,Archivo);


  fprintf(Archivo,"%d", Inicio->X1);
  fprintf(Archivo,"%d", Inicio->Y1);
  temp= Inicio->sig;
  
  while (temp !=NULL){
    fprintf(Archivo,"%d", temp->X);
    fprintf(Archivo,"%d", temp->Y);
    temp=temp->sig;
  }

  fclose(Archivo);
}



void Ganador(GtkWidget *window, gpointer data){
  GtkWidget *ganador;
  GtkWidget *label;
  Lista *Inicio = (Lista *) data;
  char text [50];
  GtkWidget *verticalbox;
  
  ganador = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(ganador),320,200);
  gtk_container_border_width(GTK_CONTAINER(ganador),25);


  strcpy(text,"Felicidades al ganador: ");
  
  if(Inicio->ganador==1)
    strcat(text,Inicio->Jugador1->nombre);

  if(Inicio->ganador==2)
    strcat(text,Inicio->Jugador2->nombre);
  
  
  
  label = gtk_label_new (text);


  verticalbox = gtk_vbox_new(TRUE,5);
  gtk_box_pack_start(GTK_BOX(verticalbox),label,TRUE,TRUE,5);
  gtk_container_add(GTK_CONTAINER(ganador),verticalbox);

  gtk_signal_connect(GTK_OBJECT(ganador),"destroy",GTK_SIGNAL_FUNC(StopTheApp),NULL);
  gtk_widget_show_all(ganador);


}




void GUARDAR(GtkWidget *window, gpointer data){
  Lista *Inicio = (Lista *) data;
  GtkWidget *windownombres;
  GtkWidget *verticalbox,*button;
  GtkWidget *entrybox,*label1;


  
  windownombres = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(windownombres),320,200);
  gtk_container_border_width(GTK_CONTAINER(windownombres),5);
  
  verticalbox = gtk_vbox_new(TRUE,5);
  label1 = Addlabel(verticalbox,"Escriba el nombre del archivo donde lo quiere guardar:");
  
  entrybox = gtk_entry_new();
  Inicio->entry2 = entrybox;
  gtk_box_pack_start(GTK_BOX(verticalbox),entrybox,TRUE,TRUE,5);

  gtk_signal_connect(GTK_OBJECT(windownombres),"destroy",GTK_SIGNAL_FUNC(StopTheApp),NULL);

  button = AddButton1(windownombres,verticalbox,"Continuar",Guardar,Inicio);

  //Cuando se de click en continuar debe guardar lo que este en la entrybox

  gtk_container_add(GTK_CONTAINER(windownombres),verticalbox);
  gtk_widget_show_all(windownombres);



}
