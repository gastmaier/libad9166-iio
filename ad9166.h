/*
 * Copyright (C) 2022 Analog Devices, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 */

 /** @file ad9166.h
  * @brief Public interface */

#ifndef __AD9166_H__
#define __AD9166_H__

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @defgroup FLAGS MCS Flags
 *
 * @{
 */
/** @} */

#ifdef _WIN32
#   ifdef LIBAD9166_EXPORTS
#	define __api __declspec(dllexport)
#   else
#	define __api __declspec(dllimport)
#   endif
#elif __GNUC__ >= 4 && !defined(MATLAB_MEX_FILE) && !defined(MATLAB_LOADLIBRARY)
#   define __api __attribute__((visibility ("default")))
#else
#   define __api
#endif

struct iio_context;
struct iio_device;

/* ---------------------------------------------------------------------------*/
/* ------------------------- Top-level functions -----------------------------*/
/** @defgroup TopLevel Top-level functions
 * @{ */


/** @} */

#ifdef __cplusplus
}
#endif

#undef __api

#endif /* __AD9166_H__ */
