/*
	Author: Chen
	Implementation: Supplemental Page Table
*/

/*
	Page table mainly deal with such two situations:
	1. When page fault occurs, supplemental page table helps get the page to frame.
	2. When process exits, supplemental page table helps recycle resources.
	
	As is known to us all, the second situation is trivial :
		What we need to do is only iterate each element in page table and free them all (in fact, only FRAME and SWAP), then we destroy page table.

	Let's talk about the first situation.
	Where is physical address of our page?
		Maybe in stack (at the top of virtual address space) and we haven't apply a frame for it.
		Maybe in RAM, ok, in fact, if it's true, then page fault should not occur.
		Maybe in SWAP, a unfortunate frame has been evicted in this space.
		Maybe in FILESYS, we haven't load it ---- and this is what we need to do.
		
	When a virtual address is given to us, we hope to figure out what it is.
	But before we acctually start, we need to make sure that the top of VAS(virtual address space) has mapped to ZEROS.
	if the page has no mapping in our table, okay, a bad request.
	if page ----> ZEROS, the page below it shuold be added in our table; obtain a frame and refresh it.
	if page ----> FRAME, ASSERT false.
	if page ----> SWAP, obtain a frame and fill it with SWAP slot.
	if page ----> FILESYS, obtain a frame and fill it with FILESTREAM.
	Return the frame to caller. 
	
	Parallelism seems has nothing to do with me, after all, one process(thread) can't make two page fault at the same time.
	BUT FRAME and SWAP need it!
*/

#include "../lib/stdint.h"
#include "../lib/kernel/hash.h"
#include "../threads/palloc.h"

enum page_status {
	ZEROS,
	FRAME,
	SWAP,
	FILE
};

struct page_table_elem {
	void *key, *value;
	enum page_status status;
	/*
		key		:	page
		value	:	NULL (for stack growth)		status = ZEROS
				 or FRAME						status = FRAME
		         or swap slot					status = SWAP
		         or file pointer				status = FILESYS 
	*/
	struct hash_elem elem;
};

/* basic life cycle */
bool
page_init(struct hash *page_table);
void
page_destroy(struct hash *page_table); 

/* page fault handler */
void
page_page_fault(struct hash *page_table, void *vaddr);

/* interface for other modules*/
struct page_table_elem*
page_map_to_frame(struct hash *page_table, void *key, void *value);

struct page_table_elem*
page_map_to_swap(struct hash *page_table, void *key, void *value);

struct page_table_elem*
page_map_to_file(struct hash *page_table, void *key, void *value);


