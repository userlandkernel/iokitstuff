//
//  iocoresurfaceroot.h
//  Zeroday
//
//  Created by Sem Voigtländer on 18/12/19.
//  Copyright © 2019 kernelprogrammer. All rights reserved.
//

#ifndef iocoresurfaceroot_h
#define iocoresurfaceroot_h

#include <stdio.h>
#include <IOSurface/IOSurfaceRef.h>
#include <IOSurface/IOSurfaceTypes.h>
#include "iokit.h"

enum IOCoreSurfaceRootAction {
    kIOCoreSurfRootCreateAction = 0,
    kIOCoreSurfRootReleaseAction = 1,
    kIOCoreSurfRootLockAction = 2,
    kIOCoreSurfRootUnlockAction = 3,
    kIOCoreSurfRootLockPlaneAction = 4,
    kIOCoreSurfRootUnlockPlaneAction = 5,
    kIOCoreSurfRootLookupAction = 6,
    kIOCoreSurfRootSetYCBMatrixAction = 7,
    kIOCoreSurfRootWrapClientImageAction = 8,
    kIOCoreSurfRootWrapClientMemoryAction = 9,
    kIOCoreSurfRootGetYCBMatrixAction = 10,
    kIOCoreSurfRootSetValueAction = 11,
    kIOCoreSurfRootCopyValueAction = 12,
    kIOCoreSurfRootRemoveValueAction = 13,
    kIOCoreSurfRootBindAccelAction = 14,
    kIOCoreSurfRootBindAccelOnPlaneAction = 15,
    kIOCoreSurfRootReadLimitsAction = 16,
    kIOCoreSurfRootIncrementUseCountAction = 17,
    kIOCoreSurfRootDecrementUseCountAction = 18,
    kIOCoreSurfRootSetSurfaceNotifyAction = 20,
    kIOCoreSurfRootRemoveSurfaceNotifyAction = 21,
    kIOCoreSurfRootSetTiledAction = 24,
    kIOCoreSurfRootIsTiledAction = 25
};

struct IOSrufaceWrapArg {
    uint64_t address;
    uint32_t width;
    uint32_t height;
    uint32_t format; // 4cc code, e.g. 'BGRA'
    uint32_t elementBytes;
    uint32_t rowBytes;
    uint32_t allocSize;
};

struct IOSurfaceSharedData {
    uint32_t unknown0[2]; // related to IOAccelerator
    uint32_t seed;
    uint32_t useCount;
    uint32_t YCbCrMatrix;
    uint32_t maxValueSizeHint; // hint - maximum serialized size of any surface value (aka - those set via setValue)
};

struct IOSurfaceLimits {
    uint32_t addressAlignMask; // e.g. 3 for 4-byte alignment
    uint32_t rowBytesAlignMask; // e.g. 3 for 4-byte alignment
    uint32_t rowBytesMax;
    uint32_t widthMax;
    uint32_t heightMax;
};

struct IOSurfacePlaneData {
    uint64_t sharedData; // pointer to IOSurfaceSharedData, driver-mapped
    uint32_t width;
    uint32_t height;
    uint32_t unknown0; // plane base?
    uint32_t offset;
    uint32_t rowBytes;
    uint32_t unknown1; // plane size?
    uint16_t elementBytes;
    uint8_t elementWidth;
    uint8_t elementHeight;
    uint32_t seed;
};

struct IOSurfaceData {
    uint64_t address;
    uint64_t sharedData;
    IOSurfaceID surfaceID;
    uint32_t allocSize;
    uint32_t width;
    uint32_t height;
    uint32_t rowBytes;
    uint32_t offset;
    uint32_t format; // 4cc, e.g. 'BGRA'
    uint32_t unknown0; // might be allocSize, rounded up to page size?
    uint32_t numPlanes;
    uint32_t unknown1;
    uint16_t elementBytes;
    uint8_t elementWidth;
    uint8_t elementHeight;
    uint32_t cacheMode;
    uint32_t unknown2[2]; // one of these might be 'seed'
    struct IOSurfacePlaneData planes[32];
};

struct IOSurfaceLockArg {
    IOSurfaceID surfaceID;
    uint32_t    lockOptions;
    size_t      planeIndex;
};

struct IOSurfaceLockSeedArg {
    uint32_t    seed;
};

struct IOSurfaceSetValueArg {
    IOSurfaceID surfaceID;
    
    // XML PList - array of size 2
    //   [0] - value (any object)
    //   [1] - key (string)
    char setValuePList[0];
};

struct IOSurfaceCopyValueArg {
    IOSurfaceID surfaceID;
    char keyName[0];
};

struct IOSurfaceCreateArg {
    // XML PList dictionary with keys:
    //   IOSurfaceWidth
    //   IOSurfaceHeight
    //   IOSurfaceBytesPerRow
    //   IOSurfaceBytesPerElement
    //   IOSurfaceElementWidth
    //   IOSurfaceElementHeight
    //   IOSurfacePixelFormat
    //   IOSurfaceAllocSize
    //   IOSurfaceTileMode (also IOSurfaceBufferTileMode?)
    //   IOSurfaceCacheMode
    //   IOSurfaceOffset
    //   IOSurfaceIsGlobal
    //   IOSurfaceMemoryRegion
    //   IOSurfacePurgeWhenNotInUse
    //   IOSurfacePlaneInfo - array of dictionaries with keys:
    //     IOSurfacePlaneWidth
    //     IOSurfacePlaneHeight
    //     IOSurfacePlaneBytesPerRow
    //     IOSurfacePlaneBytesPerElement
    //     IOSurfacePlaneElementWidth
    //     IOSurfacePlaneElementHeight
    //     IOSurfacePlaneOffset
    //     IOSurfacePlaneBase
    //     IOSurfacePlaneSize
    char createPList[0];
};

typedef struct IntSize {
    uint32_t width;
    uint32_t height;
} IntSize;

kern_return_t IOCoreSurfaceRootCreate(uint32_t allocSize, IOSurfaceID* surfaceID);
#endif /* iocoresurfaceroot_h */
