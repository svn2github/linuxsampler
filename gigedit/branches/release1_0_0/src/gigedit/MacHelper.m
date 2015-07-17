/*
    Copyright (c) 2013 Christian Schoenebeck
    
    This file is part of "gigedit" and released under the terms of the
    GNU General Public License version 2.
*/

#import "MacHelper.h"
#import <Cocoa/Cocoa.h>
#import <stdio.h>

@interface MacHelper : NSObject {
@public
    void (*m_fn)(void* info);
    void* m_info;
}
@end

@implementation MacHelper

- (id)init {
    if ((self = [super init])) {
        m_fn   = nil;
        m_info = nil;
    }
    return self;
}

- (void)runCFunc {
    (*m_fn)(m_info);
}

@end

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

void macHelperRunCFuncOnMainThread(void (*fn)(void* info), void* info) {
    MacHelper* obj = [[MacHelper alloc] init];
    obj->m_fn = fn;
    obj->m_info = info;
    printf("perfoming selector on main thread ...\n"); fflush(stdout);
    [obj performSelectorOnMainThread:@selector(runCFunc) withObject:obj waitUntilDone:NO];
    printf("Selector scheduled async. (on main thread).\n"); fflush(stdout);
    [obj release];
}

#if defined(__cplusplus)
}
#endif // __cplusplus
