// Copyright (c) 2015 Alexander Færøy. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef PASSPHRASE_IDENTITY_CORE_H
#define PASSPHRASE_IDENTITY_CORE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sodium.h>

#include "buffer.h"
#include "openssh.h"
#include "openpgp.h"
#include "profile.h"
#include "readpassphrase.h"
#include "memory.h"

/*
 * Call initializers for the various components we need.
 * MUST be called before anything other function defined in this header file.
 * Returns zero on success, otherwise an error code.
 */
int pi_init(void);

/*
 * Returns a pointer to a static error message string if the passphrases
 * provided do NOT match, or if they fail the complexity requirements.
 * Returns NULL on success.
 */
const char *
passphrase_is_invalid(const char *passphrase, const char *passphrase_verify);

/*
 * Writes the generated keys for [profile] to specified output_directory.
 * The flags ssh_output and gpg_output are true when the respective key types
 * should be generated.
 * Returns true on success; false if an error occured.
 */
bool output_profiles(struct profile_t *profile, const char *output_directory,
    bool ssh_output, bool gpg_output);

#endif /* PASSPHRASE_IDENTITY_CORE_H */
