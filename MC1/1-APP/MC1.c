 /*----------------------------------------------------------------------------
   	[File Name]:    <MC1.c>

  	[Author]:       <AHMED KHALED>

 	[DATA CREATED]: <1/4/2021>

    [Description]:  <the application file for MC1>
 ------------------------------------------------------------------------------*/





/*-----------------------------------------------------------------------------
                               INCLUDES
 ------------------------------------------------------------------------------*/
#include"MC1.h"



/*------------------------------------------------------------------------------
                           GLOBAL Variables
 -------------------------------------------------------------------------------*/
uint8 i,z;
uint8 pass[3],repass[3],option[0];
timer_ConfigType g_config={F_CPU_64,0,255};
UART_ConfigStruct g_struct={0,0,3,Baud_Rate};


/*--------------------------------------------------------------------------------
                        FUNCTION Definitions
---------------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------------------------
 	 [FUNCTION NAME]: enter

 	 [DESCRIPTION]: this function is to request a password from the user for opening the door
                    this function send the password entered by the user to MC2
                    this function when called will wait a MATCHED or UNMATCHED bytes from MC1 according to the password in the EEPROM
 	 	 	 	 	if this MC received MATCHED it will display opening
					if received unmatched this function will request the password again.

	 [Arguments]:   Void
	 [Returns]:     Void
 ----------------------------------------------------------------------------------------------*/

void enter(void)
{
	LCD_clearScreen();                                  //clearing LCD
	LCD_displayStringRowColumn(0, 1, "Enter Password"); //requesting the password through LCD
	_delay_ms(50);
	LCD_goToRowColumn(1, 0);                            //moving the cursor of LCD to the next line

	for(i=0;i<=3;i++)                                    //loop to receive and send the password and to show stars instead of the numbers
	{
		pass[i]=KeyPad_getPressedKey();
		if((pass[i] >= 0) && (pass[i] <= 9))
		{
			_delay_ms(50);
			LCD_displayString("*");
			_delay_ms(50);
			SEND_DATA_UART(pass[i]);
		}

	}

	//now it sent the password entered and waiting to receive MATCHED or UNMATCHED
	if(RECEIVE_DATA_UART()==MATCHED)
	{
		//sending MATCHED to MC1 to move to the next step
		SEND_DATA_UART(MATCHED);
		LCD_clearScreen();
		sei();
		Timer0_init(&g_config);
		Timer0_start(&g_config,15);
		LCD_displayString("opening");
		_delay_ms(100);
		LCD_clearScreen();
		Timer0_setCallBack(close);


	}
	else
	{
		//if not it will send to MC1 to receive another password
		SEND_DATA_UART(UNMATCHED);
		LCD_clearScreen();
		LCD_displayString("Wrong pass");
		enter();

	}

}



/*----------------------------------------------------------------------------------------
  	[FUNCTION NAME]: signin

	[DESCRIPTION]: this function is used when configuring the password, sending it to MC1,
 	 	 	 	 	so it take from the user 2 passwords and sending them to MC1 to check
	[Arguments]:   Void
	[Returns]:     Void
 -----------------------------------------------------------------------------------------*/

 void signin(void)
 {

	 LCD_displayStringRowColumn(0, 1, "Enter Password");
	 _delay_ms(50);
	 LCD_goToRowColumn(1, 0);

	 for(i=0;i<=3;i++)
	 {
		 pass[i]=KeyPad_getPressedKey();
		 if((pass[i] >= 0) && (pass[i] <= 9))
		 {
			 SEND_DATA_UART(pass[i]);
			 _delay_ms(50);
			 LCD_displayString("*");


		 }
	 }

	 _delay_ms(50);
	 LCD_clearScreen();
	 _delay_ms(100);

	 LCD_displayStringRowColumn(0, 1, "ReEnter Password");
	 LCD_goToRowColumn(1, 0);

	 for (z=0;z<=3;)
	 {
		 repass[z]=KeyPad_getPressedKey();
		 _delay_ms(50);
		 if((repass[z] >= 0) && (repass[z] <= 9))
		 {
			 _delay_ms(50);
			 LCD_displayString("*");
			 _delay_ms(50);
			 SEND_DATA_UART(repass[z]);

		 }
		 else{
			 _delay_ms(50);
			 LCD_clearScreen();
			 _delay_ms(50);

		 }
		 z++;

	 }
 }


 /*-------------------------------------------------------------------------------------------------------------
   	[FUNCTION NAME]: Pass_config

 	[DESCRIPTION]: this function is to reconfigure a new password so it take the old password and 2 new passwords by calling another function which is signup
 	 	 	 	   it will send each password (old and 2 new) to MC1 and wait to check and send back a response with MATCHED or UNMATCHED
 	[Arguments]:   Void
 	[Returns]:     Void
  --------------------------------------------------------------------------------------------------------------*/


