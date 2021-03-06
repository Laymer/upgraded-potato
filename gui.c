//
// Created by laymer on 1/5/22.
// source :
// https://docs.gtk.org/gtk4/getting_started.html
//
#include <stdio.h>
#include "gui.h"
#include <gtk/gtk.h>

static void
print_hello (GtkWidget *widget, gpointer   data) {
	g_print ("Hello World\n");
}

static void activate (GtkApplication* app, gpointer user_data) {
	GtkWidget *window;
	GtkWidget *button;
	GtkWidget *box;

	window = gtk_application_window_new (app);
	gtk_window_set_title (GTK_WINDOW (window), "Window");
	gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

	box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_set_halign (box, GTK_ALIGN_CENTER);
	gtk_widget_set_valign (box, GTK_ALIGN_CENTER);

	gtk_window_set_child (GTK_WINDOW (window), box);

	button = gtk_button_new_with_label ("Hello World");

	g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
	g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_window_destroy), window);

	gtk_box_append (GTK_BOX (box), button);

	gtk_widget_show (window);
}

void init_interface(int argc, char ** argv){

	GtkApplication *app;
	int status;

	app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
	status = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);

    printf("Done.\n");
	printf("Status : %d\n", status);
}

int main(int argc, char *argv[])
{
	printf("Hi :)\n");

	init_interface(argc, argv);
}