//
//  iomobileframebuffer.c
//  Zeroday
//
//  Created by Sem Voigtländer on 18/12/19.
//  Copyright © 2019 kernelprogrammer. All rights reserved.
//

#include "iomobileframebuffer.h"
#include "iokit.h"

kern_return_t IOMobileFrameBufferGetDefaultSurface(IOSurfaceID* surfaceID) {
    
    kern_return_t err = KERN_SUCCESS;
    io_service_t iombf = io_get_service(IOSVC_IOMBF); // Try-get iombf service
    io_connect_t conn = IO_OBJECT_NULL;
    
    // Verify arguments are sane
    if(!surfaceID)
        return KERN_INVALID_ARGUMENT;
    
    // First make sure that we found the iombf service
    if( !MACH_PORT_VALID(iombf) ) {
        printf("Couldn't find IOMobileFrameBuffer service.\n");
        return KERN_FAILURE;
    }
    conn = io_connect_service(iombf); // Open a connection to IOMobileFrameBuffer
    
    // Now make sure that the connection succeeded (sandbox might change in the future)
    if( !MACH_PORT_VALID(conn) ) {
        printf("Could not connect to IOMobileFrameBuffer service.\n");
        return KERN_FAILURE;
    }
    
    uint64_t output[] = {0};
    uint32_t outputCnt = 1;
    err = IOConnectCallMethod(conn, kIOMBFGetDefaultSurfaceAction, NULL, 0, NULL, 0, output, &outputCnt, NULL, NULL);
    
    if( err != KERN_SUCCESS ) {
        printf("Failed to get default surface: %s\n", mach_error_string(err));
    }
    else {
        *surfaceID = (IOSurfaceID)output[0]; // Copy out the surface ID
        printf("Got default surface ID: %d\n", *surfaceID);
    }
    
    // Securely dispose of allocated resources
    if ( conn != MACH_PORT_NULL ) {
        IOConnectRelease(conn);
        conn = MACH_PORT_NULL;
    }
    
    if ( iombf != MACH_PORT_NULL ) {
        IOObjectRelease(iombf);
        iombf = MACH_PORT_NULL;
    }
    
    return err;
}

kern_return_t IOMobileFramebufferSwapBegin(IOMobileFramebufferSwapID* swapID) {
    
    kern_return_t err = KERN_SUCCESS;
    io_service_t iombf = io_get_service(IOSVC_IOMBF); // Try-get iombf service
    io_connect_t conn = IO_OBJECT_NULL;
    
    // Verify arguments are sane
    if(!swapID)
        return KERN_INVALID_ARGUMENT;
    
    // First make sure that we found the iombf service
    if( !MACH_PORT_VALID(iombf) ) {
        printf("Couldn't find IOMobileFrameBuffer service.\n");
        return KERN_FAILURE;
    }
    conn = io_connect_service(iombf); // Open a connection to IOMobileFrameBuffer
    
    // Now make sure that the connection succeeded (sandbox might change in the future)
    if( !MACH_PORT_VALID(conn) ) {
        printf("Could not connect to IOMobileFrameBuffer service.\n");
        return KERN_FAILURE;
    }

    uint32_t outputCnt = 1;
    err = IOConnectCallMethod(conn, kIOMBFSwapBeginAction, NULL, 0, NULL, 0, (uint64_t*)swapID, &outputCnt, NULL, NULL);
    
    if( err != KERN_SUCCESS ) {
        printf("Failed to get begin swapping: %s\n", mach_error_string(err));
    }
    else {
        printf("Got swapID: %#x\n", *swapID);
    }
    
    // Securely dispose of allocated resources
    if ( conn != MACH_PORT_NULL ) {
        IOConnectRelease(conn);
        conn = MACH_PORT_NULL;
    }
    
    if ( iombf != MACH_PORT_NULL ) {
        IOObjectRelease(iombf);
        iombf = MACH_PORT_NULL;
    }
    
    return err;
}

