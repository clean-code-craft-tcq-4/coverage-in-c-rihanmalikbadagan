#pragma once

#define IS_OK 0
#define NOT_OK -1

#define PASSIVE_COOLING_LOW_LIMIT 0
#define PASSIVE_COOLING_HIGH_LIMIT 35

#define HI_ACTIVE_COOLING_LOW_LIMIT 0
#define HI_ACTIVE_COOLING_HIGH_LIMIT 45

#define MED_ACTIVE_COOLING_LOW_LIMIT 0
#define MED_ACTIVE_COOLING_HIGH_LIMIT 40
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

int checkAndAlert(
  AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);
int sendAlert (AlertTarget alertTarget, BreachType breachType);
void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);
