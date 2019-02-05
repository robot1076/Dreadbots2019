/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

#include <frc/shuffleboard/Shuffleboard.h> 

#include "Example.h"
#include <frc/Joystick.h>
#include <AHRS.h>
#include "rev/CANSparkMax.h"

#include "ctre/Phoenix.h"
#include "Lifter.h"
#include "frc/WPILib.h"
#include "Drive.h"
#include "Stilts.h"
#include "DoubleManipulator.h"

//----------USB Controllers--------
frc::Joystick *js1 = new frc::Joystick(0);
frc::Joystick *js2 = new frc::Joystick(1); //Driver 2

//js1
int const slowButton = 7;
int const turboButton = 8;
int const joystickX = 0;
int const joystickY = 1;
int const joystickRot = 2;
//js2
int const upButton = 6; 
int const downButton = 8;
int const ballPickup = 1;
int const hatchPickup = 4;
//---------------------------------
bool const DRIVE_ENABLED = false;
bool const LIFTER_ENABLED = false;
bool const MANIPULATOR_ENABLED = true;

//-------------Talons-------------------
WPI_TalonSRX *lFront = new WPI_TalonSRX(4); //left front
WPI_TalonSRX *rFront = new WPI_TalonSRX(1); //right front
WPI_TalonSRX *lBack = new WPI_TalonSRX(2); //left rear
WPI_TalonSRX *rBack = new WPI_TalonSRX(3); //right rear
//----------------------------------------

//Lifter *lifter = new Lifter();

AHRS *gyro;
Drive *drive = new Drive(lFront, lBack, rFront, rBack);


void Robot::RobotInit() 
{
  // Example *example;
  // example = new Example();
  // example->HelloWorld(4);
  gyro = new AHRS(SPI::Port::kMXP);

  gyro->ZeroYaw();
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() 
{

}

void Robot::AutonomousInit() 
{
  gyro->ZeroYaw();
}

void Robot::AutonomousPeriodic() 
{
  currentAngle = gyro->GetYaw();

  if(DRIVE_ENABLED) {
    //drive->DriveStraight(.3, currentAngle);
  }

}

void Robot::TeleopInit()
{
  //lifter->LiftInit();
  manipulator->Init();
  manipulator->SetPickup(false);
  buttonTimer = 0;
}

void Robot::TeleopPeriodic() 
{
  if(LIFTER_ENABLED){
    TeleopLifterControl();
    lifter->CheckHeight(); //needs to be finished. will be used for outputing to smart dashboard
  }
  if(MANIPULATOR_ENABLED){
    TeleopManipulatorControl();
  }
  if(DRIVE_ENABLED) {
    drive->MecDrive(js1->GetRawAxis(joystickX), -(js1->GetRawAxis(joystickY)), js1->GetRawAxis(joystickRot),
      js1->GetRawButton(turboButton), js1->GetRawButton(slowButton));
  }
  buttonTimer++;
}

void Robot::TestPeriodic() 
{

}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
