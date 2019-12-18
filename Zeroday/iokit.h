//
//  iokit.h
//  Zeroday
//
//  Created by Sem Voigtländer on 18/12/19.
//  Copyright © 2019 kernelprogrammer. All rights reserved.
//

#ifndef iokit_h
#define iokit_h

#include <stdio.h>
#include <IOKit/IOKitLib.h>
#include <IOKit/IOKitKeys.h>
#include <libkern/OSKextLib.h>
#include <IOKit/kext/KextManager.h>
#include <CoreFoundation/CoreFoundation.h>
io_service_t io_get_service(const char *name);
io_connect_t io_connect_service(io_service_t service);
io_connect_t io_connect_service_with_type(io_service_t service, uint32_t type);
#define IOSVC_IOMBF "IOMobileFramebuffer"
#define IOSVC_JPEGD "AppleJPEGDriver"
#define IOSVC_IOCSR "IOSurfaceRoot"
#define IOSVC_GFXACCEL "IOGraphicsAccelerator2"
#define IOSVC_ACCEL "IOAcceleratorES"
#endif /* iokit_h */
