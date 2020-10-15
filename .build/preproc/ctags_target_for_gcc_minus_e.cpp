# 1 "c:\\Users\\Administrator\\Documents\\IoTWorkbenchProjects\\examples\\MilwaukeeTool_10012020\\Device\\PnPGetStarted.ino"
// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. 
// To get started please visit https://microsoft.github.io/azure-iot-developer-kit/docs/projects/connect-iot-hub?utm_source=ArduinoExtension&utm_medium=ReleaseNote&utm_campaign=VSCode
# 5 "c:\\Users\\Administrator\\Documents\\IoTWorkbenchProjects\\examples\\MilwaukeeTool_10012020\\Device\\PnPGetStarted.ino" 2
# 6 "c:\\Users\\Administrator\\Documents\\IoTWorkbenchProjects\\examples\\MilwaukeeTool_10012020\\Device\\PnPGetStarted.ino" 2
# 7 "c:\\Users\\Administrator\\Documents\\IoTWorkbenchProjects\\examples\\MilwaukeeTool_10012020\\Device\\PnPGetStarted.ino" 2

# 9 "c:\\Users\\Administrator\\Documents\\IoTWorkbenchProjects\\examples\\MilwaukeeTool_10012020\\Device\\PnPGetStarted.ino" 2
# 10 "c:\\Users\\Administrator\\Documents\\IoTWorkbenchProjects\\examples\\MilwaukeeTool_10012020\\Device\\PnPGetStarted.ino" 2
# 11 "c:\\Users\\Administrator\\Documents\\IoTWorkbenchProjects\\examples\\MilwaukeeTool_10012020\\Device\\PnPGetStarted.ino" 2

static bool hasWifi = false;
int messageCount = 1;
int sentMessageCount = 0;
static bool messageSending = true;
static uint64_t send_interval_ms;
static const char model_id[] = "dtmi:com:JC_IOT:MXChip:AllSensors;1";
static const char sampleProperties[] = "{\"sample\": \"MXChip_AllSensors\" }";
static const char responseMessageFormat[] = "{\"message\": \"%s\" }";
static const char* successResponse = "Successfully invoke device method";
static const char* failResponse = "No method found";

static float temperature, humidity, pressure;
static int magnetometer_x, magnetometer_y, magnetometer_z;
static int accelerometer_x, accelerometer_y, accelerometer_z;
static int gyroscope_x, gyroscope_y, gyroscope_z;

// Utilities
static void InitWifi()
{
  Screen.print(2, "Connecting...");

  if (WiFi.begin() == WL_CONNECTED)
  {
    IPAddress ip = WiFi.localIP();
    Screen.print(1, ip.get_address());
    hasWifi = true;
    Screen.print(2, "Running... \r\n");
  }
  else
  {
    hasWifi = false;
    Screen.print(1, "No Wi-Fi\r\n ");
  }
}

