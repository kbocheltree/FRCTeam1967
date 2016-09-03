/*
 * jankyScaling.h
 *
 *  Created on: Feb 6, 2016
 *      Author: Gillian
 */

#ifndef INCLUDE_JANKYSCALING_H_
#define INCLUDE_JANKYSCALING_H_
//#define SCALING_WINDS 16					//Scaling winch needs to turn 360 degrees exactly 16 times

//#include "JankyTask.h"
#include "jankyTask.h"
#include "WPILib.h"
#include "jankyEncoder.h"

class jankyScaling{
public:
	//member functions
	jankyScaling(int encoderChannelA, int encoderChannelB, int motorChannelA, int motorChannelB, int pistonChannel);
	~jankyScaling();
	void ScalingStart();
	void Release();
	void LiftUp();
	void DropDn();
	void StopWU();
	void ManualDropDown();
	void ManualLiftUp();
	float GetWrap();

	//member variables
	bool encoderReset;
	bool windCheck;
	Solenoid*piston;
	JankyEncoder*motorEncoder;


};



#endif /* INCLUDE_JANKYSCALING_H_ */
