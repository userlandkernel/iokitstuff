//
//  ViewController.m
//  Zeroday
//
//  Created by Sem Voigtländer on 17/12/19.
//  Copyright © 2019 kernelprogrammer. All rights reserved.
//

#import "ViewController.h"
#include "jpegdriver.h"
#include "iomobileframebuffer.h"
#include "iocoresurfaceroot.h"
#include "ioaccelerator.h"

@interface ViewController ()
- (IBAction)boostBtnTap:(id)sender;
@property (weak, nonatomic) IBOutlet UIButton *boostBtn;
@property BOOL isBoosting;
@end

@implementation ViewController


- (void)viewDidLoad {
    [super viewDidLoad];
    printf("Ready to boost your experience :)\n");
    struct AGXSharedMemArg mem = {};
    IOAcceleratorESCreateSharedMemory(0x100, &mem);
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}
- (IBAction)boostBtnTap:(id)sender {
    
    kern_return_t err = KERN_SUCCESS;
    if(![self isBoosting]){
        err = IOMobileFramebufferSetBrightnessCorrection(0x1);
        if(err != KERN_SUCCESS) {
            [_boostBtn setTitle:@"Boosting unsupported" forState:UIControlStateDisabled];
            [_boostBtn setTitleColor:[UIColor redColor] forState:UIControlStateDisabled];
        }
        
        err = IOMobileFramebufferSetVideoPowerSaving(0x10000);
        if(err != KERN_SUCCESS) {
            [_boostBtn setTitle:@"Boosting unsupported" forState:UIControlStateDisabled];
            [_boostBtn setTitleColor:[UIColor redColor] forState:UIControlStateDisabled];
        }

        [_boostBtn setTitle:@"Revert Framebuffer" forState:UIControlStateNormal];
        [self setIsBoosting:YES];
    }
    else {
        err = IOMobileFramebufferSetBrightnessCorrection(0);
        if(err != KERN_SUCCESS) {
            [_boostBtn setTitle:@"Boosting unsupported" forState:UIControlStateDisabled];
            [_boostBtn setTitleColor:[UIColor redColor] forState:UIControlStateDisabled];
        }
        
        err = IOMobileFramebufferSetVideoPowerSaving(0);
        if(err != KERN_SUCCESS) {
            [_boostBtn setTitle:@"Boosting unsupported" forState:UIControlStateDisabled];
            [_boostBtn setTitleColor:[UIColor redColor] forState:UIControlStateDisabled];
        }
        [_boostBtn setTitle:@"Boost Framebuffer" forState:UIControlStateNormal];
        [self setIsBoosting:NO];
    }
    
}
@end