static void BuildCommandResponse(unsigned char** response, int* response_size, const char* message)
{
  int responseBuilderSize = 0;
  unsigned char* responseBuilder = 
# 50 "c:\\Users\\Administrator\\Documents\\IoTWorkbenchProjects\\examples\\MilwaukeeTool_10012020\\Device\\PnPGetStarted.ino" 3 4
                                  __null
# 50 "c:\\Users\\Administrator\\Documents\\IoTWorkbenchProjects\\examples\\MilwaukeeTool_10012020\\Device\\PnPGetStarted.ino"
                                      ;
  int result = 200;

  if ((responseBuilderSize = snprintf(
# 53 "c:\\Users\\Administrator\\Documents\\IoTWorkbenchProjects\\examples\\MilwaukeeTool_10012020\\Device\\PnPGetStarted.ino" 3 4
                                     __null
# 53 "c:\\Users\\Administrator\\Documents\\IoTWorkbenchProjects\\examples\\MilwaukeeTool_10012020\\Device\\PnPGetStarted.ino"
                                         , 0, responseMessageFormat, message)) < 0)
  {
    do{ { (void)(0 && printf("snprintf to determine string length for command response failed")); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 55 "c:\\Users\\Administrator\\Documents\\IoTWorkbenchProjects\\examples\\MilwaukeeTool_10012020\\Device\\PnPGetStarted.ino" 3 4
   __null
# 55 "c:\\Users\\Administrator\\Documents\\IoTWorkbenchProjects\\examples\\MilwaukeeTool_10012020\\Device\\PnPGetStarted.ino"
   ) l(AZ_LOG_ERROR, "c:\\Users\\Administrator\\Documents\\IoTWorkbenchProjects\\examples\\MilwaukeeTool_10012020\\Device\\PnPGetStarted.ino", __func__, 55, 0x01, "snprintf to determine string length for command response failed"); } }; }while((void)0,0);
  }
  else if ((responseBuilder = (unsigned char*)calloc(1, responseBuilderSize + 1)) == 
# 57 "c:\\Users\\Administrator\\Documents\\IoTWorkbenchProjects\\examples\\MilwaukeeTool_10012020\\Device\\PnPGetStarted.ino" 3 4
                                                                                    __null
# 57 "c:\\Users\\Administrator\\Documents\\IoTWorkbenchProjects\\examples\\MilwaukeeTool_10012020\\Device\\PnPGetStarted.ino"
                                                                                        )
  {
    do{ { (void)(0 && printf("Unable to allocate %lu bytes", (unsigned long)(responseBuilderSize + 1))); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 59 "c:\\Users\\Administrator\\Documents\\IoTWorkbenchProjects\\examples\\MilwaukeeTool_10012020\\Device\\PnPGetStarted.ino" 3 4
   __null
# 59 "c:\\Users\\Administrator\\Documents\\IoTWorkbenchProjects\\examples\\MilwaukeeTool_10012020\\Device\\PnPGetStarted.ino"
   ) l(AZ_LOG_ERROR, "c:\\Users\\Administrator\\Documents\\IoTWorkbenchProjects\\examples\\MilwaukeeTool_10012020\\Device\\PnPGetStarted.ino", __func__, 59, 0x01, "Unable to allocate %lu bytes", (unsigned long)(responseBuilderSize + 1)); } }; }while((void)0,0);
  }
  else if ((responseBuilderSize = snprintf((char*)responseBuilder, responseBuilderSize + 1, responseMessageFormat, message)) < 0)
  {
    do{ { (void)(0 && printf("snprintf to output buffer for command response")); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 63 "c:\\Users\\Administrator\\Documents\\IoTWorkbenchProjects\\examples\\MilwaukeeTool_10012020\\Device\\PnPGetStarted.ino" 3 4
   __null
# 63 "c:\\Users\\Administrator\\Documents\\IoTWorkbenchProjects\\examples\\MilwaukeeTool_10012020\\Device\\PnPGetStarted.ino"
   ) l(AZ_LOG_ERROR, "c:\\Users\\Administrator\\Documents\\IoTWorkbenchProjects\\examples\\MilwaukeeTool_10012020\\Device\\PnPGetStarted.ino", __func__, 63, 0x01, "snprintf to output buffer for command response"); } }; }while((void)0,0);
  }

  *response = responseBuilder;
  *response_size = responseBuilderSize;
  do{{ (void)(0 && printf("Response=<%s>", (const char*)responseBuilder)); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 68 "c:\\Users\\Administrator\\Documents\\IoTWorkbenchProjects\\examples\\MilwaukeeTool_10012020\\Device\\PnPGetStarted.ino" 3 4
 __null
# 68 "c:\\Users\\Administrator\\Documents\\IoTWorkbenchProjects\\examples\\MilwaukeeTool_10012020\\Device\\PnPGetStarted.ino"
 ) l(AZ_LOG_INFO, "c:\\Users\\Administrator\\Documents\\IoTWorkbenchProjects\\examples\\MilwaukeeTool_10012020\\Device\\PnPGetStarted.ino", __func__, 68, 0x01, "Response=<%s>", (const char*)responseBuilder); } }; }while((void)0,0);
}

