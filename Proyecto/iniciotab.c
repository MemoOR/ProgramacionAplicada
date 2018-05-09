

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
  int turno;
}Jugadas;

typedef struct _node2{

  GtkWidget *entry;
  GtkWidget *ventana;
  Jugadas *sig;
  int X;
  int Y;
  Jug *Jugador1;
  Jug *Jugador2;
  char archivo[20];
  char *tablero[20][20];
  
}Lista;






GtkWidget *AddButton(GtkWidget *theBox, const gchar *buttonText, gpointer CallBackFunction, Lista *EntryBox);

void StopTheApp(GtkWidget *window, gpointer data);
void Nuevo(GtkWidget *window, gpointer data);
void Cargar(GtkWidget *window, gpointer data);
void NOMBRES(GtkWidget *window, gpointer data);
void CARGAR(GtkWidget *window, gpointer data);
void Cargarjugs(GtkWidget *window, gpointer data);
static gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer *data);
static void destroy(GtkWidget *widget, gpointer data);
void command(int y);
void callback(GtkWidget *widget, gpointer callback_data);
GtkWidget *create_pad();
void ComeFichas(GtkWidget *widget, gpointer callback_data);
void FilasDe4(GtkWidget *widget, gpointer callback_data);








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

  //Cerrar ventana anterior

  //gtk_widget_destroy(Inicio->ventana);


  
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

  gtk_signal_connect(GTK_OBJECT(windownombres),"destroy",GTK_SIGNAL_FUNC(StopTheApp),NULL);
  
  gtk_container_add(GTK_CONTAINER(windownombres),verticalbox);

  gtk_widget_show_all(windownombres);
  


  

 
  
  
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

  gtk_signal_connect(GTK_OBJECT(windownombres),"destroy",GTK_SIGNAL_FUNC(StopTheApp),NULL);
  gtk_container_add(GTK_CONTAINER(windownombres),verticalbox);

  gtk_widget_show_all(windownombres);


  
  //Cerrar ventana anterior
  //  gtk_widget_destroy(Movimientos->ventana);

  
}




void NOMBRES(GtkWidget *window, gpointer data){

  const gchar *text;
  char text2[20],text3[20];

  Lista *Inicio=(Lista *)data;
  GtkWidget *window2;
  GtkWidget *row, *button, *box1;

  
  //Guarda los nobres en la memoria
 
  text =gtk_entry_get_text(GTK_ENTRY(Inicio->Jugador1->entry));
  strcpy(text2, text);
  
  
  text =gtk_entry_get_text(GTK_ENTRY(Inicio->Jugador2->entry));
  strcpy(text3,text);
  if((text2[0]!='\0')&&(text3[0]!='\0')){
    strcpy(Inicio->Jugador1->nombre,text2);
    strcpy(Inicio->Jugador2->nombre, text3);

    
    
    
    
  
    
    window2 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  
    box1 = gtk_vbox_new(TRUE, 0);
    
    row = gtk_hbox_new(TRUE, 5);
    
    gtk_box_pack_start(GTK_BOX(box1), create_pad(Inicio), TRUE, FALSE, 0);
    
    g_signal_connect(window2, "delete-event", G_CALLBACK(delete_event), NULL);
    g_signal_connect(window2, "destroy", G_CALLBACK(destroy), NULL);
    
    gtk_container_add(GTK_CONTAINER(window2), box1);

      gtk_signal_connect(GTK_OBJECT(window2),"destroy",GTK_SIGNAL_FUNC(StopTheApp),NULL);
    
    gtk_widget_show_all(window2);
  
    gtk_main();
    

    



    
  }
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
      //Mostrar una ventana que diga que ese archivo no existe
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
	temp->turno=a;
	temp2=temp;
	a++;
	
      }

      fclose(Archivo);
    }
  }


}


























//---------------------------------------------------




static gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer *data){
  return FALSE;
}

static void destroy(GtkWidget *widget, gpointer data) {
  gtk_main_quit();
}

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

void callback(GtkWidget *widget, gpointer callback_data) {
  gchar *label;
  GdkPixbuf *pix1, *pix2;

  int x = rand()%100, y=0;
  
  g_object_get(G_OBJECT(widget), "label", &label, NULL);

  pix1=gdk_pixbuf_new_from_file("red.png",NULL);
  pix2=gdk_pixbuf_new_from_file("blue.png",NULL);
  
  pix1=gdk_pixbuf_scale_simple(pix1,25,25,GDK_INTERP_BILINEAR);
  pix2=gdk_pixbuf_scale_simple(pix2,25,25,GDK_INTERP_BILINEAR);
    
  GtkWidget *img_r = gtk_image_new_from_pixbuf(pix1);
  GtkWidget *img_b = gtk_image_new_from_pixbuf(pix2);

  if (label == 0 && x >= 50){
    gtk_button_set_image (GTK_BUTTON (widget), img_b);
    command(y);
  }
  else if (label == 0 && x <= 51){
    gtk_button_set_image (GTK_BUTTON (widget), img_r);
    y=1;
    command(y);
  }
  g_free(label);
}

GtkWidget *create_pad(GtkWidget *widget, Lista *Inicio) {
  // Lista *Inicio=(Lista *)data;

  
 

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
      g_signal_connect(button, "clicked", G_CALLBACK(callback), NULL);
      
      gtk_box_pack_start(GTK_BOX(row), button, FALSE, TRUE, 2);
      gtk_widget_show(button);
    }
  }
  return container;
}
/*
int main(int argc, char **argv) {

  GtkWidget *window;
  GtkWidget *row, *button, *box1;
  
  gtk_init(&argc, &argv);
  
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  
  box1 = gtk_vbox_new(TRUE, 0);
  
  row = gtk_hbox_new(TRUE, 5);
  
  gtk_box_pack_start(GTK_BOX(box1), create_pad(), TRUE, FALSE, 0);
  
  g_signal_connect(window, "delete-event", G_CALLBACK(delete_event), NULL);
  g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL);
  
  gtk_container_add(GTK_CONTAINER(window), box1);
  
  gtk_widget_show_all(window);
  
  gtk_main();
  
  return 0;
}
  */




/*

void ComeFichas(GtkWidget *widget, gpointer callback_data)
{
	int x, int y; //variables del tablero
	var jugador=j; //j será el jugador en turno

	//valida a la derecha
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
*/
