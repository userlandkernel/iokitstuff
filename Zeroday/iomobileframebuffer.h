//
//  iomobileframebuffer.h
//  Zeroday
//
//  Created by Sem Voigtländer on 18/12/19.
//  Copyright © 2019 kernelprogrammer. All rights reserved.
//

#ifndef iomobileframebuffer_h
#define iomobileframebuffer_h

#include <stdio.h>
#include <mach/mach.h>
#include <float.h>
#include <math.h>
#include <stdint.h>
#include <IOKit/IOKitLib.h>
#include <IOKit/IOKitKeys.h>
#include <IOKit/graphics/IOFramebufferShared.h>
#include <IOSurface/IOSurfaceTypes.h>
#include <CoreFoundation/CoreFoundation.h>

typedef uint32_t IOSwapNotificationID;
typedef struct UInt32Rect {
    uint32_t x, y, width, height;
} UInt32Rect;

typedef struct UInt8Bgra {
    uint8_t b, g, r, a;
} UInt8Bgra;

typedef uint32_t IOMobileFramebufferSwapID;
typedef uint32_t IOMobileFramebufferSwapFlags;

// From the iPhoneWiki (Not all actions will work as expected)
enum IOMobileFramebufferAction {
    kIOMBFGetDefaultSurfaceAction = 3,
    kIOMBFSwapBeginAction = 4,
    kIOMBFSwapEndAction = 5,
    kIOMBFSwapWaitAction = 6,
    kIOMBFGetIdAction = 7,
    kIOMBFGetDisplaySizeAction = 8,
    kIOMBFSetVSyncNotificationsAction = 9,
    kIOMBFRequestPowerChangeAction = 12,
    kIOMBFSetDebugFlagsAction = 15,
    kIOMBFSetGammaTableAction = 17,
    kIOMBFIsMainDisplayAction = 18,
    kIOMBFSetWhiteOnBlackModeAction = 19,
    kIOMBFSetDisplayDeviceAction = 22,
    kIOMBFGetGammaTableAction = 27,
    kIOMBFSetVideoPowerSavingAction = 33, // Doubt it still works
    kIOMBFSetBrightnessCorrectionAction = 50, // Doubt it still works
};

struct IOMobileFramebufferSwapArg {
    int64_t timeStamps[3];
    uint64_t imageSources[16]; // ?
    uint32_t numImageSources; // 0..16
    uint32_t padding;
    IOMobileFramebufferSwapID swapID;
    IOSurfaceID surfaceID[4];
    UInt32Rect bounds[4]; // surface source bounds
    UInt32Rect uiSubRegion[4]; // ?
    uint32_t edgeMode[4]; // ?
    Float32 edgeCoverage[4]; // ?
    UInt32Rect frames[4]; // framebuffer target frame
    IOMobileFramebufferSwapFlags providedFlags; // which layers are provided for swap (in this structure)
    IOMobileFramebufferSwapFlags readyFlags; // which layers are ready to be swapped (layers that aren't ready must be notified as ready later via layer swap notifications)
    UInt8Bgra bgColor;
    uint32_t gammaTable; // 0..2, index to gamma table to use
    uint32_t rotation[4]; // 0 - none, 1 - 90 left, 2 - 180, 3 - 90 right
    uint32_t destEdgeAlpha; // ?
    uint32_t unknown[2];
};

struct IOMobileFramebufferDisplaySize {
    uint32_t width;
    uint32_t height;
};

struct IOMobileFramebufferGammaTables {
    struct GammaTable {
        uint32_t value[0x101];
    } gammaTable[3];
};

typedef struct {
    int64_t low32; // low 32 bits of 64 bit value. (upper bits are wasted)
    int64_t high32; // high 32 bits of 64 bit value. (upper bits are wasted)
} int64wtf;

struct IOMobileFramebufferTimingData {
    int64wtf frameNumber; // frame number
    int64wtf frameTime; // frame time, mach absolute time
    int64wtf frameDuration; // duration of last frame, mach absolute time
};

kern_return_t IOMobileFrameBufferSetDebugFlags(uint32_t *debugFlags); // INPUT is OUTPUT
kern_return_t IOMobileFrameBufferGetDefaultSurface(IOSurfaceID* surfaceID);
kern_return_t IOMobileFramebufferSwapBegin(IOMobileFramebufferSwapID* swapID);
kern_return_t IOMobileFramebufferSwapEnd(struct IOMobileFramebufferSwapArg swapArg);
kern_return_t IOMobileFramebufferGetID(IOSwapNotificationID* framebufferID);
kern_return_t IOMobileFramebufferGetDisplaySize(struct IOMobileFramebufferDisplaySize* displaySize);
kern_return_t IOMobileFramebufferSetVsyncNotifications(size_t functionAddress, size_t userData);
kern_return_t IOMobileFramebufferSetDisplayDevice(uint32_t device);
kern_return_t IOMobileFrameBufferIsMainDisplay(bool *isMainDisplay);
kern_return_t IOMobileFrameBufferSetWhiteOnBlackMode(bool enabled);
kern_return_t IOMobileFrameBufferGetGammaTables(struct IOMobileFramebufferGammaTables *gammaTables);
kern_return_t IOMobileFrameBufferSetGammaTables(struct IOMobileFramebufferGammaTables gammaTables);
kern_return_t IOMobileFramebufferSetVideoPowerSaving(uint32_t value);
kern_return_t IOMobileFramebufferSetBrightnessCorrection(uint32_t value);
kern_return_t IOMobileFramebufferResetGammaTables(void);
#endif /* iomobileframebuffer_h */
