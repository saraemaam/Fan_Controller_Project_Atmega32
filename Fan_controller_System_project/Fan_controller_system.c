/**************************************************************************************************
 *  Name        : Fan Controller System
 *  Description : Fan Controller system with the specifications listed below:
                  The aim of this project is to design a temperature-controlled
                  fan using ATmega32 microcontroller, in which the fan is automatically
                  turned ON or OFF according to the temperature. Use ATmega32 Microcontroller with frequency 1Mhz
 *  Author      : Sarah
 ***************************************************************************************************/
#include"adc.h"
#include"motor_module.h"
#include"lcd.h"
#include"lm35_sensor.h"
#include<avr/interrupt.h>

int main(void)
{
	uint8 temp = 0;

	/* Initial configuration for DC motor and ADC */
	ADC_ConfigType ADC_configuration = { ADC_INTERNAL_2_56V,ADC_FCPU_8};
	DC_Motor_Config DC_configuration = { CW_DIRECTION };
	DC_Motor_Config *dc_motor_ptr = &DC_configuration;

	/*Initialize LCD*/
	LCD_init();

	/*Initialize ADC module*/
	ADC_init(&ADC_configuration);

	/*Initialize DC Motor*/
	DcMotor_init();

	DcMotor_Rotate(&DC_configuration,50);

	LCD_displayStringRowColumn(1,3,"Temp is =  C");

	while(1)
	{
		temp = LM35_getTemperature();

		if (temp < 30){
			dc_motor_ptr->DC_State = STOP_MOTOR;
			DcMotor_Rotate(&DC_configuration,0);

			LCD_moveCursor(0,3);
			LCD_displayString("FAN IS OFF");

		}
		else if ( temp >=30 &&  temp < 60){
			dc_motor_ptr->DC_State = CW_DIRECTION;
			/*25% => 64*/
			DcMotor_Rotate(&DC_configuration,25);
			LCD_moveCursor(0,3);
			LCD_displayString("FAN IS ON ");

		}
		else if ( temp >=60 && temp < 90 ){
			dc_motor_ptr->DC_State = CW_DIRECTION;
			/* %50 => 128*/
			DcMotor_Rotate(&DC_configuration,50);
			LCD_moveCursor(0,3);
			LCD_displayString("FAN IS ON ");

		}
		else if ( temp >=90 && temp < 120){
			dc_motor_ptr->DC_State = CW_DIRECTION;
			/* %75 => 192 */
			DcMotor_Rotate(&DC_configuration,75);
			LCD_moveCursor(0,3);
			LCD_displayString("FAN IS ON ");
		}
		else if (temp >=120) {
			dc_motor_ptr-> DC_State = CW_DIRECTION;
			/* 100% => 255 */
			DcMotor_Rotate(&DC_configuration,100);
			LCD_moveCursor(0,3);
			LCD_displayString("FAN IS ON ");
		}
		else{

		}
		/* Display the temperature value every time at same position */
		LCD_moveCursor(1,12);
		if(temp >= 100)
		{
			LCD_intgerToString(temp);
		}
		else
		{
			LCD_intgerToString(temp);
			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_displayString(' ');
		}

	}

}
