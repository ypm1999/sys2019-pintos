//
// Created by sjtu-ypm on 19-4-8.
//

#include "frame.h"
#include "swap.h"
#include "../threads/thread.h"
#include "../userprog/pagedir.h"
#include "../lib/stddef.h"
#include "../threads/malloc.h"
#include "../lib/debug.h"


struct frame_item{
    void *frame;
    void *upage;
    bool pinned;
    struct hash_elem hash_elem;
    struct list_elem list_elem;
};

struct hash frame_table;
struct list frame_clock_list;

struct frame_item* current_frame;

void *frame_lookup(void *frame);
void *frame_get_used_frame();
void frame_current_clock_to_next();
void frame_current_clock_to_prev();


bool frame_hash_less(const struct hash_elem *a,
                     const struct hash_elem *b,
                     void *aux UNUSED);
unsigned frame_hash(const struct hash_elem *e,
                    void *aux UNUSED);


void frame_init(){
  hash_init(&frame_table, frame_hash, frame_hash_less, NULL);
  list_init(&frame_clock_list);
  current_frame = NULL;
}

void *frame_get_frame(enum palloc_flags flag, void *upage) {
  void *frame = palloc_get_page(PAL_USER | flag);
//  if (frame == NULL)
//    frame = frame_get_used_frame();
  if (frame == NULL)
    return NULL;
  struct frame_item* tmp = (struct frame_item*)malloc(sizeof (struct frame_item));
  tmp->frame = frame;
  tmp->upage = upage;
  tmp->pinned = true;
  hash_insert(&frame_table, &tmp->hash_elem);
  return frame;
}

void frame_free_frame(void *frame){
  struct frame_item* t = frame_lookup(frame);
  if (t == NULL)
    PANIC("try_free_a frame_that_not_exist!!");
  //TODO remove from clock_list & check current_frame==t
//  if (current_frame == t){
//    if (list_empty(&frame_clock_list))
//      current_frame = NULL;
//    else
//      frame_current_clock_to_next();
//  }
//  list_remove(&current_frame->list_elem);
  palloc_free_page(frame);
  hash_delete(&frame_table, &t->hash_elem);
  free(t);
}

bool frame_get_pinned(void* frame){
  struct frame_item* t = frame_lookup(frame);
  if (t == NULL)
    PANIC("try_set_pinned_of_a frame_that_not_exist!!");
  return t->pinned;
}

bool frame_set_pinned_false(void* frame){
  struct frame_item* t = frame_lookup(frame);
  if (t == NULL)
    return false;
  t->pinned = false;
//  list_push_back(&frame_clock_list, &t->list_elem);
//  if (list_size(&frame_clock_list) == 1)
//    current_frame = t;
  return true;
}

void *frame_lookup(void *frame){
  struct frame_item p;
  struct hash_elem * e;
  p.frame = frame;
  e = hash_find(&frame_table, &p.hash_elem);
  return e == NULL? NULL : hash_entry(e, struct frame_item, hash_elem);
}

void* frame_get_used_frame(){
  ASSERT(current_frame != NULL);

  uint32_t* pd = thread_current()->pagedir;
  while(pagedir_is_accessed(pd, current_frame->upage)){
    pagedir_set_accessed(pd, current_frame->upage, false);
    frame_current_clock_to_next();
  }
  if (pagedir_is_dirty(pd, current_frame->upage)){
    if (!swap_store_page(current_frame->upage))
      return NULL;
    pagedir_set_dirty(pd, current_frame->upage, false);
  }
  void* temp_frame = current_frame;
  frame_current_clock_to_next();
  return temp_frame;
}

void frame_current_clock_to_next(){
  ASSERT(current_frame != NULL);
  if (list_size(&frame_clock_list) == 1)
    return;;
  if (&current_frame->list_elem == list_back(&frame_clock_list))
    current_frame = list_entry(list_head(&frame_clock_list),
                               struct frame_item, list_elem);

  current_frame = list_entry(list_next(&current_frame->list_elem),
                             struct frame_item, list_elem);
}

void frame_current_clock_to_prev(){
  ASSERT(current_frame != NULL);
  if (list_size(&frame_clock_list) == 1)
    return;;

  if (&current_frame->list_elem == list_front(&frame_clock_list))
    current_frame = list_entry(list_tail(&frame_clock_list),
                               struct frame_item, list_elem);

  current_frame = list_entry(list_prev(&current_frame->list_elem),
                             struct frame_item, list_elem);
}



bool frame_hash_less(const struct hash_elem *a, const struct hash_elem *b, void *aux UNUSED){
  const struct frame_item * ta = hash_entry(a, struct frame_item, hash_elem);
  const struct frame_item * tb = hash_entry(b, struct frame_item, hash_elem);
  return ta->frame < tb->frame;
}

unsigned frame_hash(const struct hash_elem *e, void* aux UNUSED){
  struct frame_item* t = hash_entry(e, struct frame_item, hash_elem);
  return hash_bytes(&t->frame, sizeof(t->frame));
}
