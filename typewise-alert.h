#pragma once

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL,
  UNKNOWN_TARGET
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

typedef struct {
  double lowerLimit;
  double upperLimit;
} TemperatureLimits;

TemperatureLimits tempLimitArray[3] = {{0,35}, {0,45}, {0,40}};

void checkAndAlert(
  AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);
int sendAlert (AlertTarget alertTarget, BreachType breachType);
void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);
