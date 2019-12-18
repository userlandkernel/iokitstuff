//
//  AppDelegate.h
//  Zeroday
//
//  Created by Sem Voigtländer on 17/12/19.
//  Copyright © 2019 kernelprogrammer. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreData/CoreData.h>

@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;

@property (readonly, strong) NSPersistentContainer *persistentContainer;

- (void)saveContext;


@end

