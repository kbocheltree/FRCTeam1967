#include "WPILib.h"
#include "jankyRobot.h"
#include "jankyRobotTemplate.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 

class SensorTestjig : public JankyRobotTemplate
{
	Joystick stick; // only joystick
	DigitalInput sensor;
	
public:
	SensorTestjig(void):
		stick(1),		// as they are declared above.
		sensor(14)
		
	{
	
	}

	void Autonomous(void)
	{
		AutonomousInit();
		
	}

	void OperatorControl(void)
	{
		OperatorControlInit();
		
		while (IsOperatorControl())
		{
			ProgramIsAlive();
			//No need to do waits because ProgramIsAlive function does a wait. //Wait(0.005);
			
			float leftYaxis = stick.GetY();
			float rightYaxis = stick.GetRawAxis(5);	//RawAxis(5);
			TankDrive(leftYaxis,rightYaxis); 	// drive with arcade style (use right stick)for joystick 1
			SmartDashboard::PutNumber("Left Axis",leftYaxis);
			SmartDashboard::PutNumber("Right Axis",rightYaxis);	
			
			bool buttonPressed = stick.GetRawButton(3);
			if (buttonPressed)
			{
				bool sensorValue = sensor.Get();
				SmartDashboard::PutNumber("Sensor Value",sensorValue);
			}
			SmartDashboard::PutNumber("Is Sensor Button Pressed",buttonPressed);
			
		}
	}
};

START_ROBOT_CLASS(SensorTestjig);

