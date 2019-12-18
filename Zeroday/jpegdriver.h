//
//  jpegdriver.h
//  Zeroday
//
//  Created by Sem Voigtländer on 18/12/19.
//  Copyright © 2019 kernelprogrammer. All rights reserved.
//

#ifndef jpegdriver_h
#define jpegdriver_h

#include <stdio.h>
#include "iokit.h"
#include <IOSurface/IOSurfaceRef.h>
struct JPEGDriverArgs {
    int must_be_zero_1;
    IOSurfaceID src_surface /*in*/;
    size_t src_size /*in*/;
    int must_be_zero_2;
    IOSurfaceID dest_surface /*in*/;
    size_t dest_size /*in*/;
    size_t result_size /*out*/;
    size_t dest_width /*in*/;
    size_t dest_height /*in*/;
    int quality /*in: 4 gives decent quality */;
};
enum AppleJPEGDriverAction {
    kAppleJPEGDecoderInitAction = 0,
    kAppleJPEGDecoderStartAction = 1,
    kAppleJPEGEncoderInitAction = 2,
    kAppleJPEGEncoderStartAction = 3
};
kern_return_t AppleJPEGDriverDecoderInit(void);
kern_return_t AppleJPEGDriverEncoderInit(void);
kern_return_t AppleJPEGDriverDecoderStart(struct JPEGDriverArgs args);
kern_return_t AppleJPEGDriverEncoderStart(struct JPEGDriverArgs args);
#endif /* jpegdriver_h */
