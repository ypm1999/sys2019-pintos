//
// Created by sjtu-ypm on 19-4-8.
//

#include "frame.h"
#include "../lib/stddef.h"
#include "../threads/malloc.h"
#include "../lib/debug.h"

struct frame_item{
    void *frame;
    void *upage;
    bool pinned;
    struct hash_elem hash_elem;
};

struct hash frame_table;

void *frame_lookup(void *frame);

bool frame_hash_less(const struct hash_elem *a, const struct hash_elem *b, void *aux UNUSED){
  const struct frame_item * ta = hash_entry(a, struct frame_item, hash_elem);
  const struct frame_item * tb = hash_entry(b, struct frame_item, hash_elem);
  return ta->frame < tb->frame;
}

unsigned frame_hash(const struct hash_elem *e, void* aux UNUSED){
  struct frame_item* t = hash_entry(e, struct frame_item, hash_elem);
  return hash_bytes(&t->frame, sizeof(t->frame));
}

void frame_init(){
  hash_init(&frame_table, frame_hash, frame_hash_less, NULL);
}

void *frame_get_frame(enum palloc_flags flag, void *upage) {
  void *page = palloc_get_page(PAL_USER | flag);
  if (page == NULL)
    return NULL;
  struct frame_item* tmp = (struct frame_item*)malloc(sizeof (struct frame_item));
  tmp->frame = page;
  tmp->upage = upage;
  tmp->pinned = true;
  hash_insert(&frame_table, &tmp->hash_elem);
  return page;
}

void frame_free_frame(void *frame){
  struct frame_item* t = frame_lookup(frame);
  palloc_free_page(frame);
  hash_delete(&frame_table, &t->hash_elem);
  free(t);
}

void *frame_lookup(void *frame){
  struct frame_item p;
  struct hash_elem * e;
  p.frame = frame;
  e = hash_find(&frame_table, &p.hash_elem);
  return e == NULL? NULL : hash_entry(e, struct frame_item, hash_elem);
}

void* frame_get_upage(void* frame){
  struct frame_item* t = frame_lookup(frame);
  if (t == NULL)
    return NULL;
  return t->upage;
}
bool frame_get_pinned(void* frame){
  struct frame_item* t = frame_lookup(frame);
  if (t == NULL)
    return NULL;
  return t->pinned;
}
bool frame_set_pinned(void* frame, bool new_value){
  struct frame_item* t = frame_lookup(frame);
  if (t == NULL)
    return false;
  t->pinned = new_value;
  return true;
}


