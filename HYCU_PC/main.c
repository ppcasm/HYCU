/*
HYCU - HYperscan Code Uploader by: ppcasm (ppcasm@gmail.com) (PC side)
*/

#include <stdio.h>

void init_serial(char *comz, char *baudz);
void serial_write(const char *filename, unsigned char bytez);
FILE *fp;

int main(int argc, char *argv[])
{
    if(argc!=5)
    {
         printf("Wrong Usage: <%s> <COM_PORT> <BAUD> <UPLOAD_ADDRESS> <FILE_NAME>\n", argv[0]);
         exit(0);
    }

    FILE *filez = fopen(argv[4], "r");
    if(filez==NULL)
    {
         printf("File <%s> does not exist?\n", argv[4]);
         exit(0);
    }
    
    unsigned char i = 0;
    char *comz = argv[1];
    char *baudz = argv[2];
    int sizes = strlen(comz)+strlen("\\\\.\\");
    unsigned long upload_address = strtoul(argv[3], NULL, 16);
    unsigned long filesize = 0;
    char file_buf[sizes];
    sprintf(file_buf, "\\\\.\\%s", comz);
    
    init_serial(comz, baudz);
    
    printf("Upload Address: 0x%x\n", upload_address);
    
    //Set file size
    fseek(filez, 0L, SEEK_END);
    filesize = ftell(filez);
    fseek(filez, 0L, SEEK_SET);
    
    unsigned char savedfile[filesize];
    
    fread(savedfile, filesize, 1, filez);
    printf("File Size: 0x%x Bytes\n", filesize);
       
    
    //Upload upload address
    for(i=0;i<0x4;i++)
    {
       serial_write(file_buf, (upload_address>>(3-i)*8)&0xff);
    }
    
    //Upload file size
    for(i=0;i<0x4;i++)
    {
       serial_write(file_buf, (filesize>>(3-i)*8)&0xff);
    }
    
    //Write file into buffer.
    //Upload file
    for(i=0;i<filesize;i++)
    {                    
       serial_write(file_buf, savedfile[i]);
    }
    
    fclose(filez);
    
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
    fp = fopen(filename, "wb+");
    fprintf(fp, "%c", bytez);
    fclose(fp);
    
}


