#include <gtk/gtk.h>
#include <stdio.h>

#include "core.h"

/* Pointer to the embedded copy of src/gui.glade which holds our
   GUI in XML format: */
extern const gchar _binary_gui_glade_start[];

GtkBuilder *gtk_b = NULL;

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

	const gchar *profile_name = gtk_combo_box_get_active_id(
		(GtkComboBox *) gtk_builder_get_object(gtk_b,
		    "profile_combobox"));

	if (!profile_name || !strlen(profile_name)) {
		fprintf(stderr, "profile not specified\n");
		return;
	}
	printf("profile text: %s\n", profile_name);

	const gchar *username = gtk_entry_get_text(
		(GtkEntry *) gtk_builder_get_object(gtk_b, "username"));
	if (!username || !strlen(username)) {
		fprintf(stderr, "username not specified\n");
		return;
	}

	const gchar *passphrase = gtk_entry_get_text(
		(GtkEntry *) gtk_builder_get_object(gtk_b, "passphrase"));
	const gchar *passphrase_repeated = gtk_entry_get_text(
		(GtkEntry *) gtk_builder_get_object(gtk_b,
		    "passphrase_repeated"));
	const char *err_msg =
	    passphrase_is_invalid(passphrase, passphrase_repeated);
	if (err_msg) {
		fprintf(stderr, "passphrase(s): %s", err_msg);
		return;
	}

	printf("passphrase ok\n");
	gboolean ssh_output = gtk_toggle_button_get_active(
		(GtkToggleButton *)gtk_builder_get_object(gtk_b, "ssh_toggle"));
	gboolean pgp_output = gtk_toggle_button_get_active(
		(GtkToggleButton *)gtk_builder_get_object(gtk_b, "pgp_toggle"));
	printf("ssh: %d, pgp: %d\n", ssh_output, pgp_output);

	const gchar *output_directory = gtk_file_chooser_get_filename(
		(GtkFileChooser *) gtk_builder_get_object(gtk_b,
		    "output_directory"));

	if (NULL == output_directory || !strlen(output_directory)) {
		/* TODO display help message */
		fprintf(stderr, "output directory not specified\n");
		return;
	}
	printf("output dir: %s\n", output_directory);

	fprintf(stderr, "Generating...");

	struct profile_t *profile =
	    generate_profile(profile_name, username, passphrase);

	if (!output_profiles(profile, output_directory,
		ssh_output, pgp_output)) {
		fprintf(stderr, "Failed to generate\n");
	} else {
		fprintf(stderr, "Generated successfully!\n");
	}

	free_profile_t(profile);
}

int
main(int argc, char *argv[])
{
	/* initialize GTK */

	gtk_init(&argc, &argv);

	gtk_b = gtk_builder_new();
	gtk_builder_add_from_string(gtk_b, _binary_gui_glade_start,
	    /* use strlen() instead of _binary_gui_glade_size because
	       the latter is broken when ASLR is used: */
	    strlen(_binary_gui_glade_start), NULL);
	GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(gtk_b,
		"main_window"));
	gtk_builder_connect_signals(gtk_b, NULL);
	/* commented out because we need it to look up objects:
	   g_object_unref(G_OBJECT(gtkBuilder)); */

	/* Quitting main window kills us: */
	g_signal_connect(G_OBJECT(window), "destroy",
	    G_CALLBACK(on_destroy), NULL);

	pi_init();

	/* Show main window and enter event loop: */
	gtk_widget_show(window);

	gtk_main();

	return 0;
}
