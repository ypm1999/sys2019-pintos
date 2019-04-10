//
// Created by sjtu-ypm on 19-4-8.
//

#ifndef MYPINTOS_FRAME_H
#define MYPINTOS_FRAME_H

#include "../lib/stdint.h"
#include "../lib/kernel/hash.h"
#include "../threads/palloc.h"


//init frame_table
void  frame_init();


//get a frame from user pool, which must be mapped from upage
//in other words, in page_table, upage->frame_get_frame(flag, upage)
void* frame_get_frame(enum palloc_flags flag, void *upage);

//free a frame that got from frame_get_frame
void  frame_free_frame(void *frame);

//get upage according to frame
void* frame_get_upage(void* frame);

//get pinned accord to frame
//if a page is pinned, it won't be swaped to the disk
bool  frame_get_pinned(void* frame);

// set frame pinned to new_value
// return whether the set_pinned success
bool frame_set_pinned(void* frame, bool new_value);


#endif //MYPINTOS_FRAME_H
