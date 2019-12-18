//
//  iokit.c
//  Zeroday
//
//  Created by Sem Voigtländer on 18/12/19.
//  Copyright © 2019 kernelprogrammer. All rights reserved.
//

#include "iokit.h"

io_service_t io_get_service(const char *name) {
    io_service_t service = IOServiceGetMatchingService(kIOMasterPortDefault, IOServiceMatching(name));
    io_name_t className = {};
    if(MACH_PORT_VALID(service)) {
        IOObjectGetClass(service, className);
        printf("We got a userclient: %s::%s\n", name, className);
    }
    return service;
}

io_connect_t io_connect_service(io_service_t service) {
    
    kern_return_t err = KERN_SUCCESS;
    io_connect_t conn = IO_OBJECT_NULL;
    
    io_name_t className = {};
    err = IOObjectGetClass(service,className); // Retrieve the classname of the userclient
    
    printf("Got UserClient: %s\n", className);
    
    err = IOServiceOpen(service, mach_task_self(), 0, &conn); // Try to connect to the service
    if(err != KERN_SUCCESS){
        printf("Can not connect to %s\n", className);
        return IO_OBJECT_NULL;
    }
    
    return conn; // Return the connection to the service
}

io_connect_t io_connect_service_with_type(io_service_t service, uint32_t type) {
    
    kern_return_t err = KERN_SUCCESS;
    io_connect_t conn = IO_OBJECT_NULL;
    
    io_name_t className = {};
    err = IOObjectGetClass(service,className); // Retrieve the classname of the userclient
    
    printf("Got UserClient: %s\n", className);
    
    err = IOServiceOpen(service, mach_task_self(), type, &conn); // Try to connect to the service
    if(err != KERN_SUCCESS){
        printf("Can not connect to %s\n", className);
        return IO_OBJECT_NULL;
    }
    
    return conn; // Return the connection to the service
}
