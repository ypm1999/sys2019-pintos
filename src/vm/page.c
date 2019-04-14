/*
	Author: Chen
	Implementation: Supplemental Page Table
*/


#include "page.h"
#include "frame.h"
#include "swap.h"
#include "../threads/thread.h"
#include "../userprog/pagedir.h"
#include "../lib/stddef.h"
#include "../threads/malloc.h"
#include "../lib/debug.h"
#include "threads/vaddr.h"

bool page_hash_less(const struct hash_elem *lhs,
					 const struct hash_elem *rhs,
					 void *aux UNUSED);
					 
unsigned page_hash(const struct hash_elem *e,
					void *aux UNUSED);
					
void page_destroy_frame_likes(struct hash_elem *e,
							void *aux UNUSED);

bool page_stack_growth(struct hash *page_table,
							void *used);

/* basic life cycle */
/* return whether page init is sucessful or not, btw, this function will create an inital virtual stack slot */
bool
page_init(struct hash *page_table) {
	hash_init(page_table, page_hash, page_hash_less, NULL);
	
	return page_stack_growth(page_table, PHYS_BASE);
}

/* destory page_table and recycle FRAME and SWAP slot */
void
page_destroy(struct hash *page_table) {
	hash_destroy(page_table, page_destroy_frame_likes);
}

/* find the element with key = vaddr in page table*/
struct page_table_elem*
page_find(struct hash *page_table, void *vaddr) {
	struct page_table_elem *tmp;
	struct hash_elem *e;

	tmp = malloc(sizeof(*tmp));
	tmp->key = vaddr;
	e = hash_find(page_table, &(tmp->elem));
	free(tmp);
	
	if(e != NULL) {
		return hash_entry(e, struct page_table_elem, elem);
	}
	else {
		return NULL;
	}
}

/* page fault handler of page table*/
/* given a hash table and virtual address(page), allocate a frame for this page */

void
page_page_fault(struct hash *page_table, void *vaddr) {
	struct page_table_elem *t = page_find(page_table, vaddr);
	
	if(t == NULL) {
		ASSERT(false);
	}
	else {
		void *dest; /* a frame, the destination of our data to store*/
		
		switch(t->status) {
			case ZEROS:
//				dest = frame_get_frame();
				t->value = dest;
				t->status = FRAME;
				page_stack_growth(page_table, t->key);
				break;
			case FRAME:
				ASSERT(false);
				break;
			case SWAP:
//				dest = frame_get_frame();
				swap_load_to_frame(dest, t->value);
				break;
			case FILE:
//				dest = frame_get_frame();
				filesys_load_to_frame(dest, t->value);
				break;
			default:
				ASSERT(false);
		}
		
		/* TODO modify the mapping in original page_table*/
	}
}

/* interface for other modules*/
struct page_table_elem*
page_map_to_frame(struct hash *page_table, void *key, void *value) {
	struct page_table_elem* e = page_find(page_table, key);
	e->status = FRAME;
	e->value = value;
	/* TODO modify the mapping in original page_table*/
}

struct page_table_elem*
page_map_to_swap(struct hash *page_table, void *key, void *value) {
	struct page_table_elem* e = page_find(page_table, key);
	e->status = SWAP;
	e->value = value;
	/* TODO modify the mapping in original page_table*/
}

struct page_table_elem*
page_map_to_file(struct hash *page_table, void *key, void *value) {
	struct page_table_elem* e = page_find(page_table, key);
	e->status = FILESYS;
	e->value = value;
	/* TODO modify the mapping in original page_table*/
}

/* used to check whether the two pages are the same */
bool page_hash_less(const struct hash_elem *lhs, const struct hash_elem *rhs, void *aux UNUSED) {
	return hash_entry(lhs, struct page_table_elem, elem)->key < hash_entry(rhs, struct page_table_elem, elem)->key;
}

/* hash function of element in hash table*/
unsigned page_hash(const struct hash_elem *e, void* aux UNUSED){
	struct page_table_elem *t = hash_entry(e, struct page_table_elem, elem);
	return hash_bytes(&(t->key), sizeof(t->key));
}

/* return FRAME and SWAP slot back */
/* TODO maybe there is something need to be written back to FILESYS */
void page_destroy_frame_likes(struct hash_elem *e, void *aux UNUSED) {
	struct page_table_elem *t = hash_entry(e, struct page_table_elem, elem);

	if(t->status == FRAME) {
//		frame_free_frame(e->value);
	}
	else if(t->status == SWAP) {
//		swap_free_slot(e->value);
	}
	else;
}


/* create a stack slot exactly below "used" (make sure that space above "used" is full)*/
bool
page_stack_growth(struct hash *page_table, void *used) {
	struct page_table_elem *stack_elem = malloc(sizeof(*stack_elem));
	
	if(stack_elem != NULL) {
		stack_elem->key = used - PGSIZE;
		stack_elem->value = NULL;
		stack_elem->status = ZEROS;
		hash_insert(page_table, &(stack_elem->elem));
		return true;
	}
	else {
		return false;
	}
}
