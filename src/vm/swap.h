//
// Created by sjtu-ypm on 19-4-11.
//

#ifndef MYPINTOS_SWAP_H
#define MYPINTOS_SWAP_H


#include "../lib/stdbool.h"

//store upage to swap
//if the upage cant't be stored, current_process will be terminated
bool swap_store_page(void* upage);

//load a content of the upage to kpage from swap
//return whether load failed
bool swap_load_page(void* upage, void *kpage);

#endif //MYPINTOS_SWAP_H
