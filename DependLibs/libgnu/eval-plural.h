/* Plural expression evaluation.
   Copyright (C) 2000-2003, 2007, 2015-2016 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published by
   the Free Software Foundation; either version 2.1 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#ifndef STATIC
#define STATIC static
#endif

#ifndef internal_function
# define internal_function
#endif

/* Evaluate the plural expression and return an index value.  */

unsigned long plural_eval (const struct expression *pexp, unsigned long int n);
