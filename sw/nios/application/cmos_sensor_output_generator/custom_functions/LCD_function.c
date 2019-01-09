#include "LCD_function.h"
#define LCD_0_BASE LCD_0_0_BASE
void LCD_Write_Command(int Command_Data)
{
	volatile int Check;

	Check = IORD_32DIRECT(LCD_0_BASE,REGSTATECOMMANDDATA);

	if (Check == 0)
	{
		IOWR_32DIRECT(LCD_0_BASE,REGCOMMANDDATA,Command_Data);
		IOWR_32DIRECT(LCD_0_BASE,REGSTATECOMMANDDATA,0x00000001);
	}

}

void LCD_Write_Data(int Command_Data)
{
	volatile int Check;

	Check = IORD_32DIRECT(LCD_0_BASE,REGSTATECOMMANDDATA);

	if (Check == 0)
	{
		IOWR_32DIRECT(LCD_0_BASE,REGCOMMANDDATA,Command_Data);
		IOWR_32DIRECT(LCD_0_BASE,REGSTATECOMMANDDATA,0x00000002);
	}

}

void Fill_Memory(int Start, int End, int Color)
{
	volatile int i;

	for (i = Start; i < End; i += 4)
	{
		volatile int Verif;

		IOWR_32DIRECT(HPS_0_BRIDGES_BASE,i,Color);
		Verif = IORD_32DIRECT(HPS_0_BRIDGES_BASE,i);
		if (Verif != Color)
		{
			printf("Error !\n");
		}
	}

	printf("Memory filled !\n");
}

void Fill_Memory_RGBG(void)
{
	volatile int i;

	volatile int Verif;

		for (i = 0; i < LENGTHBUFFER; i += 4)
		{
			if ( i< LENGTHBUFFER/4)
			{
				IOWR_32DIRECT(HPS_0_BRIDGES_BASE,i,RED);
				Verif = IORD_32DIRECT(HPS_0_BRIDGES_BASE,i);
				if (Verif != RED)
				{
					printf("Error !\n");
				}
			}
			else if ( i> LENGTHBUFFER/4 & i<LENGTHBUFFER/2)
			{
				IOWR_32DIRECT(HPS_0_BRIDGES_BASE,i,GREEN);
				Verif = IORD_32DIRECT(HPS_0_BRIDGES_BASE,i);
				if (Verif != GREEN)
				{
					printf("Error !\n");
				}
			}
			else if ( i> LENGTHBUFFER/2 & i<3*LENGTHBUFFER/4)
			{
				IOWR_32DIRECT(HPS_0_BRIDGES_BASE,i,BLUE);
				Verif = IORD_32DIRECT(HPS_0_BRIDGES_BASE,i);
				if (Verif != BLUE)
				{
					printf("Error !\n");
				}
			}
			else
			{
				IOWR_32DIRECT(HPS_0_BRIDGES_BASE,i,GREEN);
				Verif = IORD_32DIRECT(HPS_0_BRIDGES_BASE,i);
				if (Verif != GREEN)
				{
					printf("Error !\n");
				}
			}

		}

		printf("Memory filled !\n");
}

