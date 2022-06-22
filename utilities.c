// SPDX-License-Identifier: LGPL-2.1-or-later

#include <errno.h>
#include <locale.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "libad9166-iio-config.h"
#include "utilities.h"

#if defined(_WIN32) || \
		(defined(__APPLE__) && defined(__MACH__)) || \
		(defined(__USE_XOPEN2K8) && \
		(!defined(__UCLIBC__) || defined(__UCLIBC_HAS_LOCALE__)))
#define LOCALE_SUPPORT
#endif

#ifdef LOCALE_SUPPORT
#if defined(__MINGW32__) || (!defined(_WIN32) && !defined(HAS_NEWLOCALE))
static int read_double_locale(const char *str, double *val)
{
	char *end, *old_locale;
	double value;
	bool problem = false;

	/* XXX: This is not thread-safe, but it's the only way we have to
	 * support locales under MinGW without linking with Visual Studio
	 * libraries. */
	old_locale = util_strdup(setlocale(LC_NUMERIC, NULL));
	if (!old_locale)
		return -ENOMEM;

	setlocale(LC_NUMERIC, "C");

	errno = 0;
	value = strtod(str, &end);
	if (end == str || errno == ERANGE)
		problem = true;

	setlocale(LC_NUMERIC, old_locale);
	free(old_locale);

	if (problem)
		return -EINVAL;

	*val = value;
	return 0;
}
#elif defined(_WIN32)
static int read_double_locale(const char *str, double *val)
{
	char *end;
	double value;
	bool problem = false;

	_locale_t locale = _create_locale(LC_NUMERIC, "C");
	if (!locale)
		return -ENOMEM;

	errno = 0;
	value = _strtod_l(str, &end, locale);
	if (end == str || errno == ERANGE)
		problem = true;

	_free_locale(locale);

	if (problem)
		return -EINVAL;

	*val = value;
	return 0;
}
#else
static int read_double_locale(const char *str, double *val)
{
	char *end;
	double value;
	bool problem = false;
	locale_t old_locale, new_locale;

	new_locale = newlocale(LC_NUMERIC_MASK, "C", (locale_t) 0);
	if (!new_locale)
		return -errno;

	old_locale = uselocale(new_locale);

	errno = 0;
	value = strtod(str, &end);
	if (end == str || errno == ERANGE)
		problem = true;

	uselocale(old_locale);
	freelocale(new_locale);

	if (problem)
		return -EINVAL;

	*val = value;
	return 0;
}
#endif
#endif

int util_read_double(const char *str, double *val)
{
#ifdef LOCALE_SUPPORT
	return read_double_locale(str, val);
#else
	char *end;
	double value;

	errno = 0;
	value = strtod(str, &end);
	if (end == str || errno == ERANGE)
		return -EINVAL;

	*val = value;
	return 0;
#endif
}

char *util_strdup(const char *str)
{
#if defined(_WIN32)
	return _strdup(str);
#elif defined(HAS_STRDUP)
	return strdup(str);
#else
	size_t len = strlen(str);
	char *buf = malloc(len + 1);

	if (buf)
		memcpy(buf, str, len + 1);
	return buf;
#endif
}
