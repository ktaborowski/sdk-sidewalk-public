/*
 * Copyright (c) 2023 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#ifndef SID_CRYPTO_INTERNAL_H
#define SID_CRYPTO_INTERNAL_H

#include <psa/crypto.h>

psa_status_t prepare_key(const uint8_t *key, size_t key_length, size_t key_bits,
				psa_key_usage_t usage_flags, psa_algorithm_t alg,
				psa_key_type_t type, psa_key_handle_t *key_handle);

psa_status_t perepare_persistent_key(const uint8_t *key, size_t key_length, size_t key_bits,
			    psa_key_usage_t usage_flags, psa_algorithm_t alg, psa_key_type_t type,
			    psa_key_id_t key_id);

#endif /* SID_CRYPTO_INTERNAL_H */
