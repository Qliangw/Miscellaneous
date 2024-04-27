#include <stdio.h>
#include "version.h"

int main(void)
{
	printf("version test\n");
	printf("firmware version: v%d.%d.%d\n",
		((firmware_version.version >> 6) & 0x03), 
		(firmware_version.version >> 4) & 0x03,
		(firmware_version.version & 0x0F));
	printf("compiling data: %d-%d-%d\n",
		firmware_version.comp0 + 2000,
		(firmware_version.comp1 >> 4 & 0x0F),
		firmware_version.comp2 >> 3 & 0x1f);
	printf("compiling time: %d:%d:%d %s\n",
		firmware_version.comp1 & 0x0f,
		firmware_version.comp3 & 0x3f,
		firmware_version.comp4 & 0x3f,
		((firmware_version.comp2 >> 2) & 0x01 ?("PM"):("AM")) );
	return 0;
}
