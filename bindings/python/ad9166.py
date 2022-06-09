#!/usr/bin/env python
# SPDX-License-Identifier: LGPL-2.1-or-later
# Copyright (C) 2021 Analog Devices, Inc.
# Author: Travis F. Collins <travis.collins@analog.com>

from typing import List
import math

import iio
from iio import _ContextPtr, _DevicePtr

# Imports from package ctypes are not grouped
# pylint: disable=ungrouped-imports
#
# The way the methods and classes are used, violate this, but there
#   isn't a good way to do things otherwise
# pylint: disable=protected-access
from ctypes import (
    byref,
    c_ubyte,
    c_double,
    c_int,
    c_longlong,
    c_short,
    c_uint,
    c_ulong,
    CDLL as _cdll,
    POINTER as _POINTER,
    Structure,
)
from ctypes.util import find_library
from os import strerror as _strerror
from platform import system as _system

if "Windows" in _system():
    from ctypes import get_last_error
else:
    from ctypes import get_errno
# pylint: enable=ungrouped-imports

# ctypes requires the errcheck to take three arguments, but we don't use them
# pylint: disable=unused-argument


def _check_negative(result, func, arguments):
    if result >= 0:
        return result
    raise OSError(-result, _strerror(-result))


if "Windows" in _system():
    _libad9166 = "libad9166.dll"
else:
    # Non-windows, possibly Posix system
    _libad9166 = "ad9166"

_lib = _cdll(find_library(_libad9166), use_errno=True, use_last_error=True)
