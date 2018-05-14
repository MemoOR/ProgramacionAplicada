/* @file funcion.h
*  @brief Separamos el programa para trabajar mas facilmenta al 
*  mismo tiempo, aqui estan el resto de las funciones, especialmente
*  las validaciones y lo que no usa tanto Gtk
*  @author Guillermo Ortega, Mateo Larralde y Mariana
*  @date 14/05/2018
*/

/**
*  Esta funcion valida que el archivo a cargar sea valido. Si si lo es, 
*  lo abre y carga el nombre de los jugadores y tambien va cargando
*  en una lista dinamica las coordenadas de cada tiro. Ya que se cargaron,
*  se inicializa el tablero-
*  @author Mateo Larralde
*  @param window      GtkWindow
*  @param data        Inicio
*  @return 
*/

void CARGAR(GtkWidget *window, gpointer data){
  
  char turn1[30],turn2[30];
  char text2[20];
  Lista *Inicio=(Lista *)data;
  Jugadas *temp,*temp2;
  FILE *Archivo;
  int a=1,b;
  const gchar *text;
  GtkWidget *window_tab,*verticalbox;
  GtkWidget *row_t, *box_t,*button,*box2,*box3,*box;
  GtkWidget *box4,*label,*label1,*label2,*bigbox;
  char turno[30], comid1[30], comid2[30];


  
  //Guarda el nombre del archivo en la memoria
 
  text = gtk_entry_get_text(GTK_ENTRY(Inicio->entry));
  strcpy(text2, text);

  if(text[0]=='\0'){
    quick_message("Introduzca el nombre del archivo",Inicio->ventana);
    return;
  }

  else{
  

    strcpy(Inicio->archivo,text2);
    strcat(text2,".txt");
    
    Archivo=fopen(text2,"rt");
    
    if(Archivo==NULL){
      quick_message("No existe ese archivo",Inicio->ventana);
      return;
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
	  Inicio->turnos_l=temp;
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
      
      //Aqui se crea la ventana del tablero
      
      
    
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
      button = AddButton1(window_tab,box,"<<<",NULL,Inicio);
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
  


}
  



/**
*  Esta función valida si se comieron fichas en la ultima tirada. Valida
*  desde el punto donde se tiro hacia todas las direcciones.
*  @author Mateo Larralde y Mariana.
*  @param widget GtkWidget
*  @param data   Inicio
*  @return 
*/

void ComeFichas(int y,int x,gpointer data){
  GtkWidget *button;
  Lista *Inicio=(Lista *)data;
  char j,lab1[30],lab2[30];
  char aux[5];
  
  if (Inicio->turno%2 == 1)
    j = 2;
  if (Inicio->turno%2 == 0)
    j=1;
  
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
		    if (j==1){
		      Inicio->Jugador1->comidas=Inicio->Jugador1->comidas+2;
		      strcpy(lab1,"Fichas comidas por ");
		      strcat(lab1 ,Inicio->Jugador1->nombre);
		      sprintf(aux,"%d",Inicio->Jugador1->comidas);
		      strcat(lab1, aux);
		      gtk_label_set_text (GTK_LABEL(Inicio->label1), lab1);
		    }
		    else{
		      Inicio->Jugador2->comidas=Inicio->Jugador2->comidas+2;
		      strcpy(lab2,"Fichas comidas por ");
		      strcat(lab2 ,Inicio->Jugador2->nombre);
		      sprintf(aux,"%d",Inicio->Jugador2->comidas);
		      strcat(lab2, aux);
		      gtk_label_set_text (GTK_LABEL(Inicio->label2), lab2);		  
		    }
		  
		    Inicio->tablero[x+1][y]=0;
        
		    Inicio->tablero[x+2][y]=0;
		  }
	      }
	  }
      }
    }

    //Valida izquierda
  
  if(x>2)
    {	
      if(Inicio->tablero[x][y]==j){
	
	if(Inicio->tablero[x-1][y]!=0 && Inicio->tablero[x-1][y]!=j)
	  {
	    
	    if(Inicio->tablero[x-2][y]!=0 && Inicio->tablero[x-2][y]!=j)
	      {
        
		if(Inicio->tablero[x-3][y]==j)
		  {
		    if (j==1){
		      Inicio->Jugador1->comidas=Inicio->Jugador1->comidas+2;
		      strcpy(lab1,"Fichas comidas por ");
		      strcat(lab1 ,Inicio->Jugador1->nombre);
		      sprintf(aux,"%d",Inicio->Jugador1->comidas);
		      strcat(lab1, aux);
		      gtk_label_set_text (GTK_LABEL(Inicio->label1), lab1);
		    }
		    else{
		      Inicio->Jugador2->comidas=Inicio->Jugador2->comidas+2;
		      strcpy(lab2,"Fichas comidas por ");
		      strcat(lab2 ,Inicio->Jugador2->nombre);
		      sprintf(aux,"%d",Inicio->Jugador2->comidas);
		      strcat(lab2, aux);
		      gtk_label_set_text (GTK_LABEL(Inicio->label2), lab2);		  
		    }
		  
		    Inicio->tablero[x-1][y]=0;
        
		    Inicio->tablero[x-2][y]=0;
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
		      if (j==1){
		      Inicio->Jugador1->comidas=Inicio->Jugador1->comidas+2;
		      strcpy(lab1,"Fichas comidas por ");
		      strcat(lab1 ,Inicio->Jugador1->nombre);
		      sprintf(aux,"%d",Inicio->Jugador1->comidas);
		      strcat(lab1, aux);
		      gtk_label_set_text (GTK_LABEL(Inicio->label1), lab1);
		      }
		      else{
		      Inicio->Jugador2->comidas=Inicio->Jugador2->comidas+2;
		      strcpy(lab2,"Fichas comidas por ");
		      strcat(lab2 ,Inicio->Jugador2->nombre);
		      sprintf(aux,"%d",Inicio->Jugador2->comidas);
		      strcat(lab2, aux);
		      gtk_label_set_text (GTK_LABEL(Inicio->label2), lab2);
		      }
		      
		      
		      Inicio->tablero[x+1][y+1]=0;
		     
		      Inicio->tablero[x+2][y+2]=0;
		    }
		}
	    }
	}
    }



    //valida diagonal arriba derecha
  if(x<=17 && y>2)
    {
      if(Inicio->tablero[x][y]==j)
	{
	 
	  if(Inicio->tablero[x+1][y-1]!=0 && Inicio->tablero[x+1][y-1]==j)
	    {

	      if(Inicio->tablero[x+2][y-2]!=0 && Inicio->tablero[x+2][y-2]!=j)
		{
	        
		  if(Inicio->tablero[x+3][y-3]==j)
		    {
		      if (j==1){
		      Inicio->Jugador1->comidas=Inicio->Jugador1->comidas+2;
		      strcpy(lab1,"Fichas comidas por ");
		      strcat(lab1 ,Inicio->Jugador1->nombre);
		      sprintf(aux,"%d",Inicio->Jugador1->comidas);
		      strcat(lab1, aux);
		      gtk_label_set_text (GTK_LABEL(Inicio->label1), lab1);
		      }
		      else{
		      Inicio->Jugador2->comidas=Inicio->Jugador2->comidas+2;
		      strcpy(lab2,"Fichas comidas por ");
		      strcat(lab2 ,Inicio->Jugador2->nombre);
		      sprintf(aux,"%d",Inicio->Jugador2->comidas);
		      strcat(lab2, aux);
		      gtk_label_set_text (GTK_LABEL(Inicio->label2), lab2);
		      }
		      
		      
		      Inicio->tablero[x+1][y-1]=0;
		     
		      Inicio->tablero[x+2][y-2]=0;
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
		      if(j==1){
			Inicio->Jugador1->comidas=Inicio->Jugador1->comidas+2;
			strcpy(lab1,"Fichas comidas por ");
			strcat(lab1 ,Inicio->Jugador1->nombre);
			sprintf(aux,"%d",Inicio->Jugador1->comidas);
			strcat(lab1, aux);
			gtk_label_set_text (GTK_LABEL(Inicio->label1), lab1);
		      }
		      else{
			Inicio->Jugador2->comidas=Inicio->Jugador2->comidas+2;
			strcpy(lab2,"Fichas comidas por ");
			strcat(lab2 ,Inicio->Jugador2->nombre);
			sprintf(aux,"%d",Inicio->Jugador2->comidas);
			strcat(lab2, aux);
			gtk_label_set_text (GTK_LABEL(Inicio->label2), lab2);
		      }
	        
		      
		      Inicio->tablero[x][y+1]=0;
		      
		      Inicio->tablero[x][y+2]=0;
		    }
		}
	    }
	}
    }



    //valida abajo
  if(y>2)
    {
      if(Inicio->tablero[x][y]==j)
	{
        
	  if(Inicio->tablero[x][y-1]!=0  && Inicio->tablero[x][y-1]!=j)
	    {
	   
	      if(Inicio->tablero[x][y-2]!=0 && Inicio->tablero[x][y-2]==j)
		{
		 
		  if(Inicio->tablero[x][y-3]==j)
		    {
		      if(j==1){
			Inicio->Jugador1->comidas=Inicio->Jugador1->comidas+2;
			strcpy(lab1,"Fichas comidas por ");
			strcat(lab1 ,Inicio->Jugador1->nombre);
			sprintf(aux,"%d",Inicio->Jugador1->comidas);
			strcat(lab1, aux);
			gtk_label_set_text (GTK_LABEL(Inicio->label1), lab1);
		      }
		      else{
			Inicio->Jugador2->comidas=Inicio->Jugador2->comidas+2;
			strcpy(lab2,"Fichas comidas por ");
			strcat(lab2 ,Inicio->Jugador2->nombre);
			sprintf(aux,"%d",Inicio->Jugador2->comidas);
			strcat(lab2, aux);
			gtk_label_set_text (GTK_LABEL(Inicio->label2), lab2);
		      }
	        
		      
		      Inicio->tablero[x][y-1]=0;
		      
		      Inicio->tablero[x][y-2]=0;
		    }
		}
	    }
	}
    }
  
  //valida diagonal abajo izquierda
  if(x>2 && y<=17)
    {
      if(Inicio->tablero[x][y]==j)
	{
	   
	  
	  if(Inicio->tablero[x-1][y+1]!=0 && Inicio->tablero[x-1][y+1]!=j)
	    {
	    
	      if(Inicio->tablero[x-2][y+2]!=0 && Inicio->tablero[x-2][y+2]!=j)
		{
        
		  if(Inicio->tablero[x-3][y+3]==j)
		    {
		      if (j==1){
			Inicio->Jugador1->comidas=Inicio->Jugador1->comidas+2;
			strcpy(lab1,"Fichas comidas por ");
			strcat(lab1 ,Inicio->Jugador1->nombre);
			sprintf(aux,"%d",Inicio->Jugador1->comidas);
			strcat(lab1, aux);
			gtk_label_set_text (GTK_LABEL(Inicio->label1), lab1);
		      }
		      else{
			Inicio->Jugador2->comidas=Inicio->Jugador2->comidas+2;
			strcpy(lab2,"Fichas comidas por ");
			strcat(lab2 ,Inicio->Jugador2->nombre);
			sprintf(aux,"%d",Inicio->Jugador2->comidas);
			strcat(lab2, aux);
			gtk_label_set_text (GTK_LABEL(Inicio->label2), lab2);
		      }
        
		      
		      Inicio->tablero[x-1][y+1]=0;
		      
		      Inicio->tablero[x-2][y+2]=0;
		    }
		}
	    }
	}
    }



  //valida diagonal arriba izquierda
  if(x>2 && y>2)
    {
      if(Inicio->tablero[x][y]==j)
	{
	   
	  
	  if(Inicio->tablero[x-1][y-1]!=0 && Inicio->tablero[x-1][y-1]!=j)
	    {
	    
	      if(Inicio->tablero[x-2][y-2]!=0 && Inicio->tablero[x-2][y-2]!=j)
		{
        
		  if(Inicio->tablero[x-3][y-3]==j)
		    {
		      if (j==1){
			Inicio->Jugador1->comidas=Inicio->Jugador1->comidas+2;
			strcpy(lab1,"Fichas comidas por ");
			strcat(lab1 ,Inicio->Jugador1->nombre);
			sprintf(aux,"%d",Inicio->Jugador1->comidas);
			strcat(lab1, aux);
			gtk_label_set_text (GTK_LABEL(Inicio->label1), lab1);
		      }
		      else{
			Inicio->Jugador2->comidas=Inicio->Jugador2->comidas+2;
			strcpy(lab2,"Fichas comidas por ");
			strcat(lab2 ,Inicio->Jugador2->nombre);
			sprintf(aux,"%d",Inicio->Jugador2->comidas);
			strcat(lab2, aux);
			gtk_label_set_text (GTK_LABEL(Inicio->label2), lab2);
		      }
        
		      
		      Inicio->tablero[x-1][y-1]=0;
		      
		      Inicio->tablero[x-2][y-2]=0;
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



/**
*  Esta función valida si hubo filas de 5. Si si, llama a la funcion de
*  Ganador. Tambien, cada vez que se tira una ficha, recorre todo el tablero 
*  para contar el numero de fichas de 4 de jugador que tiro. y lo guarda en 
*  la memoria.
*  @author Mateo Larralde y Mariana.
*  @param 
*  @param data   Inicio
*  @return 
*/




void FilasDe4(int x,int y,gpointer data)
{
  int i=0,j=0; //variables del tablero
  //jug será el jugador en turno
  int cont=0;
  int com1;
  int a,b;
  char jug;
  GtkWidget *button;
  Lista *Inicio=(Lista *)data;
  
  com1=0;


  if(Inicio->turno %2 == 1)
    jug=2;
  if (Inicio->turno %2 ==0)
    jug=1;

  
    while(i<20){
      a=i;
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
	cont=0;
	j++;
      }
      i=a+1;
    }
    
  
    //valida diagonal derecha

    i=0;
    j=0;
    while(i<20){
      a=i;
      while(j<20){
	b=j;
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
	cont=0;
	j=b+1;
      }
      i=a+1;
    }
  
    //valida abajo

    i=0;
    j=0;
    while(i<20){
      while(j<20){
	b=j;

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
	cont=0;
	j=b+1;
      }
      i++;
    }
  
  //valida diagonal derecha abajo

    i=3;
    j=0;
    
    while(i<20){
      a=i;
      while(j<20){
	b=j;
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
	cont=0;
	j=b+1;
      }
      i=a+1;
    }
    
  
    if(jug==1)
      Inicio->Jugador1->fila4=com1;
    if(jug==2)
      Inicio->Jugador2->fila4=com1;
  
  if(com1>4)
    Ganador(button, Inicio);
  
}



/**
*  Esta función recibe el nombre del archivo donde se va a guardar el
*  juego y crea un archivo de texto en donde se imprimen los nombres
*  de los jugadores, y luego las coordenadas de cada tiro en orden.
*  @author Mateo Larralde 
*  @param widget GtkWidget
*  @param data   Inicio
*  @return 
*/
 
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
  temp= Inicio->turnos_l;
  
  while (temp !=NULL){
    fprintf(Archivo,"%d", temp->X);
    fprintf(Archivo,"%d", temp->Y);
    temp=temp->sig;
  }

  fclose(Archivo);
}

/**
*  Al cumplirse alguna de las condiciones para ganar el juego, se
*  llama a esta funcion que crea una ventana donde se anuncia al
*  ganador. Aquí termina el juego
*  @author Mateo Larralde
*  @param widget GtkWidget
*  @param data   Inicio
*  @return 
*/

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
  
  if(Inicio->turno%2==0)
    strcat(text,Inicio->Jugador1->nombre);

  if(Inicio->turno%2==1)
    strcat(text,Inicio->Jugador2->nombre);
  
  
  
  label = gtk_label_new (text);


  verticalbox = gtk_vbox_new(TRUE,5);
  gtk_box_pack_start(GTK_BOX(verticalbox),label,TRUE,TRUE,5);
  gtk_container_add(GTK_CONTAINER(ganador),verticalbox);

  gtk_signal_connect(GTK_OBJECT(ganador),"destroy",GTK_SIGNAL_FUNC(StopTheApp),NULL);
  gtk_widget_show_all(ganador);


}

/**
*  Esta función se llama al apretar el boton de guardar, y despliega una
*  ventana que pregunta el nombre del archivo donde se va a guardar 
*  el juego.
*  @author Mateo Larralde
*  @param widget GtkWidget
*  @param data   Inicio
*  @return 
*/


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
