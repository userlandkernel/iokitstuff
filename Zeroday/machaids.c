//
//  machaids.c
//  iokitstuff
//
//  Created by Sem Voigtländer on 18/12/19.
//  Copyright © 2019 kernelprogrammer. All rights reserved.
//

#include "machaids.h"

static kern_return_t create_mach_voucher(const mach_voucher_attr_recipe_data_t *recipes, size_t recipes_size, mach_voucher_t *kvp) {
    kern_return_t kr = KERN_SUCCESS;
    mach_port_t mhp = mach_host_self();
    mach_voucher_t kv = MACH_VOUCHER_NULL;
    mach_voucher_attr_raw_recipe_array_t kvr;
    mach_voucher_attr_recipe_size_t kvr_size;
    kvr = (mach_voucher_attr_raw_recipe_array_t)recipes;
    kvr_size = (mach_voucher_attr_recipe_size_t)recipes_size;
    kr = host_create_mach_voucher(mhp, kvr, kvr_size, &kv);
    
    if(!kvp) {
        return KERN_FAILURE;
    }
    
    *kvp = kv;
    
    return kr;
}
