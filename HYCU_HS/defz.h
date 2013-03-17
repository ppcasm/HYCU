
#define HW_GPIO_IOA         (volatile unsigned int *)0x88200074
#define HW_TV_CLOCK_CONF    (volatile unsigned int*)0x88210030
#define HW_TV_VDAC_CTRL     (volatile unsigned int*)0x88030050
#define HW_TV_MODE		    (volatile unsigned int*)0x88030000
#define HW_TV_BUF1 		    (volatile unsigned int*)0x88070000
#define HW_TV_BUF2    	    (volatile unsigned int*)0x88070004
#define HW_TV_BUF3    	    (volatile unsigned int*)0x88070008
#define HW_TV_BUF_SEL       (volatile unsigned int*)0x88090020
#define CON_TV_CLOCK_EN            0x00000001
#define CON_TV_RESET_DIS           0x00000002
#define CON_TV_VDAC_EN	           0x00000000
#define CON_TV_CTRL_EN             0x00001000
#define CON_TV_NTSC		           0x00000000
#define CON_TV_VGA_MODE            0x00000004
#define CON_TV_RGB_MODE            0x00000100
#define CON_TV_RGB565_MODE         0x00000000
#define CON_TV_INTERLACE_MODE      0x00000001
#define CON_TV_NTSC_TYPE           0x00000000
#define CON_TV_LE			       0x00000000

#define CLOCK (1<<24) //Goes to pin  
#define DATA (1<<25) //Goes to pin

//Globalize framebuffer pointer
unsigned short *fb = (unsigned short *)0;

void video_init(void);
void video_drawbg(void);
void video_hexdump(int cx, int cy, unsigned long x, unsigned short colorzz);
void video_print(int x, int y, char *text, unsigned short colorz);
void video_clearscreen(void);
unsigned char recv_byte(void);