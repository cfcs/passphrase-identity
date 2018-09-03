#include "core.h"

int
pi_init(void)
{
	/* Initialize base64 encoder and decoder. */
	buffer_init();

	if (sodium_init() == -1)
	{
		fprintf(stderr, "Error: Unable to initialize libsodium ...\n");
		return (EXIT_FAILURE);
	}

	return (0);

}

const char *
passphrase_is_invalid(const char *passphrase, const char *passphrase_verify)
{
	if (!passphrase || !passphrase_verify) {
		return ("Error: Both passphrase and passphrase verification "
		    "must be specified");
	}

	if (0 != strcmp(passphrase, passphrase_verify)) {
		return ("Error: Passphrases do not match.\n");
	}

	if (strlen(passphrase) < 12) {
		return ("Error: Provided passphrase is shorter than 12 "
		    "characters.\n");
	}

	return (NULL);
}

/*
 * TODO load directly into agents:
 * ssh-add -c -k -
 *
 */

bool
output_profiles(struct profile_t *profile, const char *output_directory,
    bool ssh_output, bool gpg_output)
{
	bool success = true;

	if (ssh_output) {
		if (generate_openssh_keypair(profile)) {
			printf("Successfully generated SSH key pair ...\n");
			// TODO check return val of this or make it a void(*)(..)
			openssh_write(output_directory, profile->username,
			    strlen(profile->username),
			    (unsigned char *) &(profile->openssh_secret),
			    (unsigned char *) &(profile->openssh_public));
		} else {
			fprintf(stderr, "Error: Unable to generate SSH key pair ...\n");
			success = false;
		}
	}

	if (gpg_output) {
		if (generate_openpgp_keypair(profile)) {
			printf("Successfully generated OpenPGP key pair ...\n");
			if (openpgp_write(output_directory, profile)) {
				printf("Successfully wrote OpenPGP key pair to disk.\n");
			} else {
				fprintf(stderr, "Failed to write OpenPGP key pair to disk...\n");
				success = false;
			}
		} else {
			fprintf(stderr, "Error: Unable to generate GPG key pair ...\n");
			success = false;
		}
	}

	return success;
}
