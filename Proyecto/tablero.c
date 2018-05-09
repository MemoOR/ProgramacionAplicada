#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>

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
  char archivo[20];
  
}Lista;


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

GtkWidget *create_pad() {
  char *options[20][20];

  for(int i=0;i<20;i++)
    for(int j=0;j<20;j++)
      options[i][j]=0;

  GtkWidget *container;
  GtkWidget *row, *button;

  container = gtk_vbox_new(FALSE, 3);
  
  for (int i = 0; i < 20; i++) {
    
    row = gtk_hbox_new(TRUE, 0);
    gtk_box_pack_start(GTK_BOX(container), row, FALSE, TRUE, 0);
    
    for(int j = 0; j < 20; j++){
   
      button = gtk_button_new_with_label(options[i][j]);
      
      gtk_widget_set_size_request(button, 35, 35);
      g_signal_connect(button, "clicked", G_CALLBACK(callback), NULL);
      
      gtk_box_pack_start(GTK_BOX(row), button, FALSE, TRUE, 2);
      gtk_widget_show(button);
    }
  }
  return container;
}

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
