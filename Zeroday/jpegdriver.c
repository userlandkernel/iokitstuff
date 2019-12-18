//
//  jpegdriver.c
//  Zeroday
//
//  Created by Sem Voigtländer on 18/12/19.
//  Copyright © 2019 kernelprogrammer. All rights reserved.
//

#include "jpegdriver.h"
#include <mach/mach.h>

kern_return_t AppleJPEGDriverDecoderInit(void) {
    
    kern_return_t err = KERN_SUCCESS;
    io_service_t jpgd = io_get_service(IOSVC_JPEGD); // Try-get apple-jpeg service
    io_connect_t conn = IO_OBJECT_NULL;
    
    
    // First make sure that we found the iombf service
    if( !MACH_PORT_VALID(jpgd) ) {
        printf("Couldn't find AppleJPEGDriver service.\n");
        return KERN_FAILURE;
    }
    conn = io_connect_service(jpgd); // Open a connection to AppleJPEGDriver
    
    // Now make sure that the connection succeeded (sandbox might change in the future)
    if( !MACH_PORT_VALID(conn) ) {
        printf("Could not connect to AppleJPEGDriver service.\n");
        return KERN_FAILURE;
    }
    
    err = IOConnectCallMethod(conn, kAppleJPEGDecoderInitAction, NULL, 0, NULL, 0, NULL, NULL, NULL, NULL);
    
    if( err != KERN_SUCCESS ) {
        printf("Failed to initialize JPEG Decoder: %s\n", mach_error_string(err));
    }
    else {
        printf("Initialized JPEG Decoder\n");
    }
    
    // Securely dispose of allocated resources
    if ( conn != MACH_PORT_NULL ) {
        IOConnectRelease(conn);
        conn = MACH_PORT_NULL;
    }
    
    if ( jpgd != MACH_PORT_NULL ) {
        IOObjectRelease(jpgd);
        jpgd = MACH_PORT_NULL;
    }
    
    return err;
}

kern_return_t AppleJPEGDriverEncoderInit(void) {
    
    kern_return_t err = KERN_SUCCESS;
    io_service_t jpgd = io_get_service(IOSVC_JPEGD); // Try-get apple-jpeg service
    io_connect_t conn = IO_OBJECT_NULL;
    
    
    // First make sure that we found the iombf service
    if( !MACH_PORT_VALID(jpgd) ) {
        printf("Couldn't find AppleJPEGDriver service.\n");
        return KERN_FAILURE;
    }
    conn = io_connect_service(jpgd); // Open a connection to AppleJPEGDriver
    
    // Now make sure that the connection succeeded (sandbox might change in the future)
    if( !MACH_PORT_VALID(conn) ) {
        printf("Could not connect to AppleJPEGDriver service.\n");
        return KERN_FAILURE;
    }
    
    err = IOConnectCallMethod(conn, kAppleJPEGEncoderInitAction, NULL, 0, NULL, 0, NULL, NULL, NULL, NULL);
    
    if( err != KERN_SUCCESS ) {
        printf("Failed to get initialize JPEG Encoder: %s\n", mach_error_string(err));
    }
    else {
        printf("Initialized JPEG Encoder\n");
    }
    
    // Securely dispose of allocated resources
    if ( conn != MACH_PORT_NULL ) {
        IOConnectRelease(conn);
        conn = MACH_PORT_NULL;
    }
    
    if ( jpgd != MACH_PORT_NULL ) {
        IOObjectRelease(jpgd);
        jpgd = MACH_PORT_NULL;
    }
    
    return err;
}

kern_return_t AppleJPEGDriverEncoderStart(struct JPEGDriverArgs args) {
    
    kern_return_t err = KERN_SUCCESS;
    io_service_t jpgd = io_get_service(IOSVC_JPEGD); // Try-get apple-jpeg service
    io_connect_t conn = IO_OBJECT_NULL;
    
    
    // First make sure that we found the iombf service
    if( !MACH_PORT_VALID(jpgd) ) {
        printf("Couldn't find AppleJPEGDriver service.\n");
        return KERN_FAILURE;
    }
    conn = io_connect_service(jpgd); // Open a connection to AppleJPEGDriver
    
    // Now make sure that the connection succeeded (sandbox might change in the future)
    if( !MACH_PORT_VALID(conn) ) {
        printf("Could not connect to AppleJPEGDriver service.\n");
        return KERN_FAILURE;
    }
    
    err = IOConnectCallMethod(conn, kAppleJPEGEncoderStartAction, NULL, 0, &args, sizeof(args), NULL, NULL, NULL, NULL);
    
    if( err != KERN_SUCCESS ) {
        printf("Failed to start JPEG Encoder: %s\n", mach_error_string(err));
    }
    else {
        printf("Started JPEG encoder.\n");
    }
    
    // Securely dispose of allocated resources
    if ( conn != MACH_PORT_NULL ) {
        IOConnectRelease(conn);
        conn = MACH_PORT_NULL;
    }
    
    if ( jpgd != MACH_PORT_NULL ) {
        IOObjectRelease(jpgd);
        jpgd = MACH_PORT_NULL;
    }
    
    return err;
}

kern_return_t AppleJPEGDriverDecoderStart(struct JPEGDriverArgs args) {
    
    kern_return_t err = KERN_SUCCESS;
    io_service_t jpgd = io_get_service(IOSVC_JPEGD); // Try-get apple-jpeg service
    io_connect_t conn = IO_OBJECT_NULL;
    
    // First make sure that we found the iombf service
    if( !MACH_PORT_VALID(jpgd) ) {
        printf("Couldn't find AppleJPEGDriver service.\n");
        return KERN_FAILURE;
    }
    conn = io_connect_service(jpgd); // Open a connection to AppleJPEGDriver
    
    // Now make sure that the connection succeeded (sandbox might change in the future)
    if( !MACH_PORT_VALID(conn) ) {
        printf("Could not connect to AppleJPEGDriver service.\n");
        return KERN_FAILURE;
    }
    
    uint32_t inputCnt = sizeof(args);
    
    err = IOConnectCallMethod(conn, kAppleJPEGDecoderStartAction, NULL, 0, &args, inputCnt, NULL, NULL, NULL, NULL);
    
    if( err != KERN_SUCCESS ) {
        printf("Failed to start JPEG Decoder: %s\n", mach_error_string(err));
    }
    else {
        printf("Started JPEG Decoder.\n");
    }
    
    // Securely dispose of allocated resources
    if ( conn != MACH_PORT_NULL ) {
        IOConnectRelease(conn);
        conn = MACH_PORT_NULL;
    }
    
    if ( jpgd != MACH_PORT_NULL ) {
        IOObjectRelease(jpgd);
        jpgd = MACH_PORT_NULL;
    }
    
    return err;
}
