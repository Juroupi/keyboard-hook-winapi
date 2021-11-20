#include "keyboard_hook.h"

#include <windows.h>


static KeyboardHookCallback userCallback = NULL;

static int keyDown[256] = { 0 };


static LRESULT CALLBACK defaultCallback(int code, WPARAM wParam, LPARAM lParam) {

	if (code == HC_ACTION) {

		KBDLLHOOKSTRUCT* kbdHookStruct = (KBDLLHOOKSTRUCT*)lParam;

		KeyEvent event;

		event.keycode = (int)kbdHookStruct->vkCode;
		event.scancode = (int)kbdHookStruct->scanCode;
		event.extended = (kbdHookStruct->flags & LLKHF_EXTENDED) != 0;
		event.down = (kbdHookStruct->flags & LLKHF_UP) == 0;
		event.injected = (kbdHookStruct->flags & (LLKHF_INJECTED | LLKHF_LOWER_IL_INJECTED)) != 0;

		if (event.down) {
			keyDown[event.keycode]++;
		}

		else {
			keyDown[event.keycode] = 0;
		}

		HookReturn ret = userCallback(&event, keyDown);

		if (ret == HOOK_STOP) {
			PostQuitMessage(0);
		}

		else if (ret == HOOK_BLOCK) {
			return 1;
		}
	}

	return CallNextHookEx(NULL, code, wParam, lParam);
}


int keyboardHook(KeyboardHookCallback callback) {
	
	HHOOK hook;
	MSG msg;

	userCallback = callback;

	hook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)defaultCallback, NULL, 0);
	if (hook == NULL) {
		return 0;
	}

	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnhookWindowsHookEx(hook);

	return 1;
}