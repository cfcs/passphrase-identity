#include <gtk/gtk.h>
#include <stdio.h>

#include "core.h"

static void on_destroy(GtkWidget *_widget, gpointer _data);
static void
on_destroy(GtkWidget *widget __attribute__((__unused__)),
    gpointer data __attribute__((__unused__)) )
{
	gtk_main_quit();
}

void on_generate_clicked(void *_widget, gpointer _data);
void
on_generate_clicked(void *widget __attribute__((__unused__)),
    gpointer data __attribute__((__unused__)))
{
	printf("Generate! clicked\n");
	const char *err_msg = passphrase_is_invalid("p1", "p2");
	if (err_msg) {
		return;
	}
/*
	struct profile_t *profile =
	    generate_profile(profile_name, username, passphrase);

	bool success =
	    output_profiles(profile, output_directory, ssh_output, gpg_output);

	free_profile_t(profile);
*/
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

	pi_init();

	/* Show main window and enter event loop: */
	gtk_widget_show(window);
	gtk_main();

	return 0;
}
