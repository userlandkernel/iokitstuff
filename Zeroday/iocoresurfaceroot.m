//
//  iocoresurfaceroot.c
//  Zeroday
//
//  Created by Sem Voigtländer on 18/12/19.
//  Copyright © 2019 kernelprogrammer. All rights reserved.
//

#include "iocoresurfaceroot.h"
#include <mach/mach.h>
#import <Foundation/Foundation.h>


static NSDictionary *optionsForBiplanarSurface(IntSize size, unsigned pixelFormat, size_t firstPlaneBytesPerPixel, size_t secondPlaneBytesPerPixel)
{
    int width = size.width;
    int height = size.height;
    
    size_t firstPlaneBytesPerRow = IOSurfaceAlignProperty(kIOSurfaceBytesPerRow, width * firstPlaneBytesPerPixel);
    size_t firstPlaneTotalBytes = IOSurfaceAlignProperty(kIOSurfaceAllocSize, height * firstPlaneBytesPerRow);
    
    size_t secondPlaneBytesPerRow = IOSurfaceAlignProperty(kIOSurfaceBytesPerRow, width * secondPlaneBytesPerPixel);
    size_t secondPlaneTotalBytes = IOSurfaceAlignProperty(kIOSurfaceAllocSize, height * secondPlaneBytesPerRow);
    
    size_t totalBytes = firstPlaneTotalBytes + secondPlaneTotalBytes;
    
    NSArray *planeInfo = @[
                           @{
                           (id)kIOSurfacePlaneWidth: @(width),
                           (id)kIOSurfacePlaneHeight: @(height),
                           (id)kIOSurfacePlaneBytesPerRow: @(firstPlaneBytesPerRow),
                           (id)kIOSurfacePlaneOffset: @(0),
                           (id)kIOSurfacePlaneSize: @(firstPlaneTotalBytes)
                           },
                           @{
                           (id)kIOSurfacePlaneWidth: @(width),
                           (id)kIOSurfacePlaneHeight: @(height),
                           (id)kIOSurfacePlaneBytesPerRow: @(secondPlaneBytesPerRow),
                           (id)kIOSurfacePlaneOffset: @(firstPlaneTotalBytes),
                           (id)kIOSurfacePlaneSize: @(secondPlaneTotalBytes)
                           }
                           ];
    return @{
        (id)kIOSurfaceWidth: @(width),
        (id)kIOSurfaceHeight: @(height),
        (id)kIOSurfacePixelFormat: @(pixelFormat),
        (id)kIOSurfaceAllocSize: @(totalBytes),
        (id)kIOSurfaceCacheMode: @(kIOMapWriteCombineCache),
        (id)kIOSurfacePlaneInfo: planeInfo,
    };
}

kern_return_t IOCoreSurfaceRootCreate(uint32_t allocSize, IOSurfaceID* surfaceID) {
    
    // Verify arguments are sane
    if(!surfaceID)
        return KERN_INVALID_ARGUMENT;
    
    CFMutableDictionaryRef dict = CFDictionaryCreateMutable(NULL, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
    CFDictionarySetValue(dict, CFSTR("IOSurfaceAllocSize"), CFNumberCreate(NULL, kCFNumberSInt32Type, &allocSize));
    CFDictionarySetValue(dict, CFSTR("IOSurfaceIsGlobal"), kCFBooleanTrue);
    IOSurfaceRef surface = IOSurfaceCreate(dict);
    
    printf("allocated IOSurface: %p\n", surface);
    
    *surfaceID = IOSurfaceGetID(surface);
    printf("Created IOSurface with ID: %#x\n", *surfaceID);
    return KERN_SUCCESS;
}



