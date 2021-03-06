#pragma once

#include "frc/WPILib.h"
#include "Lifter.h"
#include "HatchPanelSuction.h"

class AutoHatchPanel
{
  public:
    AutoHatchPanel();
    void alignToTarget();
    void driveToTarget();
    void placePanel(int level);
    void GrabPanel();
  private:
    Lifter lifter{};
    HatchPanelSuction suction{};
};