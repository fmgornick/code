#include <gtk/gtk.h>

static void activate (GtkApplication *app, gpointer user_data);
static void button_1_print (GtkWidget *widget, gpointer data);
static void button_2_print (GtkWidget *widget, gpointer data);

int main (int argc, char *argv[]) {
    GtkApplication *app;
    int status;

    // create application
    app = gtk_application_new ("com.github.fmgornick.logic_simulator", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;
}

/* void end_program(GtkWidget *wid, gpointer ptr) { */
/*     gtk_main_quit(); */
/* } */

static void activate (GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    /* GtkWidget *button_box; */

    // create new window 
    // set window title and size
    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "logic simulator");
    gtk_window_set_default_size (GTK_WINDOW (window), 400, 400);
    g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

    // container that packs buttions
    grid = gtk_grid_new ();

    // pack container into window
    gtk_container_add (GTK_CONTAINER (window), grid);

    // create button 1
    button = gtk_button_new_with_label ("button 1");
    g_signal_connect (button, "clicked", G_CALLBACK (button_1_print), NULL);

    // place button 1 into grid cell (0,0), filling out 1 cell horizontally & vertically
    gtk_grid_attach (GTK_GRID (grid), button, 0, 0, 1, 1);

    // create button 2
    button = gtk_button_new_with_label ("button 2");
    g_signal_connect (button, "clicked", G_CALLBACK (button_2_print), NULL);

    // place button 1 into grid cell (1,0), filling out 1 cell horizontally & vertically
    gtk_grid_attach (GTK_GRID (grid), button, 1, 0, 1, 1);

    // create quit button
    button = gtk_button_new_with_label("quit");
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);

    // quit button on second row and spans 2 columns
    gtk_grid_attach (GTK_GRID (grid), button, 0, 1, 2, 1);

    // displays all widgets on the window
    gtk_widget_show_all (window);
    gtk_main ();
}

static void button_1_print (GtkWidget *widget, gpointer data) {
    g_print("i am button 1\n");
}

static void button_2_print (GtkWidget *widget, gpointer data) {
    g_print("i am button 2\n");
}
