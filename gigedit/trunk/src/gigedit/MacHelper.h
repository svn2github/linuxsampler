/*
    Copyright (c) 2013 Christian Schoenebeck
    
    This file is part of "gigedit" and released under the terms of the
    GNU General Public License version 2.
*/

#ifndef GIGEDIT_MAC_HELPER
#define GIGEDIT_MAC_HELPER

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

/**
 * Run the given C callback function @a fn on the process's main thread. This
 * function will return immediately. The callback function will be scheduled
 * for asynchronous execution. In general this function will only succeed if
 * if there is a CoreFoundation event loop established and running in this
 * process, if not, the callback function will never be executed!
 *
 * @param fn - callback function to be executed on main thread
 * @param info - arbitrary pointer which will be passed to the callback call
 */
void macHelperRunCFuncOnMainThread(void (*fn)(void* info), void* info);

#if defined(__cplusplus)
}
#endif // __cplusplus

#endif // GIGEDIT_MAC_HELPER
