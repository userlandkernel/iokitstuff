//
//  ioaccelerator.c
//  Zeroday
//
//  Created by Sem Voigtländer on 18/12/19.
//  Copyright © 2019 kernelprogrammer. All rights reserved.
//

#include "ioaccelerator.h"
#include "iocoresurfaceroot.h"
#include <mach/mach.h>
#include <IOKit/graphics/IOAccelClientConnect.h>
#include <IOKit/graphics/IOAccelSurfaceConnect.h>

kern_return_t IOAcceleratorCreateSharedMemory(size_t memsize, struct AGXSharedMemArg* agxMem) {
    kern_return_t err = KERN_SUCCESS;
    io_service_t agx = io_get_service("IOGraphicsAccelerator2"); // Try-get AGX service
    io_connect_t conn = IO_OBJECT_NULL;
    
    // First make sure that we found the AGX service
    if( !MACH_PORT_VALID(agx) ) {
        printf("Couldn't find AGX service.\n");
        return KERN_FAILURE;
    }

    conn = io_connect_service_with_type(agx, kIOAcceleratorOpenShared); // Open a connection to AGX
    
    // Second make sure that we can connect to the AGX service
    if( !MACH_PORT_VALID(conn) ) {
        printf("Couldn't connect to AGX service (shared userclient): %s\n", mach_error_string(err));
        return KERN_FAILURE;
    }

    size_t outputCnt = sizeof(struct AGXSharedMemArg);
    
    err = IOConnectCallMethod(conn, kIOAccelCreateSharedMemAction, (uint64_t*)&memsize, 1, NULL, 0, NULL, NULL, agxMem, &outputCnt);
    if (err != KERN_SUCCESS) {
        printf("Couldn't create shared memory: %s\n", mach_error_string(err));
        return err;
    }
    else {
        printf("create shmem success!\n");
        printf("base: %p size: 0x%x id: 0x%x\n", agxMem->base, agxMem->size, agxMem->id);
    }
    
    return err;
}

kern_return_t IOAcceleratorESCreateSharedMemory(size_t memsize, struct AGXSharedMemArg* agxMem) {
    kern_return_t err = KERN_SUCCESS;
    io_service_t agx = io_get_service("IOAcceleratorES"); // Try-get AGX service
    io_connect_t conn = IO_OBJECT_NULL;
    
    // First make sure that we found the AGX service
    if( !MACH_PORT_VALID(agx) ) {
        printf("Couldn't find AGX service.\n");
        return KERN_FAILURE;
    }
    
    conn = io_connect_service_with_type(agx, kIOAcceleratorOpenShared); // Open a connection to AGX
    
    // Second make sure that we can connect to the AGX service
    if( !MACH_PORT_VALID(conn) ) {
        printf("Couldn't connect to AGX service (shared userclient): %s\n", mach_error_string(err));
        return KERN_FAILURE;
    }
    
    size_t outputCnt = sizeof(struct AGXSharedMemArg);
    
    err = IOConnectCallMethod(conn, kIOAccelCreateSharedMemAction, (uint64_t*)&memsize, 1, NULL, 0, NULL, NULL, agxMem, &outputCnt);
    if (err != KERN_SUCCESS) {
        printf("Couldn't create shared memory: %s\n", mach_error_string(err));
        return err;
    }
    else {
        printf("create shmem success!\n");
        printf("base: %p size: 0x%x id: 0x%x\n", agxMem->base, agxMem->size, agxMem->id);
    }
    
    return err;
}
