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
