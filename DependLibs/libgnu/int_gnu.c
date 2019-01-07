/*
 * Copyright (C) 2002-2014 Free Software Foundation, Inc.
 *
 * This file is part of LIBTASN1.
 *
 * The LIBTASN1 library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA
 */


#include "int_gnu.h"

/****************************************/
/* Returns the first 8 bits.            */
/* Used with the field type of asn1_node_st */
/****************************************/
unsigned int type_field (unsigned int ntype)
{
  return (ntype & 0xff);
}

/* To convert old types from a static structure */
unsigned int convert_old_type (unsigned int ntype)
{
  unsigned int type = ntype & 0xff;
  if (type == ASN1_ETYPE_TIME)
    {
      if (ntype & CONST_UTC)
	type = ASN1_ETYPE_UTC_TIME;
      else
	type = ASN1_ETYPE_GENERALIZED_TIME;

      ntype &= ~(CONST_UTC | CONST_GENERALIZED);
      ntype &= 0xffffff00;
      ntype |= type;

      return ntype;
    }
  else
    return ntype;
}

void *_asn1_realloc(void *ptr, size_t size)
{
  void *ret;

  if (size == 0)
    return ptr;

  ret = realloc(ptr, size);
  if (ret == NULL)
    {
      free(ptr);
    }
  return ret;
}


