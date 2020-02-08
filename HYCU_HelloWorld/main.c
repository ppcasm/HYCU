/*
HYCU - HYperscan Code Uploader by ppcasm (ppcasm@gmail.com) (HyperScan Side)

*/
//#include "image.h"
#include "font.h"
#include "defz.h"

int main()
{
	
	video_init();
    video_drawbg();

    video_print((640/8)/2-sizeof("Hello World!")/2, 4, "Hello World!", 0xffff);
	
  return 0;
}

unsigned long calc_chksum32(unsigned char *pointz, unsigned long codesize)
{
	int i = 0;
	int chksum32 = 0;
	for(i=0;i<codesize;i++)
	{
		chksum32+=pointz[i];
	}
	
  return chksum32;
}

void video_print(int x, int y, char *text, unsigned short colorzz)
{
    short xx, yy;
    unsigned short colorz;
    while (*text) 
    {
        for (yy = 0; yy < 16; yy++) 
        {
	      for (xx = 0; xx < 8; xx++)
	      {
            if(font[(*text)*16+yy] & (1<<(8-xx))) colorz = colorzz; else colorz = fb[(y*16+yy)*640+(x*8+xx)];
	        fb[(y*16+yy)*640+(x*8+xx)] = colorz;
	      }
	}
	x++;
	text++;
    }
    
  return;
}

unsigned char recv_byte(void)
{
	unsigned char bytez = 0;
	int x;
	int trap = 1;
	for(x=0;x<8;x++)
	{
		trap = 1;
		while(trap)
	    {
	       if(*HW_GPIO_IOA & CLOCK) trap = 0; else trap = 1;
	    }
	    
		if(*HW_GPIO_IOA & DATA) bytez+=(1<<x); 
		while(*HW_GPIO_IOA & CLOCK){} 
	}

  return bytez;	
}

void video_init()
{
     if(*HW_GPIO_IOA == 0) fb = (unsigned short *) 0x9e000000; else fb = (unsigned short *) 0xA0400000;
    
     *HW_TV_CLOCK_CONF = CON_TV_CLOCK_EN | CON_TV_RESET_DIS;
     *HW_TV_VDAC_CTRL  = CON_TV_VDAC_EN;
     *HW_TV_MODE       = CON_TV_CTRL_EN
	     	  	   	   | CON_TV_NTSC
		     		   | CON_TV_INTERLACE_MODE
				       | CON_TV_NTSC_TYPE
				       | CON_TV_LE;


     *HW_TV_MODE 	   |= CON_TV_VGA_MODE;
     *HW_TV_MODE	   |= CON_TV_RGB_MODE
				       |  CON_TV_RGB565_MODE;
				  
     *HW_TV_BUF1 = fb;
     *HW_TV_BUF2 = fb;
     *HW_TV_BUF3 = fb;

     *HW_TV_BUF_SEL = 0;
     
  return;
}

void video_clearscreen(void)
{
	int i = 0;
	for(i=0;i<(640*480);i++)
	{
		fb[i] = 0xFFFF;
	}
}

void video_hexdump(int cx, int cy, unsigned long x, unsigned short colorzz)
{
	unsigned long i;
	unsigned long digit;
	char s[9];
	for(i=0;i<8;i++)
	{
		digit=x>>28;
	    x<<=4;
	    s[i] = digit+'0'+(digit<10?0:'a'-10-'0');
	}
	
	s[8]=0x00;
	video_print(cx, cy, "0x", colorzz);
	cx++;
	cx++;
	video_print(cx, cy, s, colorzz);
}

void video_drawbg(void)
{
	int i = 0;
	for(i=0;i<=640*480;i++)
	{
		fb[i]="\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
	
	}
}