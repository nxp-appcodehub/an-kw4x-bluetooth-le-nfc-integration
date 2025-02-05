/*! *********************************************************************************
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2022 NXP
 * All rights reserved.
 *
 * \file
 *
 * SPDX-License-Identifier: BSD-3-Clause
 ********************************************************************************** */

#ifndef RNG_INTERFACE_H
#define RNG_INTERFACE_H

#include "EmbeddedTypes.h"
#include <stddef.h>

#ifndef gRngUseMutex_c
#define gRngUseMutex_c TRUE
#endif

/*! *********************************************************************************
*************************************************************************************
* Public macros
*************************************************************************************
********************************************************************************** */
#define gRngSuccess_d       (0x00U)
#define gRngInternalError_d (0x01U)
#define gRngNullPointer_d   (0x80U)
#define gRngMaxRequests_d   (100000U)

#ifndef gRngIsrPrio_c
#define gRngIsrPrio_c (0x80)
#endif

/*! *********************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
********************************************************************************** */

/*! Generic PRNG function pointer type definition. */
typedef int (*fpRngPrng_t)(void *data, unsigned char *output, size_t len);

/*! Generic RNG Entropy function pointer type definition. */
typedef int (*fpRngEntropy_t)(void *data, unsigned char *output, size_t len);

/*! *********************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
********************************************************************************** */

/*! *********************************************************************************
*************************************************************************************
* Public function prototypes
*************************************************************************************
********************************************************************************** */

#ifdef __cplusplus
extern "C" {
#endif
/*! *********************************************************************************
 * \brief  Initialize the RNG Software Module
 *         Please call SecLib_Init() before calling this function to make sure
 *         RNG hardware is correctly initialized.
 *
 * \return  Status of the RNG initialization procedure.
 *
 ********************************************************************************** */
uint8_t RNG_Init(void);

/*! *********************************************************************************
 * \brief  Read a random number from the HW RNG module.
 *
 * \param[out] pRandomNo - pointer to location where the value will be stored
 *
 * \return  status of the RNG module
 *
 ********************************************************************************** */
uint8_t RNG_HwGetRandomNo(uint32_t *pRandomNo);

/*! *********************************************************************************
 * \brief  Generates a 32-bit statistically random number
 *         No random number will be generated if the RNG was not initialized
 *         or an error occurs.
 *
 * \param[out]  pRandomNo  Pointer to location where the value will be stored
 *
 ********************************************************************************** */
void RNG_GetRandomNo(uint32_t *pRandomNo);

/*! *********************************************************************************
 * \brief  Initialize seed for the PRNG algorithm.
 *         If this function is called again, even with a NULL argument,
 *         the PRNG will be reseeded.
 *
 * \param[in]  pSeed  Ignored - please set to NULL
 *             This parameter is ignored because it is no longer needed.
 *             The PRNG is automatically seeded from the true random source.
 *
 ********************************************************************************** */
void RNG_SetPseudoRandomNoSeed(uint8_t *pSeed);

/*! *********************************************************************************
 * \brief  Generates an 256 bit (or 160 bit) pseudo-random number. The PRNG algorithm used
 *         depends on the platform's cryptographic hardware and software capabilities.
 *         Please check the implementation and/or the output of this function at runtime
 *         to see how many bytes does the PRNG produce (depending on the implementation).
 *
 * \param[out]  pOut  Pointer to the output buffer (max 32 bytes or max 20 bytes)
 * \param[in]   outBytes  The number of bytes to be copied (1-32 or 1-20 depending on the implementation)
 * \param[in]   pSeed  Ignored - please set to NULL
 *              This parameter is ignored because it is no longer needed.
 *              The PRNG is automatically seeded from the true random source.
 *              The length of the seed if present is 32 bytes or 20 bytes (depending on the implementation).
 *
 * \return  The number of bytes copied OR
 *          -1 if reseed is needed OR
 *          0 if he PRNG was not initialized or 0 bytes were requested or an error occurred
 *
 ********************************************************************************** */
int16_t RNG_GetPseudoRandomNo(uint8_t *pOut, uint8_t outBytes, uint8_t *pSeed);

/*! *********************************************************************************
 * \brief  Generates a random number. The RNG algorithm used depends on the platform's
 *         cryptographic hardware and software capabilities.
 *         Please check the implementation and/or the output of this function at runtime
 *         to see how many bytes does the PRNG produce (depending on the implementation).
 *
 * \param[out]  ctx_data
 * \param[out]  output   Pointer to the output buffer (max 32 bytes or max 20 bytes)
 * \param[in]   len      size of the numer that we want to generate
 *
 * \return  int random number
 *
 ********************************************************************************** */
int PRNG_GetRandomData(void *ctx_data, unsigned char *output, size_t len);

/*! *********************************************************************************
 * \brief  Returns a pointer to the general PRNG function
 *         Call RNG_SetPseudoRandomNoSeed() before calling this function.
 *
 * \return  Function pointer to the general PRNG function or NULL if it
 *          was not seeded.
 *
 ********************************************************************************** */
fpRngPrng_t RNG_GetPrngFunc(void);

/*! *********************************************************************************
 * \brief  Returns a pointer to the general PRNG context
 *         Call RNG_SetPseudoRandomNoSeed() before calling this function.
 *
 * \return  Function pointer to the general PRNG context or NULL if it
 *          was not initialized correctly.
 *
 ********************************************************************************** */
void *RNG_GetPrngContext(void);

#ifdef __cplusplus
}
#endif
#endif /* RNG_INTERFACE_H */
