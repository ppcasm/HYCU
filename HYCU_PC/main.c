/*
HYCU - HYperscan Code Uploader by: ppcasm (ppcasm@gmail.com) (PC side)

*/

#include <stdio.h>
#define DLY 200000
void delayz(int time);
void init_serial(char *comz, char *baudz);
unsigned long chksum(unsigned char *chkbuf, unsigned long sizez);
void serial_write(const char *filename, unsigned char bytez);
FILE *fp;

int main(int argc, char *argv[])
{
    if(argc!=5)
    {
         printf("Wrong Usage: <%s> <COM_PORT> <BAUD> <UPLOAD_ADDRESS> <FILE_NAME>\n", argv[0]);
         exit(0);
    }

    FILE *filez = fopen(argv[4], "rb");
    if(filez==NULL)
    {
         printf("File <%s> does not exist?\n", argv[4]);
         exit(0);
    }
    
    unsigned long i = 0;
    unsigned long cur_num = 0;
    unsigned long prev_num = 0;
    char *comz = argv[1];
    char *baudz = argv[2];
    int sizes = strlen(comz)+strlen("\\\\.\\");
    unsigned long upload_address = strtoul(argv[3], NULL, 16);
    unsigned long filesize = 0;
    unsigned long chksum32 = 0;
    char file_buf[sizes];
    
    sprintf(file_buf, "\\\\.\\%s", comz);
    
    init_serial(comz, baudz);
    fp = fopen(file_buf, "wb+");
    
    printf("Upload Address: 0x%x\n", upload_address);
    
    //Set file size
    fseek(filez, 0L, SEEK_END);
    filesize = ftell(filez);
    fseek(filez, 0L, SEEK_SET);
    
    unsigned char savedfile[filesize];
    
    //Read file into buffer.
    fread(savedfile, filesize, 1, filez);
    printf("File Size: 0x%x Bytes\n", filesize);
    
    //Upload upload address
    for(i=0;i<0x4;i++)
    {
      serial_write(file_buf, (upload_address>>(3-i)*8)&0xff);
    }
    
    //Give time to draw
    delayz(DLY);
    
    //Upload file size
    for(i=0;i<0x4;i++)
    {
      serial_write(file_buf, (filesize>>(3-i)*8)&0xff);
    }
    
    //Give time to draw
    delayz(DLY);
    
    //Upload file
    printf("LOADING: %d%%\n", 0);
    
    for(i=0;i<filesize;i++)
    {  
       serial_write(file_buf, savedfile[i]);
       
       cur_num = (((i*100)/filesize));
       if(!(cur_num%10))
       {    
            if(prev_num!=cur_num)
            {
            prev_num = ((i*100)/filesize);
            printf("LOADING: %d%%\n", ((i*100)/filesize));
            }
       }
    }
    
    printf("LOADING: %d%%\n\n", 100);
    
    //Calculate Checksum
    chksum32 = chksum(savedfile, filesize);
    printf("CHKSUM: 0x%08x\n\n", chksum32);
     
    //Send Checksum
    for(i=0;i<0x4;i++)
    {
      serial_write(file_buf, (chksum32>>(3-i)*8)&0xff);
    }
    
    //Give time to draw
    delayz(DLY);
    
    //serial_write(file_buf, 0);
    
    
    printf("DONE\n");
    fclose(filez);
    fclose(fp);

  return;  
}

void init_serial(char *comz, char *baudz)
{
     //_VERY_ lazy way to initialize serial
     int sizes = strlen(comz)+strlen(baudz)+strlen("mode %s: baud=%s parity=N data=8 stop=1 to=off xon=off dtr=off rts=off");
     char mode_buf[sizes];
     printf("\n\nIf you see an illegal device name error here, try another COM port.\n\n");
     sprintf(mode_buf, "mode %s: baud=%s parity=N data=8 stop=1 to=off xon=off dtr=off rts=off", comz, baudz);
     system(mode_buf); 
     
     
  return;
}

void serial_write(const char *filename, unsigned char bytez)
{
    
    fprintf(fp, "%c", bytez);
    delayz(DLY);
    fflush(fp);
}

unsigned long chksum(unsigned char *chkbuf, unsigned long sizez)
{
    int i = 0;
    unsigned long chksum32 = 0;
    for(i=0;i<sizez;i++)
    {
       chksum32+=chkbuf[i];
    }
    
  return chksum32;
}
 
void delayz(int time)
{
     int i = 0;
     for(i=0;i<=time;i++){}
     
  return;
}

