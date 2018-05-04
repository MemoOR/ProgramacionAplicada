#include <gtk/gtk.h>
#include <string.h>

static gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer *data) {
  return FALSE;
}

static void destroy(GtkWidget *widget, gpointer data) {
  gtk_main_quit();
}

void command(char *label) {
  
  switch(*label){
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
    
  GtkWidget *img_r = gtk_image_new_from_file ("red.png");
  GtkWidget *img_b = gtk_image_new_from_file ("blue.png");

  GtkSettings *default_settings = gtk_settings_get_default();

  g_object_set(default_settings, "gtk-button-images", TRUE, NULL);
  
  g_object_get(G_OBJECT(widget), "label", &label, NULL);
  
  if (*label == 0){
    gtk_button_set_image (GTK_BUTTON (widget), img_b);
    command(label); 
  }
  else if (*label == 1){

  }
  g_free(label);
}

/*
  --GtkWidget *image = gtk_image_new_from_file ("red.png");
  
  --GtkWidget *button = gtk_button_new ();
  
  --gtk_button_set_image (GTK_BUTTON (button), image);
*/


GtkWidget *create_pad() {
  char *options[20][20];

  for(int i=0;i<20;i++)
    for(int j=0;j<20;j++)
      options[i][j]="";

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
  
  box1 = gtk_vbox_new(FALSE, 0);
  
  row = gtk_hbox_new(TRUE, 5);
  
  gtk_box_pack_start(GTK_BOX(box1), create_pad(), TRUE, FALSE, 0);
  
  g_signal_connect(window, "delete-event", G_CALLBACK(delete_event), NULL);
  g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL);
  
  gtk_container_add(GTK_CONTAINER(window), box1);
  
  gtk_widget_show_all(window);
  
  gtk_main();
  
  return 0;
}
