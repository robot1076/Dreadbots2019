/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"
#include "DoubleManipulator.h"

#include "ctre/Phoenix.h"
#include "frc/WPILib.h"

//const int WRIST_ID = 0;
//const int WHEEL_ID = 1;
const int SAFETY_TIMEOUT_SECONDS = 5;
double positions[] = {0, 5.0, 10.0, 15.0};
//TalonSRX wrist = {WRIST_ID};
//TalonSRX intakeWheels = {WHEEL_ID};

DoubleManipulator::DoubleManipulator(WPI_TalonSRX &wrist_in, WPI_TalonSRX &intakeWheels_in) : wrist(wrist_in), intakeWheels(intakeWheels_in) {}

void DoubleManipulator::Init()
{
    wrist.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative);

    wrist.SetSensorPhase(true);
    wrist.ConfigClosedLoopPeakOutput(0, .5);
    currentPosition = 0;
    wrist.SetSelectedSensorPosition(0);

    wrist.SetSafetyEnabled(false);
    // liftMotor.StopMotor();
    wrist.SetExpiration(SAFETY_TIMEOUT_SECONDS);

    //intakeWheels.SetSensorPhase(true);
    //intakeWheels.SetSelectedSensorPosition(0);
    //intakeWheels.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative);
}

void DoubleManipulator::RotateWrist(int position)
{ //0 = lowest, 1 = 45 degrees, 2 = 90 degrees, 3 = a little past 90 for rocket
    //Must raise lift in order to get to 0
    std::cout << "moving to position: " << (positions[position] * TALON_TICKS_PER_ROTATION) << std::endl;
    std::cout << "Motor Position: " << wrist.GetSelectedSensorPosition() << std::endl;
    currentPosition = position;
    wrist.Set(ControlMode::Position, (positions[position] * TALON_TICKS_PER_ROTATION));
}

void DoubleManipulator::SpinWheels(double motorSpeed)
{
    intakeWheels.Set(ControlMode::PercentOutput, motorSpeed);
}

void DoubleManipulator::GrabPanel(Solenoid *sol)
{
    sol->Set(false);
}

void DoubleManipulator::ReleasePanel(Solenoid *sol)
{
    sol->Set(true);
}

void DoubleManipulator::SetBallPickup(bool value)
{
    pickingUp = value;
}

bool DoubleManipulator::CheckBallPickup()
{
    return pickingUp;
}

int DoubleManipulator::GetCurrentPosition(){
    return currentPosition;
}

void DoubleManipulator::SetCurrentPosition(int position){
    currentPosition = position;
}