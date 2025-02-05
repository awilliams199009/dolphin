// Copyright 2010 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <string>

#include "InputCommon/ControllerEmu/ControlGroup/ControlGroup.h"
#include "InputCommon/ControllerEmu/ControllerEmu.h"
#include "InputCommon/ControllerEmu/Setting/NumericSetting.h"
#include "InputCommon/ControllerEmu/ControlGroup/PrimeHackModes.h"
#include "InputCommon/ControllerEmu/Control/Control.h"

struct GCPadStatus;

namespace ControllerEmu
{
class AnalogStick;
class Buttons;
class MixedTriggers;
class PrimeHackModes;
}  // namespace ControllerEmu

enum class PadGroup
{
  Buttons,
  MainStick,
  CStick,
  DPad,
  Triggers,
  Rumble,
  Mic,
  Options,

  Beams,
  Visors,
  Camera,
  Misc,
  ControlStick,
  Modes
};

class GCPad : public ControllerEmu::EmulatedController
{
public:
  explicit GCPad(unsigned int index);
  GCPadStatus GetInput() const;
  void SetOutput(const ControlState strength);

  bool GetMicButton() const;

  std::string GetName() const override;

  ControllerEmu::ControlGroup* GetGroup(PadGroup group);

  void LoadDefaults(const ControllerInterface& ciface) override;

  void ChangeUIPrimeHack(bool useMetroidUI);

  bool CheckSpringBallCtrl();
  bool PrimeControllerMode();

  void SetPrimeMode(bool controller);

  bool CheckPitchRecentre();
  std::tuple<double, double> GetPrimeStickXY();

  std::tuple<double, double, bool, bool, bool> GetPrimeSettings();

  // Values averaged from multiple genuine GameCube controllers.
  static constexpr ControlState MAIN_STICK_GATE_RADIUS = 0.7937125;
  static constexpr ControlState C_STICK_GATE_RADIUS = 0.7221375;

private:
	bool using_metroid_ui = false;
  std::vector<std::unique_ptr<ControllerEmu::Control>> trigger_controls_temp;

  ControllerEmu::Buttons* m_buttons;
  ControllerEmu::AnalogStick* m_main_stick;
  ControllerEmu::AnalogStick* m_c_stick;
  ControllerEmu::Buttons* m_dpad;
  ControllerEmu::MixedTriggers* m_triggers;
  ControllerEmu::ControlGroup* m_rumble;
  ControllerEmu::Buttons* m_mic;
  ControllerEmu::ControlGroup* m_options;

  ControllerEmu::SettingValue<bool> m_always_connected_setting;

  ControllerEmu::ControlGroup* m_primehack_camera;
  ControllerEmu::ControlGroup* m_primehack_misc;
  ControllerEmu::AnalogStick* m_primehack_stick;
  ControllerEmu::PrimeHackModes* m_primehack_modes;

  ControllerEmu::SettingValue<double> m_primehack_camera_sensitivity;
  ControllerEmu::SettingValue<double> m_primehack_horizontal_sensitivity;
  ControllerEmu::SettingValue<double> m_primehack_vertical_sensitivity;

  ControllerEmu::SettingValue<bool> m_primehack_invert_y;
  ControllerEmu::SettingValue<bool> m_primehack_invert_x;
  ControllerEmu::SettingValue<bool> m_primehack_remap_map_controls;

  static constexpr u8 STICK_GATE_RADIUS = 0x60;
  static constexpr u8 STICK_CENTER = 0x80;
  static constexpr u8 STICK_RADIUS = 0x7F;

  const unsigned int m_index;
};