static void SendConfirmationCallback(IOTHUB_CLIENT_CONFIRMATION_RESULT result)
{
  if (result == IOTHUB_CLIENT_CONFIRMATION_OK)
  {
    blinkSendConfirmation();
    sentMessageCount++;
  }

  Screen.print(1, "> IoT Hub");
  char line1[20];
  sprintf(line1, "Count: %d/%d",sentMessageCount, messageCount);
  Screen.print(2, line1);

  char line2[20];
  sprintf(line2, "T:%.2f H:%.2f", temperature, humidity);
  Screen.print(3, line2);
  messageCount++;
}

static void MessageCallback(const char* payLoad, int size)
{
  blinkLED();
  Screen.print(1, payLoad, true);
}

static void DeviceTwinCallback(DEVICE_TWIN_UPDATE_STATE updateState, const unsigned char *payLoad, int size)
{
  char *temp = (char *)malloc(size + 1);
  if (temp == 
# 99 "c:\\Users\\Administrator\\Documents\\IoTWorkbenchProjects\\examples\\MilwaukeeTool_10012020\\Device\\PnPGetStarted.ino" 3 4
             __null
# 99 "c:\\Users\\Administrator\\Documents\\IoTWorkbenchProjects\\examples\\MilwaukeeTool_10012020\\Device\\PnPGetStarted.ino"
                 )
  {
    return;
  }
  memcpy(temp, payLoad, size);
  temp[size] = '\0';
  parseTwinMessage(updateState, temp);
  free(temp);
}

static int DeviceMethodCallback(const char *methodName, const unsigned char *payload, int size, unsigned char **response, int *response_size)
{
  do{{ (void)(0 && printf("Try to invoke method %s", methodName)); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 111 "c:\\Users\\Administrator\\Documents\\IoTWorkbenchProjects\\examples\\MilwaukeeTool_10012020\\Device\\PnPGetStarted.ino" 3 4
 __null
# 111 "c:\\Users\\Administrator\\Documents\\IoTWorkbenchProjects\\examples\\MilwaukeeTool_10012020\\Device\\PnPGetStarted.ino"
 ) l(AZ_LOG_INFO, "c:\\Users\\Administrator\\Documents\\IoTWorkbenchProjects\\examples\\MilwaukeeTool_10012020\\Device\\PnPGetStarted.ino", __func__, 111, 0x01, "Try to invoke method %s", methodName); } }; }while((void)0,0);
  int result = 200;

  if (strcmp(methodName, "start") == 0)
  {
    do{{ (void)(0 && printf("Start sending temperature, humidity and pressure data")); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 116 "c:\\Users\\Administrator\\Documents\\IoTWorkbenchProjects\\examples\\MilwaukeeTool_10012020\\Device\\PnPGetStarted.ino" 3 4
   __null
# 116 "c:\\Users\\Administrator\\Documents\\IoTWorkbenchProjects\\examples\\MilwaukeeTool_10012020\\Device\\PnPGetStarted.ino"
   ) l(AZ_LOG_INFO, "c:\\Users\\Administrator\\Documents\\IoTWorkbenchProjects\\examples\\MilwaukeeTool_10012020\\Device\\PnPGetStarted.ino", __func__, 116, 0x01, "Start sending temperature, humidity and pressure data"); } }; }while((void)0,0);
    messageSending = true;
  }
  else if (strcmp(methodName, "stop") == 0)
  {
    do{{ (void)(0 && printf("Stop sending temperature, humidity and pressure data")); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 121 "c:\\Users\\Administrator\\Documents\\IoTWorkbenchProjects\\examples\\MilwaukeeTool_10012020\\Device\\PnPGetStarted.ino" 3 4
   __null
# 121 "c:\\Users\\Administrator\\Documents\\IoTWorkbenchProjects\\examples\\MilwaukeeTool_10012020\\Device\\PnPGetStarted.ino"
   ) l(AZ_LOG_INFO, "c:\\Users\\Administrator\\Documents\\IoTWorkbenchProjects\\examples\\MilwaukeeTool_10012020\\Device\\PnPGetStarted.ino", __func__, 121, 0x01, "Stop sending temperature, humidity and pressure data"); } }; }while((void)0,0);
    messageSending = false;
  }
  else
  {
    do{{ (void)(0 && printf("No method %s found", methodName)); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 126 "c:\\Users\\Administrator\\Documents\\IoTWorkbenchProjects\\examples\\MilwaukeeTool_10012020\\Device\\PnPGetStarted.ino" 3 4
   __null
# 126 "c:\\Users\\Administrator\\Documents\\IoTWorkbenchProjects\\examples\\MilwaukeeTool_10012020\\Device\\PnPGetStarted.ino"
   ) l(AZ_LOG_INFO, "c:\\Users\\Administrator\\Documents\\IoTWorkbenchProjects\\examples\\MilwaukeeTool_10012020\\Device\\PnPGetStarted.ino", __func__, 126, 0x01, "No method %s found", methodName); } }; }while((void)0,0);
    BuildCommandResponse(response, response_size, failResponse);
    result = 404;
  }
  BuildCommandResponse(response, response_size, successResponse);
  return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Arduino sketch