kern_return_t IOMobileFramebufferSwapEnd(struct IOMobileFramebufferSwapArg swapArg) {
    
    kern_return_t err = KERN_SUCCESS;
    io_service_t iombf = io_get_service(IOSVC_IOMBF); // Try-get iombf service
    io_connect_t conn = IO_OBJECT_NULL;
    
    // First make sure that we found the iombf service
    if( !MACH_PORT_VALID(iombf) ) {
        printf("Couldn't find IOMobileFrameBuffer service.\n");
        return KERN_FAILURE;
    }
    conn = io_connect_service(iombf); // Open a connection to IOMobileFrameBuffer
    
    // Now make sure that the connection succeeded (sandbox might change in the future)
    if( !MACH_PORT_VALID(conn) ) {
        printf("Could not connect to IOMobileFrameBuffer service.\n");
        return KERN_FAILURE;
    }
    
    err = IOConnectCallMethod(conn, kIOMBFSwapEndAction, (uint64_t*)&swapArg, sizeof(struct IOMobileFramebufferSwapArg), NULL, 0, NULL, NULL, NULL, NULL);
    
    if( err != KERN_SUCCESS ) {
        printf("Failed to end swapping: %s\n", mach_error_string(err));
    }
    
    // Securely dispose of allocated resources
    if ( conn != MACH_PORT_NULL ) {
        IOConnectRelease(conn);
        conn = MACH_PORT_NULL;
    }
    
    if ( iombf != MACH_PORT_NULL ) {
        IOObjectRelease(iombf);
        iombf = MACH_PORT_NULL;
    }
    
    return err;
}

kern_return_t IOMobileFramebufferGetID(IOSwapNotificationID* framebufferID) {
    
    kern_return_t err = KERN_SUCCESS;
    io_service_t iombf = io_get_service(IOSVC_IOMBF); // Try-get iombf service
    io_connect_t conn = IO_OBJECT_NULL;
    
    // Verify arguments are sane
    if(!framebufferID)
        return KERN_INVALID_ARGUMENT;
    
    // First make sure that we found the iombf service
    if( !MACH_PORT_VALID(iombf) ) {
        printf("Couldn't find IOMobileFrameBuffer service.\n");
        return KERN_FAILURE;
    }
    conn = io_connect_service(iombf); // Open a connection to IOMobileFrameBuffer
    
    // Now make sure that the connection succeeded (sandbox might change in the future)
    if( !MACH_PORT_VALID(conn) ) {
        printf("Could not connect to IOMobileFrameBuffer service.\n");
        return KERN_FAILURE;
    }
    
    uint32_t outputSize = 1;
    err = IOConnectCallMethod(conn, kIOMBFGetIdAction, NULL, 0, NULL, 0, (uint64_t*)framebufferID, &outputSize, NULL, NULL);
    
    if( err != KERN_SUCCESS ) {
        printf("Failed to get framebufferID: %s\n", mach_error_string(err));
    }
    else {
        printf("Got framebufferID: %#x\n", *framebufferID);
    }
    
    // Securely dispose of allocated resources
    if ( conn != MACH_PORT_NULL ) {
        IOConnectRelease(conn);
        conn = MACH_PORT_NULL;
    }
    
    if ( iombf != MACH_PORT_NULL ) {
        IOObjectRelease(iombf);
        iombf = MACH_PORT_NULL;
    }
    
    return err;
}

kern_return_t IOMobileFramebufferGetDisplaySize(struct IOMobileFramebufferDisplaySize* displaySize) {
    
    kern_return_t err = KERN_SUCCESS;
    io_service_t iombf = io_get_service(IOSVC_IOMBF); // Try-get iombf service
    io_connect_t conn = IO_OBJECT_NULL;
    
    // Verify arguments are sane
    if(!displaySize)
        return KERN_INVALID_ARGUMENT;
    
    // First make sure that we found the iombf service
    if( !MACH_PORT_VALID(iombf) ) {
        printf("Couldn't find IOMobileFrameBuffer service.\n");
        return KERN_FAILURE;
    }
    conn = io_connect_service(iombf); // Open a connection to IOMobileFrameBuffer
    
    // Now make sure that the connection succeeded (sandbox might change in the future)
    if( !MACH_PORT_VALID(conn) ) {
        printf("Could not connect to IOMobileFrameBuffer service.\n");
        return KERN_FAILURE;
    }
    
    size_t outputSize = sizeof(struct IOMobileFramebufferDisplaySize);
    err = IOConnectCallMethod(conn, kIOMBFGetDisplaySizeAction, NULL, 0, NULL, 0, NULL, NULL, (uint64_t*)displaySize, &outputSize);
    
    if( err != KERN_SUCCESS ) {
        printf("Failed to get display size: %s\n", mach_error_string(err));
    }
    else {
        printf("Height: %d Width: %d\n", displaySize->height, displaySize->width);
    }
    
    // Securely dispose of allocated resources
    if ( conn != MACH_PORT_NULL ) {
        IOConnectRelease(conn);
        conn = MACH_PORT_NULL;
    }
    
    if ( iombf != MACH_PORT_NULL ) {
        IOObjectRelease(iombf);
        iombf = MACH_PORT_NULL;
    }
    
    return err;
}

