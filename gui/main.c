#include <gtk/gtk.h>
#include <stdio.h>

static void on_destroy(GtkWidget *_widget, gpointer _data);
static void
on_destroy(GtkWidget *widget, gpointer data)
{
	gtk_main_quit();
}

void on_generate_clicked(void *_widget, gpointer _data);
void
on_generate_clicked(void *widget, gpointer data)
{
	printf("Generate! clicked\n");
}

int
main(int argc, char *argv[])
{
	/* initialize GTK */

	gtk_init(&argc, &argv);

	GtkBuilder *gtkBuilder = gtk_builder_new();
	gtk_builder_add_from_file(gtkBuilder, "gui.glade", NULL);
	GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(gtkBuilder,
		"main_window"));
	gtk_builder_connect_signals(gtkBuilder, NULL);
	g_object_unref(G_OBJECT(gtkBuilder));

	/* Quitting main window kills us: */
	g_signal_connect(G_OBJECT(window), "destroy",
	    G_CALLBACK(on_destroy), NULL);

	/* Show main window and enter event loop: */
	gtk_widget_show(window);
	gtk_main();

	return 0;
}