void setup()
{
  Screen.init();
  Screen.print(0, "IoT DevKit");
  Screen.print(2, "Initializing...");

  Screen.print(3, " > Serial");
  Serial.begin(115200);

  // Initialize the WiFi module
  Screen.print(3, " > WiFi");
  hasWifi = false;
  InitWifi();
  if (!hasWifi)
  {
    return;
  }

  LogTrace("HappyPathSetup", 
# 154 "c:\\Users\\Administrator\\Documents\\IoTWorkbenchProjects\\examples\\MilwaukeeTool_10012020\\Device\\PnPGetStarted.ino" 3 4
                            __null
# 154 "c:\\Users\\Administrator\\Documents\\IoTWorkbenchProjects\\examples\\MilwaukeeTool_10012020\\Device\\PnPGetStarted.ino"
                                );

  Screen.print(3, " > Sensors");
  SensorInit();

  Screen.print(3, " > IoT Hub");
  DevKitMQTTClient_SetOption("MiniSolution", "DevKit-PnP-GetStarted");
  DevKitMQTTClient_Init(true, false, model_id);
  DevKitMQTTClient_SetSendConfirmationCallback(SendConfirmationCallback);
  DevKitMQTTClient_SetMessageCallback(MessageCallback);
  DevKitMQTTClient_SetDeviceTwinCallback(DeviceTwinCallback);
  DevKitMQTTClient_SetDeviceMethodCallback(DeviceMethodCallback);

  EVENT_INSTANCE* message = DevKitMQTTClient_Event_Generate(sampleProperties, STATE);
  DevKitMQTTClient_SendEventInstance(message);

  send_interval_ms = SystemTickCounterRead();
}

void loop()
{
  if (hasWifi)
  {
    if (messageSending &&
        (int)(SystemTickCounterRead() - send_interval_ms) >= getInterval())
    {
      // Send teperature data
      char messagePayload[1024];

      readMessage(messageCount, messagePayload, &temperature, &humidity, &pressure, &magnetometer_x, &magnetometer_y, &magnetometer_z, &accelerometer_x, &accelerometer_y, &accelerometer_z, &gyroscope_x, &gyroscope_y, &gyroscope_z);

      EVENT_INSTANCE* message = DevKitMQTTClient_Event_Generate(messagePayload, MESSAGE);
      DevKitMQTTClient_SendEventInstance(message);

      send_interval_ms = SystemTickCounterRead();
    }
    else
    {
      DevKitMQTTClient_Check();
    }
  }
  delay(1000);
}