kern_return_t IOMobileFramebufferSetVsyncNotifications(size_t functionAddress, size_t userData) {
    
    kern_return_t err = KERN_SUCCESS;
    io_service_t iombf = io_get_service(IOSVC_IOMBF); // Try-get iombf service
    io_connect_t conn = IO_OBJECT_NULL;
    
    // First make sure that we found the iombf service
    if( !MACH_PORT_VALID(iombf) ) {
        printf("Couldn't find IOMobileFrameBuffer service.\n");
        return KERN_FAILURE;
    }
    conn = io_connect_service(iombf); // Open a connection to IOMobileFrameBuffer
    
    // Now make sure that the connection succeeded (sandbox might change in the future)
    if( !MACH_PORT_VALID(conn) ) {
        printf("Could not connect to IOMobileFrameBuffer service.\n");
        return KERN_FAILURE;
    }
    
    size_t input[] = {functionAddress, userData};
    uint32_t inputCount = 2;
    err = IOConnectCallMethod(conn, kIOMBFSetVSyncNotificationsAction, (uint64_t*)input, inputCount, NULL, 0, NULL, NULL, NULL, NULL);
    
    if( err != KERN_SUCCESS ) {
        printf("Failed to set Vsync notifications: %s\n", mach_error_string(err));
    }
    
    // Securely dispose of allocated resources
    if ( conn != MACH_PORT_NULL ) {
        IOConnectRelease(conn);
        conn = MACH_PORT_NULL;
    }
    
    if ( iombf != MACH_PORT_NULL ) {
        IOObjectRelease(iombf);
        iombf = MACH_PORT_NULL;
    }
    
    return err;
}

kern_return_t IOMobileFramebufferSetDisplayDevice(uint32_t device) {
    
    kern_return_t err = KERN_SUCCESS;
    io_service_t iombf = io_get_service(IOSVC_IOMBF); // Try-get iombf service
    io_connect_t conn = IO_OBJECT_NULL;
    
    // First make sure that we found the iombf service
    if( !MACH_PORT_VALID(iombf) ) {
        printf("Couldn't find IOMobileFrameBuffer service.\n");
        return KERN_FAILURE;
    }
    conn = io_connect_service(iombf); // Open a connection to IOMobileFrameBuffer
    
    // Now make sure that the connection succeeded (sandbox might change in the future)
    if( !MACH_PORT_VALID(conn) ) {
        printf("Could not connect to IOMobileFrameBuffer service.\n");
        return KERN_FAILURE;
    }
    
    size_t input[] = {device};
    uint32_t inputCount = 1;
    err = IOConnectCallMethod(conn, kIOMBFSetDisplayDeviceAction, (uint64_t*)input, inputCount, NULL, 0, NULL, NULL, NULL, NULL);
    
    if( err != KERN_SUCCESS ) {
        printf("Failed to set display device: %s\n", mach_error_string(err));
    }
    
    // Securely dispose of allocated resources
    if ( conn != MACH_PORT_NULL ) {
        IOConnectRelease(conn);
        conn = MACH_PORT_NULL;
    }
    
    if ( iombf != MACH_PORT_NULL ) {
        IOObjectRelease(iombf);
        iombf = MACH_PORT_NULL;
    }
    
    return err;
}

