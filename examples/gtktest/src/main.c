/**
 *---------------------------------------------------------------------------
 * @brief    Gtktest main file.
 *
 * @file     main.c
 * @author   Your Name <your.name@yourdomain.org>
 * @date     2017-10-30
 * @license  BSD
 *
 *---------------------------------------------------------------------------
 *
 *
 */


// Includes -----------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>

#include <gtk/gtk.h>

#include "main.h"

// Macros -------------------------------------------------------------------

//G_DEFINE_TYPE(ExampleAppWindow, example_app_window, GTK_TYPE_APPLICATION_WINDOW);
//G_DEFINE_TYPE(ExampleApp, example_app, GTK_TYPE_APPLICATION);
// Variables ----------------------------------------------------------------


// Prototypes ---------------------------------------------------------------

void sigint(int sig);
void sighup(int sig);

// Code ---------------------------------------------------------------------

void sigint(int sig) {

}

void sighup(int sig) {

}


static void print_hello (GtkWidget *widget, gpointer   data) {
    g_print ("Hello World\n");
}

static void activate (GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *button_box;

    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Window");
    gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

    button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
    gtk_container_add (GTK_CONTAINER (window), button_box);

    button = gtk_button_new_with_label ("Hello World");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
    gtk_container_add (GTK_CONTAINER (button_box), button);

    gtk_widget_show_all (window);
}




int main (int    argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;
}
