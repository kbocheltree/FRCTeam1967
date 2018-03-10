/*
 * DriveSegment.cpp
 *
 *  Created on: Feb 8, 2018
 *      Author: AnishaKabir
 */
#include "WPILib.h"
#include "DriveSegment.h"
#include "JankyAutoEntry.h"
#include "ctre/Phoenix.h"
#include "JankyAutoEntry.h"
#include <math.h>

#define MEASURED_DIST_PER_PULSE 0.0912
#define ENCODER_UNITS_PER_ROTATION 4096
#define DIAMETER 6
#define CIRCUMFERENCE_INCHES DIAMETER*M_PI

double lEncoderCount;
double rEncoderCount;
double lEncoderDistance;
double rEncoderDistance;
double testEncoderCount;
double testEncoderDistance;

DriveSegment::DriveSegment(frc::ADXRS450_Gyro*gyro, RobotDrive*drive, SensorCollection*leftEncoder, SensorCollection*rightEncoder, WPI_TalonSRX*leftmotor, WPI_TalonSRX*rightmotor, int inchDistance, double speed, double p, double i, double d) {
//DriveSegment::DriveSegment(RobotDrive*drive, Encoder*testEncoder, int inchDistance, double speed) {
	distance = inchDistance;
	chassis = drive;
	_leftEncoder = leftEncoder;
	_rightEncoder = rightEncoder;
	_leftmotor = leftmotor;
	_rightmotor = rightmotor;
	//_encoder=testEncoder;
	_speed = speed;
	_gyro=gyro;
	kP = p;
	kI = i;
	kD = d;
	pid = new PIDController(kP,kI,kD,_gyro,this);
	// TODO Auto-generated constructor stub

}

DriveSegment::~DriveSegment() {
	// TODO Auto-generated destructor stub
	delete pid;
}

bool DriveSegment::JobDone(){
	lEncoderCount = -_leftEncoder->GetQuadraturePosition();
	rEncoderCount = _rightEncoder->GetQuadraturePosition();
	lEncoderDistance = (lEncoderCount/ENCODER_UNITS_PER_ROTATION)*CIRCUMFERENCE_INCHES;
	rEncoderDistance = (rEncoderCount/ENCODER_UNITS_PER_ROTATION)*CIRCUMFERENCE_INCHES;
	//remove in final code:
	//printf("Left Encoder dist %f \n", lEncoderDistance);
	//printf("Right Encoder dist %f \n", rEncoderDistance);
	if((lEncoderDistance>=distance)||(rEncoderDistance>=distance)){
		printf("job done \n");
		return true;
	}
	/*testEncoderCount=-_encoder->Get();
	testEncoderDistance=(testEncoderCount*MEASURED_DIST_PER_PULSE);
	SmartDashboard::PutNumber("Encoder Count", testEncoderCount);
	//printf("Test Encoder Count %f \n", testEncoderCount);
	SmartDashboard::PutNumber("Encoder Distance", testEncoderDistance);
	if(testEncoderDistance>=distance){
		printf("job done \n");
		return true;
	}*/
	return false;
}

void DriveSegment::RunAction(){
	//chassis->TankDrive(_speed, _speed);
}

void DriveSegment::Start(){
	_leftEncoder->SetQuadraturePosition(0, 10);
	_rightEncoder->SetQuadraturePosition(0, 10);
	_leftmotor->SetSelectedSensorPosition(0, 0, 10);
	_rightmotor->SetSelectedSensorPosition(0, 0, 10);
	_gyro->Reset();
	pid->SetInputRange(-180.0, 180.0);
	pid->SetOutputRange(-1.0, 1.0);
	pid->SetSetpoint(0.0);
	pid->Enable();
	//_encoder->Reset();
}

void DriveSegment::End(){
	pid->Disable();
	chassis->TankDrive(0.0, 0.0);
}

void DriveSegment::PIDWrite(double output)
{
	chassis->Drive(_speed, output);
	//chassis->CurvatureDrive(_speed, output, true); //IF CHANGING TO ARCADE DRIVE REMEMBER THAT NEGATIVE NUMBERS MEAN FORWARD
}
