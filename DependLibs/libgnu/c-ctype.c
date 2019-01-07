#include <config_libgnu.h>
#include <libgnu/c-ctype.h>

bool
c_isalnum (int c)
{
  switch (c)
    {
    _C_CTYPE_DIGIT:
    _C_CTYPE_LOWER:
    _C_CTYPE_UPPER:
      return true;
    default:
      return false;
    }
}

bool
c_isalpha (int c)
{
  switch (c)
    {
    _C_CTYPE_LOWER:
    _C_CTYPE_UPPER:
      return true;
    default:
      return false;
    }
}

/* The function isascii is not locale dependent.
   Its use in EBCDIC is questionable. */
bool
c_isascii (int c)
{
  switch (c)
    {
    case ' ':
    _C_CTYPE_CNTRL:
    _C_CTYPE_DIGIT:
    _C_CTYPE_LOWER:
    _C_CTYPE_PUNCT:
    _C_CTYPE_UPPER:
      return true;
    default:
      return false;
    }
}

bool
c_isblank (int c)
{
  return c == ' ' || c == '\t';
}

bool
c_iscntrl (int c)
{
  switch (c)
    {
    _C_CTYPE_CNTRL:
      return true;
    default:
      return false;
    }
}

bool
c_isdigit (int c)
{
  switch (c)
    {
    _C_CTYPE_DIGIT:
      return true;
    default:
      return false;
    }
}

bool
c_isgraph (int c)
{
  switch (c)
    {
    _C_CTYPE_DIGIT:
    _C_CTYPE_LOWER:
    _C_CTYPE_PUNCT:
    _C_CTYPE_UPPER:
      return true;
    default:
      return false;
    }
}

bool
c_islower (int c)
{
  switch (c)
    {
    _C_CTYPE_LOWER:
      return true;
    default:
      return false;
    }
}

bool
c_isprint (int c)
{
  switch (c)
    {
    case ' ':
    _C_CTYPE_DIGIT:
    _C_CTYPE_LOWER:
    _C_CTYPE_PUNCT:
    _C_CTYPE_UPPER:
      return true;
    default:
      return false;
    }
}

bool
c_ispunct (int c)
{
  switch (c)
    {
    _C_CTYPE_PUNCT:
      return true;
    default:
      return false;
    }
}

bool
c_isspace (int c)
{
  switch (c)
    {
    case ' ': case '\t': case '\n': case '\v': case '\f': case '\r':
      return true;
    default:
      return false;
    }
}

bool
c_isupper (int c)
{
  switch (c)
    {
    _C_CTYPE_UPPER:
      return true;
    default:
      return false;
    }
}

bool
c_isxdigit (int c)
{
  switch (c)
    {
    _C_CTYPE_DIGIT:
    _C_CTYPE_A_THRU_F:
      return true;
    default:
      return false;
    }
}

int
c_tolower (int c)
{
  switch (c)
    {
    _C_CTYPE_UPPER:
      return c - 'A' + 'a';
    default:
      return c;
    }
}

int
c_toupper (int c)
{
  switch (c)
    {
    _C_CTYPE_LOWER:
      return c - 'a' + 'A';
    default:
      return c;
    }
}

