//
//  ioaccelerator.h
//  Zeroday
//
//  Created by Sem Voigtländer on 18/12/19.
//  Copyright © 2019 kernelprogrammer. All rights reserved.
//

#ifndef ioaccelerator_h
#define ioaccelerator_h

#include <stdio.h>
#include <IOKit/graphics/IOAccelTypes.h>
#include "iokit.h"
enum IOAcceleratorOpenType {
    kIOAcceleratorOpenShared = 2,
};

enum IOAcceleratorAction {
    kIOAccelCreateSharedMemAction = 5,
};

// From Google Project Zero
struct AGXSharedMemArg {
    void* base;
    uint32_t size;
    uint32_t id;
};

struct submit_command_buffers_struct_input {
    uint32_t field_0;
    uint32_t field_1;
    uint32_t resource_id_0;
    uint32_t resource_id_1;
    uint64_t field_4;
    uint64_t field_5;
};

struct async_reference {
    mach_port_t port;
    void(*fptr)(void);
    uint64_t something;
};
kern_return_t IOAcceleratorCreateSharedMemory(size_t memsize, struct AGXSharedMemArg* agxMem);
kern_return_t IOAcceleratorESCreateSharedMemory(size_t memsize, struct AGXSharedMemArg* agxMem);
#endif /* ioaccelerator_h */