void Fill_Memory_0_1(void)
{
	volatile int i;
	volatile int j;

	volatile int Verif;

	j = 0;

	for (i = 0; i < LENGTHBUFFER; i += 4)
		{
			if (j == 0)
			{
				IOWR_32DIRECT(HPS_0_BRIDGES_BASE,i,0);
				Verif = IORD_32DIRECT(HPS_0_BRIDGES_BASE,i);
				if (Verif != 0)
				{
					printf("Error !\n");
				}
				j = 1;
			}
			else
			{
				IOWR_32DIRECT(HPS_0_BRIDGES_BASE,i,0xFFFFFFFF);
				Verif = IORD_32DIRECT(HPS_0_BRIDGES_BASE,i);
				if (Verif != 0xFFFFFFFF)
				{
					printf("Error !\n");
				}
				j = 0;
			}
		}

		printf("Memory filled !\n");
}
void LCD_Configuration()
{
	volatile int j;

	for (j = 0; j < 10000; j += 1);

	printf("LCD COnfiguration Start!\n");

	IOWR_32DIRECT(LCD_0_BASE,REGSTARTADD,HPS_0_BRIDGES_BASE);
	alt_printf("RegStartAdd=%x\n", IORD_32DIRECT(LCD_0_BASE,REGSTARTADD));
	IOWR_32DIRECT(LCD_0_BASE,REGLENGTHBUFFER,LENGTHBUFFER);
	alt_printf("RegLengthBuffer=%x\n", IORD_32DIRECT(LCD_0_BASE,REGLENGTHBUFFER));

	IOWR_32DIRECT(LCD_0_BASE,REGCOMMANDDATA,0);
	IOWR_32DIRECT(LCD_0_BASE,REGSTATECOMMANDDATA,0);

	//Fill_Memory(STARTADD,LENGTHBUFFER,RED);
	Fill_Memory_0_1();
	//Fill_Memory_RGBG();

	LCD_Write_Command(0x00000001);
	for (j = 0; j < 10000; j += 1);
	LCD_Write_Command(0x00000000);
	for (j = 0; j < 100000; j += 1);
	LCD_Write_Command(0x00000001);
	for (j = 0; j < 500000; j += 1);

	LCD_Write_Command(0x00000011);

	LCD_Write_Command(0x000000CF);
	LCD_Write_Data(0x00000000);
	LCD_Write_Data(0x00000081);

	LCD_Write_Command(0x000000E8);
	LCD_Write_Data(0x00000085);
	LCD_Write_Data(0x00000001);
	LCD_Write_Data(0x00000798);

	LCD_Write_Command(0x000000CB);
	LCD_Write_Data(0x00000039);
	LCD_Write_Data(0x0000002C);
	LCD_Write_Data(0x00000000);
	LCD_Write_Data(0x00000034);
	LCD_Write_Data(0x00000002);

	LCD_Write_Command(0x000000F7);
	LCD_Write_Data(0x00000020);

	LCD_Write_Command(0x000000EA);
	LCD_Write_Data(0x00000000);
	LCD_Write_Data(0x00000000);

	LCD_Write_Command(0x000000B1);
	LCD_Write_Data(0x00000000);
	LCD_Write_Data(0x0000001B);

	LCD_Write_Command(0x000000B6);
	LCD_Write_Data(0x0000000A);
	LCD_Write_Data(0x000000A2);

	LCD_Write_Command(0x000000C0);
	LCD_Write_Data(0x00000005);

	LCD_Write_Command(0x000000C1);
	LCD_Write_Data(0x00000011);

	LCD_Write_Command(0x000000C5);
	LCD_Write_Data(0x00000045);
	LCD_Write_Data(0x00000045);

	LCD_Write_Command(0x000000C7);
	LCD_Write_Data(0x000000A2);

	LCD_Write_Command(0x00000036);
	LCD_Write_Data(0x0000002C);

	LCD_Write_Command(0x000000F2);
	LCD_Write_Data(0x00000000);

	LCD_Write_Command(0x00000026);
	LCD_Write_Data(0x00000001);

	LCD_Write_Command(0x000000E0);
	LCD_Write_Data(0x0000000F);
	LCD_Write_Data(0x00000026);
	LCD_Write_Data(0x00000024);
	LCD_Write_Data(0x0000000B);
	LCD_Write_Data(0x0000000E);
	LCD_Write_Data(0x00000008);
	LCD_Write_Data(0x0000004B);
	LCD_Write_Data(0x000000A8);
	LCD_Write_Data(0x0000003B);
	LCD_Write_Data(0x0000000A);
	LCD_Write_Data(0x00000014);
	LCD_Write_Data(0x00000006);
	LCD_Write_Data(0x00000010);
	LCD_Write_Data(0x00000009);
	LCD_Write_Data(0x00000000);

	LCD_Write_Command(0x000000E1);
	LCD_Write_Data(0x00000000);
	LCD_Write_Data(0x0000001C);
	LCD_Write_Data(0x00000020);
	LCD_Write_Data(0x00000004);
	LCD_Write_Data(0x00000010);
	LCD_Write_Data(0x00000008);
	LCD_Write_Data(0x00000034);
	LCD_Write_Data(0x00000047);
	LCD_Write_Data(0x00000044);
	LCD_Write_Data(0x00000005);
	LCD_Write_Data(0x0000000B);
	LCD_Write_Data(0x00000009);
	LCD_Write_Data(0x0000002F);
	LCD_Write_Data(0x00000036);
	LCD_Write_Data(0x0000000F);

	LCD_Write_Command(0x0000002A);
	LCD_Write_Data(0x00000000);
	LCD_Write_Data(0x00000000);
	LCD_Write_Data(0x00000001);
	LCD_Write_Data(0x0000003F);

	LCD_Write_Command(0x0000002B);
	LCD_Write_Data(0x00000000);
	LCD_Write_Data(0x00000000);
	LCD_Write_Data(0x00000000);
	LCD_Write_Data(0x000000EF);

	LCD_Write_Command(0x0000003A);
	LCD_Write_Data(0x00000055);

	LCD_Write_Command(0x000000F6);
	LCD_Write_Data(0x00000001);
	LCD_Write_Data(0x00000030);
	LCD_Write_Data(0x00000000);

	LCD_Write_Command(0x00000029);

	LCD_Write_Command(0x0000002C);

	printf("LCD Configuration Over !\n");

}