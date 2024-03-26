#include <iostream>
#include <stdlib.h>
#include <string>

#define STRLEN			128
#define OK				0
#define MEMORY_ERR		1
#define INPUT_ERR		2
using namespace std;


extern "C" {
	void strcopy(char* dst, char* src, int len);
}

int asmstrlen(char* s) {
	int len = 0;
	__asm {
		mov esi, 0
		mov ebx, [s]
		strLeng:
		cmp[ebx + esi], 0
			je breakLength
			inc esi
			jmp strLeng
			breakLength :
		mov len, esi
	}

	return len;
}

int main(void) {
	int rc = OK;
	int len = 0;

	char* s = (char*)calloc(STRLEN, sizeof(char));
	if (!s) {
		rc = MEMORY_ERR;
	}

	if (!rc) {
		len = asmstrlen(s);
		cout << "asmstrlen result: " << len << '\n';
	}

	char* src = NULL;
	if (!rc) {
		src = (char*)calloc(STRLEN, sizeof(char));
		if (!src)
			rc = MEMORY_ERR;
	}

	if (!rc) {
		cout << "Entered: " << src << '\n';
	}

	char* dst = NULL;
	if (!rc) {
		dst = (char*)calloc(STRLEN, sizeof(char));
		if (!dst) {
			rc = MEMORY_ERR;
		}
	}

	if (!rc) {
		int srclen = asmstrlen(src);
		strcopy(dst, src, srclen);
		cout << "Copied: " << dst << '\n';
	}

	if (s) free(s);
	if (src) free(src);
	if (dst) free(dst);

	return rc;
}
