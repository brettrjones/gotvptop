
#pragma once
#include <libgnu/config_libgnu.h>

/* sys/mman.h for w32 */

#define	PROT_NONE	 0x00	/* No access.  */
#define	PROT_READ	 0x04	/* Pages can be read.  */
#define	PROT_WRITE	 0x02	/* Pages can be written.  */
#define	PROT_EXEC	 0x01	/* Pages can be executed.  */

/* Flags contain mapping type, sharing type and options.  */

/* Mapping type (must choose one and only one of these).  */
#define MAP_FILE	 0x0001	/* Mapped from a file or device.  */
#define MAP_ANON	 0x0002	/* Allocated from anonymous virtual memory.  */
#define MAP_TYPE	 0x000f	/* Mask for type field.  */
#define MAP_ANONYMOUS  MAP_ANON /* Linux name. */

/* Sharing types (must choose one and only one of these).  */
#define MAP_COPY	 0x0020	/* Virtual copy of region at mapping time.  */
#define	MAP_SHARED	 0x0010	/* Share changes.  */
#define	MAP_PRIVATE	 0x0000	/* Changes private; copy pages on write.  */

/* Other flags.  */
#define	MAP_FIXED	 0x0100	/* Map address must be exactly as requested. */
#define MAP_NOEXTEND	 0x0200	/* For MAP_FILE, don't change file size.  */
#define MAP_HASSEMPHORE  0x0400	/* Region may contain semaphores.  */
#define MAP_INHERIT	 0x0800	/* Region is retained after exec.  */

#define MAP_FAILED	 ((void *)-1)

void *mmap (void *, size_t, int, int, int, uint64_t);
int munmap (void *, size_t);

