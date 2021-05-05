#include <gtk/gtk.h>

static void button_1 (GtkWidget *widget, gpointer data);
static void button_2 (GtkWidget *widget, gpointer data);

int main (int argc, char *argv[]) {
    GtkBuilder *builder;
    GObject *window;
    GObject *button;
    GError *error = NULL;

    gtk_init (&argc, &argv);

    builder = gtk_builder_new ();
    if (gtk_builder_add_from_file (builder, "src/builder.ui", &error) == 0) {
        g_printerr ("error loading file: %s\n", error->message);
        g_clear_error (&error);
        return 1;
    }

    window = gtk_builder_get_object (builder, "window");
    g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

    button = gtk_builder_get_object (builder, "button1");
    g_signal_connect (button, "clicked", G_CALLBACK (button_1), NULL);

    button = gtk_builder_get_object (builder, "button2");
    g_signal_connect (button, "clicked", G_CALLBACK (button_2), NULL);

    button = gtk_builder_get_object (builder, "quit");
    g_signal_connect (button, "clicked", G_CALLBACK (gtk_main_quit), NULL);

    gtk_main ();
    return 0;
}

static void button_1 (GtkWidget *widget, gpointer data) {
    g_print ("i'm button 1\n");
}
static void button_2 (GtkWidget *widget, gpointer data) {
    g_print ("i'm button 2\n");
}
