/* Windows support code for Mairix.  */

#include <libgnu/config_libgnu.h>
#ifdef TARGET_OS_WINDOWS

#include "mman_w32.h"

#include "djgpp/djpwd.h"
#include <sys/mman.h>
#include <sys/utsname.h>

#include <io.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define LODWORD(l)   ((DWORD)((DWORDLONG)(l)))
#define HIDWORD(l)   ((DWORD)(((DWORDLONG)(l)>>32)&0xFFFFFFFF))

int uname (struct utsname *u)
{
  if (u)
    {
      DWORD packed_version, major, minor, build;
      char *plev = getenv ("PROCESSOR_LEVEL");
      DWORD nodename_size;

      /* FIXME: The CPU stuff is only correct for 32-bit machines.  */

      /* sysname[] */
      strcpy (u->sysname, "MinGW32");

      /* release[] and version[] */
      packed_version = GetVersion();
      major = (DWORD)(LOBYTE (LOWORD (packed_version)));
      minor = (DWORD)(HIBYTE (LOWORD (packed_version)));
      snprintf (u->release, sizeof(u->release), "%lu.%lu", major, minor);

      if (packed_version < 0x80000000)
        build = (DWORD)(HIWORD (packed_version));
      else
	build = 0;
      snprintf (u->version, sizeof(u->version), "%lu", build);

      /* machine[] */
      strcpy (u->machine, "i686-pc");
      if (plev)
	{
	  if (strcmp (plev, "15") == 0)
	    u->machine[1] = '7'; /* Pentium 4 */
	  else
	    u->machine[1] = plev[0];
	}

      /* nodename[] */
      nodename_size = 256;
      if (!GetComputerName (u->nodename, &nodename_size))
	strcpy (u->nodename, "unknown");

      return 0;
    }
  return -1;
}

struct passwd * getpwuid (int uid)
{
  static struct passwd pwentry;
  char *homedir = getenv("HOME");

  if (!homedir)
    homedir = getenv("USERPROFILE");

  pwentry.pw_name = getenv("USERNAME");
  pwentry.pw_dir = homedir;
  pwentry.pw_passwd = "";
  pwentry.pw_uid = pwentry.pw_gid = 42;
  pwentry.pw_shell = getenv("COMSPEC");

  return &pwentry;
}

//pid_t
//getuid (void)
//{
//  return 42;
//}

int
fname_cmp (const char *fn1, const char *fn2)
{
  char name1[MAX_PATH], name2[MAX_PATH];
  char n1[MAX_PATH], n2[MAX_PATH];
  char *p;

  if (stricmp(fn1, fn2) == 0)
    return 0;
  strcpy(n1, fn1);
  strcpy(n2, fn2);
  for (p = n1; *p; p++)
    if (*p == '/')
      *p = '\\';
  for (p = n2; *p; p++)
    if (*p == '/')
      *p = '\\';
  if (GetFullPathName(n1, MAX_PATH, name1, NULL)
      && GetFullPathName(n2, MAX_PATH, name2, NULL))
    {
      if (stricmp(name1, name2) == 0)
	return 0;
      if (GetShortPathName(name1, n1, MAX_PATH)
	  && GetShortPathName(name2, n2, MAX_PATH)
	  && stricmp(name1, name2) == 0)
	return 0;
    }
  if (GetShortPathName(n1, name1, MAX_PATH)
      && GetShortPathName(n2, name2, MAX_PATH)
      && stricmp(name1, name2) == 0)
    return 0;

  return stricmp(n1, n2);
}

int
link (const char *oldname, const char *newname)
{
  if (!CreateHardLink(newname, oldname, NULL)) {
    errno = EACCES;
    return -1;
  }
  return 0;
}

/* The mmap/munmap implementation was shamelessly stolen, with minimal
   changes, from libgwc32, a Windows port of glibc.  */

static DWORD granularity = 0;
static int isw9x = -1;

