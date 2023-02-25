#include <JoystickLibraryAdapter.h>
//
//        DOES NOT WORK
//
// JoystickLibraryAdapter::JoystickLibraryAdapter(JoystickInterface *j)
// {
//     joystick = j;
//     // axis numbers set to my preference
//     joystickXYZsetters.at(2) = {&JoystickInterface::setXAxis};
//     joystickXYZsetters.at(1) = {&JoystickInterface::setYAxis};
//     joystickXYZsetters.at(0) = {&JoystickInterface::setZAxis};
//     joystickRXRYRZsetters.at(0) = {&JoystickInterface::setRxAxis};
//     joystickRXRYRZsetters.at(2) = {&JoystickInterface::setRyAxis};
//     joystickRXRYRZsetters.at(2) = {&JoystickInterface::setRyAxis};
// }

// void JoystickLibraryAdapter::setXYZ(int index, long value)
// {
//     (joystick->*joystickXYZsetters.at(index))(value);
// }

// void JoystickLibraryAdapter::setRXRYRZ(int index, long value)
// {
//     (joystick->*joystickRXRYRZsetters.at(index))(value);
// }

// void JoystickLibraryAdapter::send()
// {
//     joystick->sendState();
// }
// void JoystickLibraryAdapter::begin()
// {
//     joystick->begin();
// }

// void JoystickLibraryAdapter::setXAxisRange(int MIN_X, int MAX_X)
// {
//     joystick->setXAxisRange(MIN_X, MAX_X);
// }
// void JoystickLibraryAdapter::setYAxisRange(int MIN_Y, int MAX_Y)
// {
//     joystick->setZAxisRange(MIN_Y, MAX_Y);
// }
// void JoystickLibraryAdapter::setZAxisRange(int MIN_Z, int MAX_Z)
// {
//     joystick->setYAxisRange(MIN_Z, MAX_Z);
// }

// void JoystickLibraryAdapter::setRxAxisRange(int MIN_X, int MAX_X)
// {
//     joystick->setRxAxisRange(MIN_X, MAX_X);
// }
// void JoystickLibraryAdapter::setRyAxisRange(int MIN_Y, int MAX_Y)
// {
//     joystick->setRzAxisRange(MIN_Y, MAX_Y);
// }
// void JoystickLibraryAdapter::setRzAxisRange(int MIN_Z, int MAX_Z)
// {
//     joystick->setRyAxisRange(MIN_Z, MAX_Z);
// }
// JoystickLibraryAdapter::~JoystickLibraryAdapter(){

// }