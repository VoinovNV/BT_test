#include <stdio.h>
#include <string.h>
#define LOCKED 0
#define UNLOCKED 1
char com[15] = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
int i = 0;
int LOCK = LOCKED;
int S_strcmp(const char* a, const char* b) {
	int k = 0;
	for (int j = 0; j < 15; j++) {
		k+= (a[j]!= b[j]);
	}
	return k;
}
static void feed(int c)
{
	if (i <= 14) {
		com[i] = c; i++;
	}
	else {
		com[0] = '\0'; i = 1;
	}

	if (c == '\n') {
		// FIXME Make me safe
		com[i - 1] = '\0';
		i = 0;
		int ok=1;
		if (!S_strcmp(com, "LOCK\0\0\0\0\0\0\0\0\0\0\0")) { 
			LOCK = LOCKED; 
			ok--;
			puts("OK"); 
		}
		if (!S_strcmp(com, "UNLOCK 1234\0\0\0\0")) {
			LOCK = UNLOCKED; 
			ok--;
			puts("OK");
		}
		if (!S_strcmp(com, "SECRET\0\0\0\0\0\0\0\0\0") && LOCK == UNLOCKED) { puts("OK My super secret!"); }
		if(ok) puts("FAIL");
		memset(com, '\0', 15);
	}
}
int main() {
	do {
		int c = getc(stdin);
		if (c == EOF)
			break;
		feed(c);
	} while (1);
	return 0;
}