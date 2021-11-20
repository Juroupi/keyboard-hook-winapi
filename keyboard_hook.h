#ifndef _KEYBOARD_HOOK_H_
#define _KEYBOARD_HOOK_H_

#include <windows.h>

typedef enum _HookReturn {
    HOOK_CONTINUE, /* continue hook */
    HOOK_STOP, /* stop hook */
    HOOK_BLOCK /* continue hook and prevent other processes to receive the event */
} HookReturn;

typedef struct _KeyEvent {
    int keycode; /* virtual key code */
    int scancode; /* scancode */
    int extended; /* if the key is extended */
    int down; /* if the key is pressed */
    int injected; /* if the event was injected by an other process */
} KeyEvent;

/** 
 * Function called at each keyboard event
 * @param keyDown for each keycode: 0 if the key is released, the number of repetitions otherwise
 * @return a value of HookReturn
 */
typedef int (*KeyboardHookCallback)(const KeyEvent* event, const int keyDown[256]);

/** 
 * Start keyboard hook
 * @return 0 if it fails, another value otherwise
 */
int keyboardHook(KeyboardHookCallback callback);

#endif