kern_return_t IOMobileFramebufferSetVideoPowerSaving(uint32_t value) {
    
    kern_return_t err = KERN_SUCCESS;
    io_service_t iombf = io_get_service(IOSVC_IOMBF); // Try-get iombf service
    io_connect_t conn = IO_OBJECT_NULL;
    
    // First make sure that we found the iombf service
    if( !MACH_PORT_VALID(iombf) ) {
        printf("Couldn't find IOMobileFrameBuffer service.\n");
        return KERN_FAILURE;
    }
    conn = io_connect_service(iombf); // Open a connection to IOMobileFrameBuffer
    
    // Now make sure that the connection succeeded (sandbox might change in the future)
    if( !MACH_PORT_VALID(conn) ) {
        printf("Could not connect to IOMobileFrameBuffer service.\n");
        return KERN_FAILURE;
    }
    
    size_t input[] = {value};
    uint32_t inputCount = 1;
    err = IOConnectCallMethod(conn, kIOMBFSetVideoPowerSavingAction, (uint64_t*)input, inputCount, NULL, 0, NULL, NULL, NULL, NULL);
    
    if( err != KERN_SUCCESS ) {
        printf("Failed to set video powersaving: %s\n", mach_error_string(err));
    }
    else {
        printf("Set videopowersaving  = %#x\n", value);
    }
    
    // Securely dispose of allocated resources
    if ( conn != MACH_PORT_NULL ) {
        IOConnectRelease(conn);
        conn = MACH_PORT_NULL;
    }
    
    if ( iombf != MACH_PORT_NULL ) {
        IOObjectRelease(iombf);
        iombf = MACH_PORT_NULL;
    }
    
    return err;
}

kern_return_t IOMobileFramebufferSetBrightnessCorrection(uint32_t value) {
    
    kern_return_t err = KERN_SUCCESS;
    io_service_t iombf = io_get_service(IOSVC_IOMBF); // Try-get iombf service
    io_connect_t conn = IO_OBJECT_NULL;
    
    // First make sure that we found the iombf service
    if( !MACH_PORT_VALID(iombf) ) {
        printf("Couldn't find IOMobileFrameBuffer service.\n");
        return KERN_FAILURE;
    }
    conn = io_connect_service(iombf); // Open a connection to IOMobileFrameBuffer
    
    // Now make sure that the connection succeeded (sandbox might change in the future)
    if( !MACH_PORT_VALID(conn) ) {
        printf("Could not connect to IOMobileFrameBuffer service.\n");
        return KERN_FAILURE;
    }
    
    size_t input[] = {value};
    uint32_t inputCount = 1;
    err = IOConnectCallMethod(conn, kIOMBFSetBrightnessCorrectionAction, (uint64_t*)input, inputCount, NULL, 0, NULL, NULL, NULL, NULL);
    
    if( err != KERN_SUCCESS ) {
        printf("Failed to set brightness correction: %s\n", mach_error_string(err));
    }
    else {
        printf("Set brightness-correction  = %#x\n", value);
    }
    
    // Securely dispose of allocated resources
    if ( conn != MACH_PORT_NULL ) {
        IOConnectRelease(conn);
        conn = MACH_PORT_NULL;
    }
    
    if ( iombf != MACH_PORT_NULL ) {
        IOObjectRelease(iombf);
        iombf = MACH_PORT_NULL;
    }
    
    return err;
}


kern_return_t IOMobileFrameBufferIsMainDisplay(bool *isMainDisplay) {
    
    kern_return_t err = KERN_SUCCESS;
    io_service_t iombf = io_get_service(IOSVC_IOMBF); // Try-get iombf service
    io_connect_t conn = IO_OBJECT_NULL;
    
    // Verify arguments are sane
    if(!isMainDisplay)
        return KERN_INVALID_ARGUMENT;
    
    // First make sure that we found the iombf service
    if( !MACH_PORT_VALID(iombf) ) {
        printf("Couldn't find IOMobileFrameBuffer service.\n");
        return KERN_FAILURE;
    }
    conn = io_connect_service(iombf); // Open a connection to IOMobileFrameBuffer
    
    // Now make sure that the connection succeeded (sandbox might change in the future)
    if( !MACH_PORT_VALID(conn) ) {
        printf("Could not connect to IOMobileFrameBuffer service.\n");
        return KERN_FAILURE;
    }
    
    // Make the call to IOMBF and return whether this is the main display
    uint32_t outputCnt = 1;
    err = IOConnectCallMethod(conn, kIOMBFIsMainDisplayAction, NULL, 0, NULL, 0, (uint64_t*)isMainDisplay, &outputCnt, NULL, NULL);
    
    if( err != KERN_SUCCESS ) {
        printf("Failed to get whether this is the main display: %s\n", mach_error_string(err));
    }
    else {
        printf("Is main display: %d\n", *isMainDisplay);
    }
    
    // Securely dispose of allocated resources
    if ( conn != MACH_PORT_NULL ) {
        IOConnectRelease(conn);
        conn = MACH_PORT_NULL;
    }
    
    if ( iombf != MACH_PORT_NULL ) {
        IOObjectRelease(iombf);
        iombf = MACH_PORT_NULL;
    }
    
    return err;
}


