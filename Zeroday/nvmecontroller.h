//
//  nvmecontroller.h
//  iokitstuff
//
//  Created by Sem Voigtländer on 28/01/20.
//  Copyright © 2020 kernelprogrammer. All rights reserved.
//

#ifndef nvmecontroller_h
#define nvmecontroller_h

#include <stdio.h>
#include <mach/mach.h>
#include <float.h>
#include <math.h>
#include <stdint.h>
#include <IOKit/IOKitLib.h>
#include <IOKit/IOKitKeys.h>
#include <CoreFoundation/CoreFoundation.h>
#include "iokit.h"
enum AppleEmbeddedNVMeControllerAction {
    kNVMECTL_sendNVMECommandAction = 2,
    kNVMECTL_isBFHModeAction = 3,
    kNVMECTL_performBFHAction = 4,
    kNVMECTL_getNandDescriptorAction = 5,
    kNVMECTL_setNVMeStateAction = 6,
    kNVMECTL_setPCIPortStateAction = 7,
    kNVMECTL_setBFHGPIOAction = 8,
};

struct NVMeIdentifyControllerStruct {
    char unknown[0x1000];
};
#endif /* nvmecontroller_h */
