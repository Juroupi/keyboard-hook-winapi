# keyboard-hook-winapi
Create a keyboard hook in c on windows

### Example

```c
#include <stdio.h>
#include "keyboard_hook.h"

int callback(const KeyEvent* event, const int keyDown[256]) {

	// display the key code
	printf("%d\n", event->keycode);

	// stop when A key is pressed
	if (event->keycode == 'A') {
		return HOOK_STOP;
	}

	return HOOK_CONTINUE;
}

int main() {

	if (!keyboardHook(callback)) {
		return 1;
	}

	return 0;
}
```

