/*
HYCU - HYperscan Code Uploader by ppcasm (ppcasm@gmail.com) (HyperScan Side)

*/

#include "font.h"
#include "image.h"
#include "defz.h"

int main()
{
	unsigned long codesize = 0;
	unsigned long upload_address = 0;
	unsigned long chksum32_pc = 0; //PC calculated checksum
	unsigned long chksum32_hs = 0; //HS calculated checksum
 
	unsigned long i = 0;
	
	unsigned char byte0 = 0;
	unsigned char byte1 = 0;
	unsigned char byte2 = 0;
	unsigned char byte3 = 0;
	
	video_init();
    video_drawbg();

    video_print((640/8)/2-sizeof("(HYCU)")/2, 2, "(HYCU)", 0xffff);
    video_print((640/8)/2-sizeof("HyperScan Code Uploader")/2, 4, "HyperScan Code Uploader", 0xffff);
    video_print((640/8)/2-sizeof("ppcasm@gmail.com")/2, 5, "ppcasm@gmail.com", 0xffff);
    
    video_print((640/8)/2-sizeof("--------INFO--------")/2, (480/16)/2-2, "--------INFO--------", 0xffff);
    video_print((640/8)/2-sizeof("---Upload Address---")/2, (480/16)/2, "---Upload Address---", 0xffff);
    video_print((640/8)/2-sizeof("----Size (bytes)----")/2, (480/16)/2+3, "----Size (bytes)----", 0xffff);
    video_print((640/8)/2-sizeof("-------Status-------")/2, (480/16)/2+6, "-------Status-------", 0xffff);
  
    byte0 = recv_byte();
    byte1 = recv_byte();
    byte2 = recv_byte();
    byte3 = recv_byte();

	upload_address = byte0<<24|byte1<<16|byte2<<8|byte3;
	video_hexdump((640/8)/2-sizeof("0xffffffff")/2, (480/16)/2+1, upload_address, 0xffff);

	void (*entry_point)(void) = (void *)upload_address; 
    unsigned char *pointz = (unsigned char *)upload_address;
	
	byte0 = recv_byte();
    byte1 = recv_byte();
    byte2 = recv_byte();
    byte3 = recv_byte();
    
    codesize = byte0<<24|byte1<<16|byte2<<8|byte3;
    video_hexdump((640/8)/2-sizeof("0xffffffff")/2, (480/16)/2+4, codesize, 0xffff);
    
    for(i=0;i<codesize;i++)
    {
    	pointz[i]=recv_byte();
    }
	
	//Calculate HS checksum
	chksum32_hs = calc_chksum32(pointz, codesize);
	
	//Get PC calculated checksum
	byte0 = recv_byte();
    byte1 = recv_byte();
    byte2 = recv_byte();
    byte3 = recv_byte();
	
	chksum32_pc = byte0<<24|byte1<<16|byte2<<8|byte3;
	
	//Compare
	if(chksum32_pc==chksum32_hs)
	{
		video_print((640/8)/2-sizeof("DONE")/2, (480/16)/2+7, "DONE", 0xffff);
		
		for(;;)
	    {
	    	entry_point();
	    }
	}
	
	else
	{
		video_print((640/8)/2-sizeof("FAILED!")/2, (480/16)/2+7, "FAILED!", 0xffff);
		video_print((640/8)/2-sizeof("!CHKSUM ERROR!")/2, (480/16)/2+8, "!CHKSUM ERROR!", 0xffff);
		video_print((640/8)/2-sizeof("HyperScan Checksum:")/2, (480/16)/2+9, "HyperScan Checksum:", 0xffff);
		video_hexdump((640/8)/2-sizeof("0xffffffff")/2, (480/16)/2+10, chksum32_hs, 0xffff);
		video_print((640/8)/2-sizeof("PC Checksum:")/2, (480/16)/2+11, "PC Checksum:", 0xffff);
		video_hexdump((640/8)/2-sizeof("0xffffffff")/2, (480/16)/2+12, chksum32_pc, 0xffff);
	}
	
	
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
		fb[i] = 0x0000;
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
	unsigned short *imgbuf = (unsigned short *)&image;
	for(i=0;i<=640*480;i++)
	{
		fb[i]=imgbuf[i];
	
	}
}