void pass_config(void)
{
	LCD_displayStringRowColumn(0, 1, "enter old Pass");
	LCD_goToRowColumn(1, 0);

	for (i=0;i<=3;)
	{
		pass[i]=KeyPad_getPressedKey();
		_delay_ms(50);
		if((pass[i] >= 0) && (pass[i] <= 9))
		{
			_delay_ms(50);
			LCD_displayString("*");
			_delay_ms(50);
			SEND_DATA_UART(pass[i]);

		}
		else
		{
			_delay_ms(50);
			LCD_clearScreen();
			_delay_ms(50);
		}
		i++;

	}

	_delay_ms(50);
	LCD_clearScreen();
	_delay_ms(100);
	if(RECEIVE_DATA_UART()==MATCHED)
	{
		SEND_DATA_UART(NEW);
		signin();
		if(RECEIVE_DATA_UART()==MATCHED)
		{
			SEND_DATA_UART(MATCHED);
			LCD_displayString("newpassdone");
//			_delay_ms(100);
		}
		else
		{
			SEND_DATA_UART(UNMATCHED);
			pass_config();
		}
	}
	else
	{
		SEND_DATA_UART(CHANGE);
		pass_config();
	}
}


/*--------------------------------------------------------------------------------------------------------
  	[FUNCTION NAME]: begin

	[DESCRIPTION]: this function is the starting menu the user will choose = or + according to what he want
				   if the  user pressed = it will go to the login function that will make the user enter a password ,sending it to MC1 to check
				   if user pressed + it will go to reconfiguring function that the user will enter old and new passwords.
	[Arguments]:   Void
	[Returns]:     Void
 ----------------------------------------------------------------------------------------------------------*/

void begin(void)
{
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 1, "+ change pass");
	_delay_ms(50);
	LCD_goToRowColumn(1, 0);
	_delay_ms(50);
	LCD_displayStringRowColumn(1, 0, "= log in");
	_delay_ms(50);
	option[0]=KeyPad_getPressedKey();



	if(option[0]=='=')
	{
		LCD_clearScreen();
		_delay_ms(50);
		SEND_DATA_UART(LOGIN);
		enter();
	}
	else if(option[0]=='+')
	{
		LCD_clearScreen();
		_delay_ms(50);
		SEND_DATA_UART(CHANGE);
		pass_config();

	}

}


/*----------------------------------------------------------------------------------------
  	[FUNCTION NAME]: close

	[DESCRIPTION]: stop my timer(clock)

	[Arguments]:   Void

	[Returns]:     Void
 -----------------------------------------------------------------------------------------*/


void close(void)
{
	Timer0_stop(&g_config);
	cli();
}


/*------------------------------------------------------------------------------------------
                      MAIN FUNCTION
 ------------------------------------------------------------------------------------------*/

int main(void)
{

	UART_Init(&g_struct);       //initializing UART


	LCD_init();        //initializing LCD


	signin();  		   //calling signin function to configure the password


	LCD_clearScreen(); //clearing the LCD



	//MC2 should send back after receiving the 2 entered passwords
	// if it received UNMATCHED will show you that not matched and send again to MC2 to be ready to receive another two passwords

	while(RECEIVE_DATA_UART()==UNMATCHED)
	{
		LCD_clearScreen();
		LCD_displayString("NOT MATCHED");
		LCD_clearScreen();
		SEND_DATA_UART(UNMATCHED);
		signin();
	}

	//sending MATCHED to MC1 to be ready to move from configuring the password and be ready to login or to change password commands
	SEND_DATA_UART(MATCHED);

	while(1)
	{
		//while this MC is connected after configuration it will stay at the start function that will be described below
		begin();
	}

}
