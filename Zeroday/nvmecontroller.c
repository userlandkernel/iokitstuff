//
//  nvmecontroller.c
//  iokitstuff
//
//  Created by Sem Voigtländer on 28/01/20.
//  Copyright © 2020 kernelprogrammer. All rights reserved.
//

#include "nvmecontroller.h"

kern_return_t nvmecontroller_setBFHGPIO(uint64_t value) {
    
    kern_return_t err = KERN_SUCCESS;
    io_service_t nvmesvc = io_get_service(IOSVC_NVMECTL); // Try-get nvme-controller service
    io_connect_t conn = IO_OBJECT_NULL;
    
    
    // First make sure that we found the iombf service
    if( !MACH_PORT_VALID(nvmesvc) ) {
        printf("Couldn't find AppleEmbeddedNVMeController service.\n");
        return KERN_FAILURE;
    }
    conn = io_connect_service(nvmesvc); // Open a connection to AppleEmbeddedNVMeController
    
    // Now make sure that the connection succeeded (sandbox might change in the future)
    if( !MACH_PORT_VALID(conn) ) {
        printf("Could not connect to AppleEmbeddedNVMeController service.\n");
        return KERN_FAILURE;
    }
    uint64_t output = 0;
    uint32_t outputCnt = 1;
    err = IOConnectCallMethod(conn, kNVMECTL_setBFHGPIOAction, &value, 1, NULL, 0, &output, &outputCnt, NULL, NULL);
    
    if(err != KERN_SUCCESS) {
        return err;
    }
    
    return err;
}

kern_return_t nvmecontroller_isBFHMode(bool *bfhMode) {
    
    kern_return_t err = KERN_SUCCESS;
    io_service_t nvmesvc = io_get_service(IOSVC_NVMECTL); // Try-get nvme-controller service
    io_connect_t conn = IO_OBJECT_NULL;
    
    if( !bfhMode )
        return KERN_INVALID_ARGUMENT;
    
    
    // First make sure that we found the iombf service
    if( !MACH_PORT_VALID(nvmesvc) ) {
        printf("Couldn't find AppleEmbeddedNVMeController service.\n");
        return KERN_FAILURE;
    }
    conn = io_connect_service(nvmesvc); // Open a connection to AppleEmbeddedNVMeController
    
    // Now make sure that the connection succeeded (sandbox might change in the future)
    if( !MACH_PORT_VALID(conn) ) {
        printf("Could not connect to AppleEmbeddedNVMeController service.\n");
        return KERN_FAILURE;
    }
    
    uint64_t output = 0;
    uint32_t outputCnt = 1;
    err = IOConnectCallMethod(conn, kNVMECTL_isBFHModeAction, NULL, 0, NULL, 0, &output, &outputCnt, NULL, NULL);
    
    if(err != KERN_SUCCESS) {
        return err;
    }
    *bfhMode = output != 0;
    
    return err;
}