void *
mmap (void *addr, size_t len, int prot, int flags, int fd, uint64_t offset)
{
  void *map = NULL;
  char *gran_addr = addr;
  HANDLE handle = INVALID_HANDLE_VALUE;
  DWORD cfm_flags = 0, mvf_flags = 0, sysgran;
  off_t gran_offset = offset, filelen = _filelength(fd);
  off_t mmlen = len;

  if (!granularity)
    {
      SYSTEM_INFO si;

      GetSystemInfo (&si);
      granularity = si.dwAllocationGranularity;
    }
  sysgran = granularity;

  switch (prot) {
    case PROT_READ | PROT_WRITE | PROT_EXEC:
    case PROT_WRITE | PROT_EXEC:
      cfm_flags = PAGE_EXECUTE_READWRITE;
      mvf_flags = FILE_MAP_ALL_ACCESS;
      break;
    case PROT_READ | PROT_WRITE:
      cfm_flags = PAGE_READWRITE;
      mvf_flags = FILE_MAP_ALL_ACCESS;
      break;
    case PROT_WRITE:
      cfm_flags = PAGE_READWRITE;
      mvf_flags = FILE_MAP_WRITE;
      break;
    case PROT_READ:
      cfm_flags = PAGE_READONLY;
      mvf_flags = FILE_MAP_READ;
      break;
    case PROT_NONE:
      cfm_flags = PAGE_NOACCESS;
      mvf_flags = FILE_MAP_READ;
      break;
    case PROT_EXEC:
      cfm_flags = PAGE_EXECUTE;
      mvf_flags = FILE_MAP_READ;
      break;
  }
  if (flags & MAP_PRIVATE)
    {
      if (isw9x == -1)
	isw9x = ((DWORD)(LOBYTE (LOWORD (GetVersion()))) < 5);
      if (isw9x == 1)
	cfm_flags = PAGE_WRITECOPY;
      mvf_flags = FILE_MAP_COPY;
    }
  if (flags & MAP_FIXED)
    {
      gran_offset = offset;
      gran_addr = addr;
    }
  else
    {
      gran_offset = offset & ~(sysgran - 1);
      gran_addr = (char *) (((DWORD) gran_addr / sysgran) * sysgran);
    }
  mmlen = (filelen < gran_offset + len ? filelen - gran_offset : len);

  handle = CreateFileMapping ((HANDLE) _get_osfhandle(fd), NULL, cfm_flags,
			      0, mmlen, NULL);
  if (!handle)
    {
      errno = EINVAL;	/* FIXME */
      return MAP_FAILED;
    }
  map = MapViewOfFileEx (handle, mvf_flags, HIDWORD(gran_offset),
			 LODWORD(gran_offset), (SIZE_T) mmlen,
			 (LPVOID) gran_addr);
  if (map == NULL && (flags & MAP_FIXED))
    {
      map = MapViewOfFileEx (handle, mvf_flags, HIDWORD(gran_offset),
			     LODWORD(gran_offset), (SIZE_T) mmlen,
			     (LPVOID) NULL);
    }
  CloseHandle(handle);

  if (map == NULL)
    {
      errno = EINVAL; 	/* FIXME */
      return MAP_FAILED;
    }
  return map;
}

int munmap (void *addr, size_t len)
{
  if (!UnmapViewOfFile (addr))
    return -1;
  return 0;
}

#ifdef TEST

#define COMPARE(F1,F2)					\
  printf ("fname_cmp: `%s' %sthe same as `%s'\n", F1,	\
	  (fname_cmp (F1, F2) == 0) ? "" : "NOT ", F2);

int
main (int argc, char *argv[])
{
  struct utsname uts;
  struct passwd *pe;
  int status;

  if ((status = uname (&uts)) != 0)
    {
      fprintf (stderr, "uname: %d\n", status);
      return 1;
    }
  printf ("uname: `%s' `%s' `%s' `%s' `%s'\n",
	  uts.sysname, uts.release, uts.version, uts.machine, uts.nodename);

  printf ("getuid: %d\n", getuid ());
  pe = getpwuid (getuid ());
  printf ("getpwuid: name=`%s' dir=`%s' uid=%d shell=`%s'\n",
	  pe->pw_name, pe->pw_dir, pe->pw_uid, pe->pw_shell);

  COMPARE ("c:\\Program Files", "C:\\PROGRA~1")
  COMPARE ("c:/Program Files", "C:\\PROGRA~1")
    ;
  unlink ("ltest");
  if (link ("w32supp.c", "ltest") == -1)
    fprintf (stderr, "link failed\n");
  else
    printf ("ltest -> w32supp.c\n");

  return 0;
}
#endif
#endif // TARGET_OS_WINDOWS