kern_return_t IOMobileFrameBufferSetWhiteOnBlackMode(bool enabled) {
    
    kern_return_t err = KERN_SUCCESS;
    io_service_t iombf = io_get_service(IOSVC_IOMBF); // Try-get iombf service
    io_connect_t conn = IO_OBJECT_NULL;
    
    // First make sure that we found the iombf service
    if( !MACH_PORT_VALID(iombf) ) {
        printf("Couldn't find IOMobileFrameBuffer service.\n");
        return KERN_FAILURE;
    }
    conn = io_connect_service(iombf); // Open a connection to IOMobileFrameBuffer
    
    // Now make sure that the connection succeeded (sandbox might change in the future)
    if( !MACH_PORT_VALID(conn) ) {
        printf("Could not connect to IOMobileFrameBuffer service.\n");
        return KERN_FAILURE;
    }
    
    uint64_t wobMode[] = {enabled}; // IOkit uses scalar input
    uint32_t wobModeCount = 1;
    
    // Perform the call to set the 'white-on-black-mode' on the framebuffer
    err = IOConnectCallMethod(conn, kIOMBFSetWhiteOnBlackModeAction, wobMode, wobModeCount, NULL, 0, NULL, NULL, NULL, NULL);
    if( err != KERN_SUCCESS ) {
        printf("Failed to enable white-on-black mode.\n");
    }
    
    // Securely dispose of allocated resources
    if ( conn != MACH_PORT_NULL ) {
        IOConnectRelease(conn);
        conn = MACH_PORT_NULL;
    }
    
    if ( iombf != MACH_PORT_NULL ) {
        IOObjectRelease(iombf);
        iombf = MACH_PORT_NULL;
    }
    
    return err;
    
}

kern_return_t IOMobileFrameBufferSetDebugFlags(uint32_t *debugFlags) {
    
    kern_return_t err = KERN_SUCCESS;
    io_service_t iombf = io_get_service(IOSVC_IOMBF); // Try-get iombf service
    io_connect_t conn = IO_OBJECT_NULL;
    
    if(!debugFlags)
        return KERN_INVALID_ARGUMENT;
    
    // First make sure that we found the iombf service
    if( !MACH_PORT_VALID(iombf) ) {
        printf("Couldn't find IOMobileFrameBuffer service.\n");
        return KERN_FAILURE;
    }
    conn = io_connect_service(iombf); // Open a connection to IOMobileFrameBuffer
    
    // Now make sure that the connection succeeded (sandbox might change in the future)
    if( !MACH_PORT_VALID(conn) ) {
        printf("Could not connect to IOMobileFrameBuffer service.\n");
        return KERN_FAILURE;
    }
    
    // Perform the call to set the 'debug flags' on the framebuffer
    uint32_t outputCnt = 2;
    err = IOConnectCallMethod(conn, kIOMBFSetDebugFlagsAction, (uint64_t*)debugFlags, 2, NULL, 0, NULL, (uint32_t*)debugFlags, &outputCnt, NULL);
    if( err != KERN_SUCCESS ) {
        printf("Failed to set the debugflags: %s\n", mach_error_string(err));
    }
    
    // Securely dispose of allocated resources
    if ( conn != MACH_PORT_NULL ) {
        IOConnectRelease(conn);
        conn = MACH_PORT_NULL;
    }
    
    if ( iombf != MACH_PORT_NULL ) {
        IOObjectRelease(iombf);
        iombf = MACH_PORT_NULL;
    }
    
    return err;
    
}


inline static void dump_gammatables(struct IOMobileFramebufferGammaTables tables){
    for(int i = 0; i < 3; i++){
        printf("TABLE %d:\n", i);
        printf("-----------------------------------------------------------------\n");
        for(int j = 0; j < 0x101; j++){
            printf("%#x ", tables.gammaTable[i].value[j]);
        }
        printf("\n-----------------------------------------------------------------\n");
    }
}

