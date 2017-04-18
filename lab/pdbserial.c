#include<bios.h>
#include<conio.h>
#include<stdio.h>
#define COM1 0//one less than the actual number
#define DR 0x100//setting data ready

#define s ( 0xE3 | 0x00 | 0x00 | 0x00 )//baud rate of 9600,7 data bits,no parity,1 stop bit
int main(void)
{
	int in,out,status=0,a;
	bioscom(0,s,COM1);//initalize port with the above settings
	clrscr();
	cprintf("data sent");
	while(1)
	{
		//receive part
		status=bioscom(3,0,COM1);//read the status of com port

		if(status & DR )//wait until data has arrived


		     {if(((out=bioscom(2,0,COM1)) & 0x7F) !=0)//receive from com port and ensure it is non-zero
			   printf("%c",out);//display on screen

		    }
		//send part
		if(kbhit())//key pressed on keyboard
		{

			if((in=getch())==27)//ascii value of esc is 27,to break out of the loop
				{

				break;

				}
		putch(in);//echo on screen
		bioscom(1,in,COM1);//send data in to com port

		}

     }
     return 0;
}
