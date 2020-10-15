// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. 

#ifndef UTILITY_H
#define UTILITY_H

void parseTwinMessage(DEVICE_TWIN_UPDATE_STATE, const char *);
void readMessage(int, char *, float *, float *, float *, int *, int *, int *, int *, int *, int *, int *, int *, int *);

void SensorInit(void);

void blinkLED(void);
void blinkSendConfirmation(void);
int getInterval(void);

#endif /* UTILITY_H */