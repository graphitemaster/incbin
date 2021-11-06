#include <assert.h>
#include <stdlib.h>
#include "../incbin.h"

INCBIN(Lorem, "loremipsum.txt");
INCBIN(Onebyte, "onebyte.txt");
INCBIN(Sevenbytes, "sevenbytes.txt");

INCBIN(char, CharLorem, "loremipsum.txt");
INCBIN(char, CharOnebyte, "onebyte.txt");
INCBIN(char, CharSevenbytes, "sevenbytes.txt");

INCTXT(TLorem, "loremipsum.txt");

int main(int argc, char **argv)
{
	assert(gLoremSize==962);
	assert(&gLoremData[gLoremSize] == (const unsigned char*) &gLoremEnd);

	assert(gOnebyteSize == 1);
	assert(&gOnebyteData[gOnebyteSize] == (const unsigned char*) &gOnebyteEnd);

	assert(gSevenbytesSize==7);
	assert(&gSevenbytesData[gSevenbytesSize] == (const unsigned char*) &gSevenbytesEnd);

	assert(gCharLoremSize==962);
	assert(&gCharLoremData[gCharLoremSize] == (const char*) &gCharLoremEnd);

	assert(gCharOnebyteSize == 1);
	assert(&gCharOnebyteData[gCharOnebyteSize] == (const char*) &gCharOnebyteEnd);

	assert(gCharSevenbytesSize==7);
	assert(&gCharSevenbytesData[gCharSevenbytesSize] == (const char*) &gCharSevenbytesEnd);

	assert(gTLoremSize==963);
	assert(&gTLoremData[gTLoremSize] == (const char*) &gTLoremEnd);

	exit(0);
}
