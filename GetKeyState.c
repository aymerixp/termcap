/*
 * source http://stackoverflow.com/questions/9009775/using-getkeystatevk-capital-1-in-linux
 * gcc -lX11 GetKeyState.c
 * */
#include <stdio.h>
#include <X11/XKBlib.h>

int main() {
	Display * d = XOpenDisplay((char*)0);

	if (d) {
		unsigned n;

		XkbGetIndicatorState(d, XkbUseCoreKbd, &n);

		// cool ca :
		printf((n & 1)?"caps on\n":"caps off\n");
	}
}

