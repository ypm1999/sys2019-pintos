//
// Created by sjtu-ypm on 19-4-8.
//

#ifndef MYPINTOS_FRAME_H
#define MYPINTOS_FRAME_H

#include "../lib/stdint.h"
#include "../lib/kernel/hash.h"



void frame_init();
void *frame_get_user_page(uint32_t *pagedir);
void frame_free_user_page(void *frame);
void *frame_lookup(void *frame);


#endif //MYPINTOS_FRAME_H
