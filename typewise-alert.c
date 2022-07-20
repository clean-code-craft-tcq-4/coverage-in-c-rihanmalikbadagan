#include "typewise-alert.h"
#include <stdio.h>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value >= upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
 
  return inferBreach(temperatureInC, tempLimitArray[coolingType].lowerLimit, tempLimitArray[coolingType].upperLimit);
}

int checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC);
  
  return sendAlert(alertTarget, breachType);
}

int sendAlert (AlertTarget alertTarget, BreachType breachType)
{
  if (alertTarget == TO_CONTROLLER)
  {
    sendToController(breachType);
    return 0;
  }

  if (alertTarget == TO_EMAIL)
  {
    sendToController(breachType);
    return 0;
  }
  
  printf("[Warning] Unknown alert target\n");
  return -1;
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";

  if (breachType == TOO_LOW)
  {
    printf("To: %s\nHi, the temperature is too low\n",recepient);
    return;
  }

  if (breachType == TOO_HIGH)
  {
    printf("To: %s\nHi, the temperature is too low\n",recepient);
    return;
  }
}
