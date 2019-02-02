/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include "frc/WPILib.h"
#include "Lifter.h"
#include <iostream>
#include "Drive.h"
#include "DoubleManipulator.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/shuffleboard/Shuffleboard.h> //not needed once Abbie's stuff is changed

double const TALON_TICKS_PER_ROTATION = 4096;

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;
  void TeleopLifterControl();
  void TeleopManipulatorControl();
  //void ElectricSolenoidTest(Solenoid *solenoid);

//----------USB Controllers--------
frc::Joystick *js1 = new frc::Joystick(0);
frc::Joystick *js2 = new frc::Joystick(1); //Driver 2

bool isADown = false;

//js1
int const turboButton = 8;
int const joystickX = 0;
int const joystickY = 1;
int const joystickRot = 2;
int const solButton = 2;
//js2
int const upButton = 6; 
int const downButton = 8; 
int const ballPickup = 1;
int const manualOverrideButton = 3;
//---------------------------------

//-----------Solenoid--------------
//Compressor *compressor = new Compressor(0);
//Solenoid *solenoid = new Solenoid(4);
bool isSolOut = false;

//-------------Talons-------------------
WPI_TalonSRX *lFront = new WPI_TalonSRX(0); //left front
WPI_TalonSRX *rFront = new WPI_TalonSRX(1); //right front
WPI_TalonSRX *lBack = new WPI_TalonSRX(2); //left rear
WPI_TalonSRX *rBack = new WPI_TalonSRX(3); //right rear
//----------------------------------------

int buttonTimer = 0;
int const BUTTON_TIMEOUT = BUTTON_TIMEOUT;

//------------Auton Variables-------
double currentAngle;

Lifter *lifter = new Lifter();
Drive *drive = new Drive(lFront, lBack, rFront, rBack);
DoubleManipulator *manipulator = new DoubleManipulator();



 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;
};
