#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(22, 0, 45) == NORMAL);
  REQUIRE(inferBreach(35, 0, 35) == TOO_HIGH);
  REQUIRE(inferBreach(10, 10, 40) == NORMAL);
}

TEST_CASE("Classify temperature breach") {
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 22) == NORMAL);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, -5) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 55) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 40) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, -10) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 38) == NORMAL);
}

TEST_CASE("Check and Alert") {
  BatteryCharacter batteryCharacter;
  batteryCharacter.coolingType = PASSIVE_COOLING;
  REQUIRE(checkAndAlert(TO_CONTROLLER, batteryCharacter, 22) == IS_OK);
  REQUIRE(checkAndAlert(TO_EMAIL, batteryCharacter, 40) == IS_OK);
  batteryCharacter.coolingType = HI_ACTIVE_COOLING;  
  REQUIRE(checkAndAlert(TO_CONTROLLER, batteryCharacter, -5) == IS_OK);
  REQUIRE(checkAndAlert(TO_CONTROLLER, batteryCharacter, 55) == IS_OK);
  batteryCharacter.coolingType = MED_ACTIVE_COOLING;
  REQUIRE(checkAndAlert(UNKNOWN_TARGET, batteryCharacter, -10) == NOT_OK);
  REQUIRE(checkAndAlert(TO_EMAIL, batteryCharacter, 38) == IS_OK);
}

TEST_CASE("Send alert") {
  REQUIRE(sendAlert(TO_CONTROLLER, NORMAL) == IS_OK);
  REQUIRE(sendAlert(TO_CONTROLLER, TOO_HIGH) == IS_OK);
  REQUIRE(sendAlert(TO_CONTROLLER, TOO_LOW) == IS_OK);
  REQUIRE(sendAlert(TO_EMAIL, NORMAL) == IS_OK);
  REQUIRE(sendAlert(UNKNOWN_TARGET, TOO_HIGH) == NOT_OK);
  REQUIRE(sendAlert(TO_EMAIL, TOO_LOW) == IS_OK);
}