kern_return_t IOMobileFrameBufferGetGammaTables(struct IOMobileFramebufferGammaTables *gammaTables) {
    
    kern_return_t err = KERN_SUCCESS;
    io_service_t iombf = io_get_service(IOSVC_IOMBF); // Try-get iombf service
    io_connect_t conn = IO_OBJECT_NULL;
    
    // Verify arguments are sane
    if(!gammaTables)
        return KERN_INVALID_ARGUMENT;
    
    // First make sure that we found the iombf service
    if( !MACH_PORT_VALID(iombf) ) {
        printf("Couldn't find IOMobileFrameBuffer service.\n");
        return KERN_FAILURE;
    }
    conn = io_connect_service(iombf); // Open a connection to IOMobileFrameBuffer
    
    // Now make sure that the connection succeeded (sandbox might change in the future)
    if( !MACH_PORT_VALID(conn) ) {
        printf("Could not connect to IOMobileFrameBuffer service.\n");
        return KERN_FAILURE;
    }
    
    // Make the call to IOMBF and return whether this is the main display
    size_t outputCnt = sizeof(struct IOMobileFramebufferGammaTables);
    err = IOConnectCallMethod(conn, kIOMBFGetGammaTableAction, NULL, 0, NULL, 0, NULL, NULL, (uint64_t*)gammaTables, &outputCnt);
    
    if( err != KERN_SUCCESS ) {
        printf("Failed to get gamma tables: %s\n", mach_error_string(err));
    }
    else {
        dump_gammatables(*gammaTables);
    }
    
    // Securely dispose of allocated resources
    if ( conn != MACH_PORT_NULL ) {
        IOConnectRelease(conn);
        conn = MACH_PORT_NULL;
    }
    
    if ( iombf != MACH_PORT_NULL ) {
        IOObjectRelease(iombf);
        iombf = MACH_PORT_NULL;
    }
    
    return err;
}

kern_return_t IOMobileFrameBufferSetGammaTables(struct IOMobileFramebufferGammaTables gammaTables) {
    
    kern_return_t err = KERN_SUCCESS;
    io_service_t iombf = io_get_service(IOSVC_IOMBF); // Try-get iombf service
    io_connect_t conn = IO_OBJECT_NULL;
    
    // First make sure that we found the iombf service
    if( !MACH_PORT_VALID(iombf) ) {
        printf("Couldn't find IOMobileFrameBuffer service.\n");
        return KERN_FAILURE;
    }
    
    conn = io_connect_service(iombf); // Open a connection to IOMobileFrameBuffer
    
    // Now make sure that the connection succeeded (sandbox might change in the future)
    if( !MACH_PORT_VALID(conn) ) {
        printf("Could not connect to IOMobileFrameBuffer service.\n");
        return KERN_FAILURE;
    }
    
    // Make the call to IOMBF and return whether this is the main display
    size_t inputCount = sizeof(struct IOMobileFramebufferGammaTables);
    err = IOConnectCallMethod(conn, kIOMBFSetGammaTableAction, NULL, 0, &gammaTables, inputCount, NULL, NULL, NULL, NULL);
    
    if( err != KERN_SUCCESS ) {
        printf("Failed to set gamma tables: %s\n", mach_error_string(err));
    }
    else {
        printf("Updated the gamma tables. \n");
    }
    
    
    // Securely dispose of allocated resources
    if ( conn != MACH_PORT_NULL ) {
        IOConnectRelease(conn);
        conn = MACH_PORT_NULL;
    }
    
    if ( iombf != MACH_PORT_NULL ) {
        IOObjectRelease(iombf);
        iombf = MACH_PORT_NULL;
    }
    
    return err;
}

kern_return_t IOMobileFramebufferResetGammaTables(void) {
    
    kern_return_t err = KERN_SUCCESS;
    struct IOMobileFramebufferGammaTables tables = {};
    
    for(int i = 0, j = 0; i < 0x101; j+=4, i++){
        tables.gammaTable[0].value[i] = j;
        tables.gammaTable[1].value[i] = j;
        tables.gammaTable[2].value[i] = j;
    }
    
    err = IOMobileFrameBufferSetGammaTables(tables);
    return err;
}
