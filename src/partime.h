/* Parse a string, yielding a struct partime that describes it.  */

/* Copyright (C) 1993, 1994, 1995, 1997, 2003, 2006 Paul Eggert
   Distributed under license by the Free Software Foundation, Inc.
   Copyright (C) 2010 Free Software Foundation, Inc..

   This file is also part of RCS.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include <limits.h>
#include <time.h>

#define TM_UNDEFINED (-1)
#define TM_DEFINED(x) (0 <= (x))

#define TM_LOCAL_ZONE LONG_MIN
#define TM_UNDEFINED_ZONE (LONG_MIN + 1)

struct partime
  {
    /* This structure describes the parsed time.
       Only the following tm_* members are used:
		sec, min, hour, mday, mon, year, wday, yday.
       If ! TM_DEFINED (value), the parser never found the value.
       The tm_year field is the actual year, not the year - 1900;
       but see ymodulus below.  */
    struct tm tm;

    /* Like tm, but values are relative to the value in tm,
       and values are initialized to 0 rather than to TM_UNDEFINED.
       Only the following tm_* members are used:
		sec, min, hour, mday, mon, year.  */
    struct tm tmr;

    /* If TM_DEFINED (wday_ordinal),
       then day number (e.g. 3 in "3rd Sunday").  */
    int wday_ordinal;

    /* If TM_DEFINED (ymodulus),
       then tm.tm_year is actually modulo ymodulus.  */
    int ymodulus;

    /* Week of year, ISO 8601 style.
       If ! TM_DEFINED (yweek), the parser never found yweek.
       Weeks start on Mondays.
       Week 1 includes Jan 4.  */
    int yweek;

    /* Seconds east of UTC; or TM_LOCAL_ZONE or TM_UNDEFINED_ZONE.  */
    long zone;
  };

char *partime (char const *, struct partime *);
char *parzone (char const *, long *);
