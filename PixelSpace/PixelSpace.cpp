
#include "PixelSpace.h"

void PixelSpace::init() {}
PixelSpace::PixelSpace() { mWindowTitle = u8"PixelSpace"; }

int main()
{
	PixelSpace pixelSpace;
	pixelSpace.run();

    return 0;
}