
#include "PixelSpace.h"

void PixelSpace::init() {}
PixelSpace::PixelSpace() { mWindowTitle = u8"PixelSpace"; }

int main(int argc, char* argv[])
{
	PixelSpace pixelSpace;
	pixelSpace.run(argc, argv);

    return 0;
}