#ifndef vc_tags_c
#define vc_tags_c

#include <stdarg.h>

// NOT ALL TAGS IMPLEMENTED YET

#define VC_TAGS_BUFFER_SIZE 1024

struct vctags {
	unsigned int buffer[VC_TAGS_BUFFER_SIZE] __attribute__((aligned(16)));
	unsigned int ptr;
} vctags;

void vc_tagmanager_init(void) {
	vctags.buffer[0] = VC_TAGS_BUFFER_SIZE;	// total size
	vctags.buffer[1] = 0;					// request / response code
	vctags.buffer[2] = 0;					// end tag indicator
	vctags.ptr = 2;
	int i;
	for(i = vctags.ptr; i < VC_TAGS_BUFFER_SIZE; i++) vctags.buffer[i] = 0; // just zero out data
}

void vc_tagmanager_add(unsigned int tag, ...) {
	va_list args;
	va_start(args, tag);
	vctags.buffer[vctags.ptr++] = tag; // add tag to previous end tag indicator
    switch (tag) {
        case TAG_FIRMWARE_VERSION:
        case TAG_BOARD_MODEL:
        case TAG_BOARD_REVISION:
        case TAG_BOARD_MAC_ADDRESS:
        case TAG_BOARD_SERIAL:
        case TAG_ARM_MEMORY:
        case TAG_VC_MEMORY:
        case TAG_DMA_CHANNELS:
            vctags.buffer[vctags.ptr++] = 8;
            vctags.buffer[vctags.ptr++] = 0;
        	vctags.ptr += (8 >> 2);
            break;
        case TAG_CLOCKS:
        case TAG_COMMAND_LINE:
            vctags.buffer[vctags.ptr++] = 256;
            vctags.buffer[vctags.ptr++] = 0;
            vctags.ptr += (256 >> 2);
            break;
        case TAG_ALLOCATE_BUFFER:
            vctags.buffer[vctags.ptr++] = 8;
            vctags.buffer[vctags.ptr++] = 4;
            vctags.buffer[vctags.ptr++] = va_arg(args, unsigned int);
			vctags.buffer[vctags.ptr++] = 0x0;
            break;
		case TAG_GET_PHYSICAL_SIZE:
	    case TAG_GET_VIRTUAL_SIZE:
	    case TAG_GET_VIRTUAL_OFFSET:
			vctags.buffer[vctags.ptr++] = 8;
			vctags.buffer[vctags.ptr++] = 0;
			vctags.ptr += 2;
			break;
	    case TAG_SET_VIRTUAL_OFFSET:
		case TAG_SET_PHYSICAL_SIZE:
		case TAG_SET_VIRTUAL_SIZE:
		case TAG_TEST_VIRTUAL_SIZE:
	    case TAG_TEST_PHYSICAL_SIZE:
			vctags.buffer[vctags.ptr++] = 8;
			vctags.buffer[vctags.ptr++] = 0;
			vctags.buffer[vctags.ptr++] = va_arg(args, unsigned int);	// Width
			vctags.buffer[vctags.ptr++] = va_arg(args, unsigned int);	// Height
			break;
        case TAG_GET_ALPHA_MODE:
        case TAG_GET_DEPTH:
        case TAG_GET_PIXEL_ORDER:
        case TAG_PITCH:
			vctags.buffer[vctags.ptr++] = 4;
			vctags.buffer[vctags.ptr++] = 0;
			vctags.ptr += 1;
			break;
		case TAG_SET_ALPHA_MODE:
		case TAG_SET_DEPTH:
		case TAG_SET_PIXEL_ORDER:
            vctags.buffer[vctags.ptr++] = 4;
            vctags.buffer[vctags.ptr++] = 0;
			vctags.buffer[vctags.ptr++] = va_arg(args, unsigned int);
			break;
        case TAG_GET_OVERSCAN:
			vctags.buffer[vctags.ptr++] = 16;
			vctags.buffer[vctags.ptr++] = 0;
			vctags.ptr += 4;
			break;
        case TAG_SET_OVERSCAN:
			vctags.buffer[vctags.ptr++] = 16;
			vctags.buffer[vctags.ptr++] = 0;
            vctags.buffer[vctags.ptr++] = va_arg(args, unsigned int);	// Top pixels
            vctags.buffer[vctags.ptr++] = va_arg(args, unsigned int);	// Bottom pixels
            vctags.buffer[vctags.ptr++] = va_arg(args, unsigned int);	// Left pixels
            vctags.buffer[vctags.ptr++] = va_arg(args, unsigned int);	// Right pixels
            break;
        default:
            // Unsupported tag
            vctags.ptr--;
            break;
    }
    // update null bit at the end
    vctags.buffer[vctags.ptr] = 0;
	va_end(args);
}

unsigned long vc_tagmanager_get(unsigned int tag) {
	// return address of tag in buffer
	unsigned int i = 2;
	while(i < VC_TAGS_BUFFER_SIZE) {
		if(vctags.buffer[i] == 0) return 0; // not found
		if(vctags.buffer[i] == tag) {
			return (unsigned long)i;
		}
		i++;
		i += (vctags.buffer[i] >> 2) + 2;
	}
	return 0;
}

void vc_tagmanager_remove(unsigned int tag) {
}

unsigned int vc_tagmanager_gettagsize(unsigned int tag) {
	unsigned int p = vc_tagmanager_get(tag);
	return (vctags.buffer[p + 1] >> 2) + 3;
}

#endif
