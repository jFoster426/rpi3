#ifndef framebuffer_c
#define framebuffer_c

#include "mailbox.c"
#include "vc_tags.c"
#include "memory.c"

struct framebuffer {
	unsigned int base;
	unsigned int size;
	unsigned int pitch;
	unsigned int screen_width;
	unsigned int screen_height;
	unsigned int color_depth;
} framebuffer;

unsigned char framebuffer_init(int screen_width, int screen_height, int color_depth) {
	framebuffer.screen_width = screen_width;
	framebuffer.screen_height = screen_height;
	framebuffer.color_depth = color_depth;
	vc_tagmanager_init();
	vc_tagmanager_add(TAG_SET_PHYSICAL_SIZE, screen_width, screen_height);
	vc_tagmanager_add(TAG_SET_VIRTUAL_SIZE, screen_width, screen_height);
	vc_tagmanager_add(TAG_SET_DEPTH, color_depth);
	vc_tagmanager_add(TAG_PITCH);
	vc_tagmanager_add(TAG_ALLOCATE_BUFFER, 16);
	mailbox0_write(8, (unsigned long)vctags.buffer | 0xC0000000);
	unsigned int data = mailbox0_read(8) & 0x3fffffff; // convert back to ARM memory
	if(data != (unsigned long)vctags.buffer) return 1;
	return 0;
}

void framebuffer_allocate() {
	unsigned int b = vc_tagmanager_get(TAG_ALLOCATE_BUFFER);
	unsigned int p = vc_tagmanager_get(TAG_PITCH);
	framebuffer.base = vctags.buffer[b + 3] & 0x3fffffff;
	framebuffer.size = vctags.buffer[b + 4];
	framebuffer.pitch = vctags.buffer[p + 3];
}

void framebuffer_write(unsigned int offset, unsigned int value) {
	if(offset >= (framebuffer.size) || offset % 4 != 0) {
		return;
	}
	put32(framebuffer.base + offset, value);
}

#endif
