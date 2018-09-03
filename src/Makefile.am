bin_PROGRAMS = passphrase-identity

if ENABLE_GUI
bin_PROGRAMS += passphrase-identity-gui
endif

common_files = \
	core.c core.h \
	buffer.c buffer.h \
	buffer_writer.c  buffer_writer.h \
	memory.c memory.h \
	openssh.c openssh.h \
	sha1.c sha.h sha-private.h \
	openpgp.c openpgp.h \
	profile.c profile.h

passphrase_identity_CFLAGS = @PASSPHRASE_IDENTITY_CFLAGS@ @SODIUM_CFLAGS@
passphrase_identity_LDFLAGS = @SODIUM_LIBS@

passphrase_identity_SOURCES = \
	$(common_files) \
	main.c \
	readpassphrase.c readpassphrase.h

passphrase_identity_gui_CFLAGS = @PASSPHRASE_IDENTITY_CFLAGS@ @SODIUM_CFLAGS@ @GTK_CFLAGS@ -rdynamic
passphrase_identity_gui_LDFLAGS = @SODIUM_LIBS@ @GTK_LIBS@
passphrase_identity_gui_SOURCES = \
	$(common_files) \
	main-gui.c
