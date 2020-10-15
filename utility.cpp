// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. 

#include "Sensor.h"
#include "AzureIotHub.h"
#include "Arduino.h"
#include "parson.h"
#include "config.h"
#include "RGB_LED.h"

#define RGB_LED_BRIGHTNESS 32

DevI2C *i2c;
HTS221Sensor *sensor;
LPS22HBSensor *pressureSensor;
LSM6DSLSensor *acc_gyroSensor;
LIS2MDLSensor *magnetometerSensor;
IRDASensor * irSensor;
static RGB_LED rgbLed;
static int interval = INTERVAL;
static float humidity, temperature, pressure;
static int magnetometer_x, magnetometer_y, magnetometer_z;
static int accelerometer_x, accelerometer_y, accelerometer_z;
static int gyroscope_x, gyroscope_y, gyroscope_z;


int getInterval()
{
    return interval;
}

void blinkLED()
{
    rgbLed.turnOff();
    rgbLed.setColor(RGB_LED_BRIGHTNESS, 0, 0);
    delay(500);
    rgbLed.turnOff();
}

void blinkSendConfirmation()
{
    rgbLed.turnOff();
    rgbLed.setColor(0, 0, RGB_LED_BRIGHTNESS);
    delay(500);
    rgbLed.turnOff();
}

void parseTwinMessage(DEVICE_TWIN_UPDATE_STATE updateState, const char *message)
{
    JSON_Value *root_value;
    root_value = json_parse_string(message);
    if (json_value_get_type(root_value) != JSONObject)
    {
        if (root_value != NULL)
        {
            json_value_free(root_value);
        }
        LogError("parse %s failed", message);
        return;
    }
    JSON_Object *root_object = json_value_get_object(root_value);

    double val = 0;
    if (updateState == DEVICE_TWIN_UPDATE_COMPLETE)
    {
        JSON_Object *desired_object = json_object_get_object(root_object, "desired");
        if (desired_object != NULL)
        {
            val = json_object_get_number(desired_object, "interval");
        }
    }
    else
    {
        val = json_object_get_number(root_object, "interval");
    }
    if (val > 500)
    {
        interval = (int)val;
        LogInfo(">>>Device twin updated: set interval to %d", interval);
    }
    json_value_free(root_value);
}

void SensorInit()
{
    i2c = new DevI2C(D14, D15);
    sensor = new HTS221Sensor(*i2c);
    sensor->init(NULL);
    sensor->reset();
    

    pressureSensor = new LPS22HBSensor(*i2c);
    pressureSensor->init(NULL);

    acc_gyroSensor = new LSM6DSLSensor(*i2c,D4,D5);
    acc_gyroSensor->init(NULL);
    acc_gyroSensor->enableAccelerator();
    acc_gyroSensor->enableGyroscope();

    magnetometerSensor = new LIS2MDLSensor(*i2c);
    magnetometerSensor->init(NULL);

    humidity = -1;
    //temperature = -1000;
    pressure = -1;
}

void getTemperatureValue(float *t)
{
    float temp;
    sensor->getTemperature(&temp);
    *t = temp;
}

void getHumidityValue(float *h)
{
    float hum;
    sensor->getHumidity(&hum);
    *h = hum;
}

void getPressureValue(float *p)
{
    float press;
    pressureSensor->getPressure(&press);
    *p = press;
}

void getMagnetometerValue(int *x, int *y, int *z)
{
    int axes[3];
    magnetometerSensor->getMAxes(axes);
    *x = axes[0];
    *y = axes[1];
    *z = axes[2];
}
void getGyroscopeXYZ(int *x, int *y, int *z)
{
    int axes[3];
    acc_gyroSensor->getGAxes(axes);
    *x = axes[0];
    *y = axes[1];
    *z = axes[2];
}

void getAcceleratorXYZ(int *x, int *y, int *z)
{
    int axes[3];
    acc_gyroSensor->getXAxes(axes);
    *x = axes[0];
    *y = axes[1];
    *z = axes[2];
}

float readTemperature()
{
    getTemperatureValue(&temperature);
    return temperature;
}

float readHumidity()
{
    getHumidityValue(&humidity);
    return humidity;
}

float readPressure()
{
    getPressureValue(&pressure);
    return pressure;
}

int readMagentometer()
{
    getMagnetometerValue(&magnetometer_x,&magnetometer_y,&magnetometer_z);
    return magnetometer_x, magnetometer_y, magnetometer_z;
}

int readAccelerometer()
{
    getMagnetometerValue(&accelerometer_x,&accelerometer_y,&accelerometer_z);
    return accelerometer_x, accelerometer_y, accelerometer_z;
}

int readGyroscope()
{
    getMagnetometerValue(&gyroscope_x,&gyroscope_y,&gyroscope_z);
    return gyroscope_x, gyroscope_y, gyroscope_z;
}

void readMessage(int messageId, char *payload, float *temperatureValue, float *humidityValue, float *pressureValue, int *magXvalue, int *magYvalue, int *magZvalue, int *accXvalue, int *accYvalue, int *accZvalue, int *gyrXvalue, int *gyrYvalue, int *gyrZvalue)
{
    JSON_Value *root_value = json_value_init_object();
    JSON_Object *root_object = json_value_get_object(root_value);
    char *serialized_string = NULL;

    //float t = readTemperature();
    readTemperature();
    readHumidity();
    readPressure();
    readMagentometer();
    readAccelerometer();
    readGyroscope();

   *temperatureValue = temperature;
    json_object_set_number(root_object, "temperature", temperature);
    
    *humidityValue = humidity;
    json_object_set_number(root_object, "humidity", humidity);

    *pressureValue = pressure;
    json_object_set_number(root_object, "pressure", pressure);

    *magXvalue = magnetometer_x;
    *magYvalue = magnetometer_y;
    *magZvalue = magnetometer_x;
    json_object_set_number(root_object, "magnetometer_x", magnetometer_x);
    json_object_set_number(root_object, "magnetometer_y", magnetometer_y);
    json_object_set_number(root_object, "magnetometer_z", magnetometer_z); 

    *accXvalue = accelerometer_x;
    *accYvalue = accelerometer_y;
    *accZvalue = accelerometer_z;
    json_object_set_number(root_object, "accelerometer_x", accelerometer_x);
    json_object_set_number(root_object, "accelerometer_y", accelerometer_y);
    json_object_set_number(root_object, "accelerometer_z", accelerometer_z); 

    *gyrXvalue = gyroscope_x;
    *gyrXvalue = gyroscope_y;
    *gyrZvalue = gyroscope_z;
    json_object_set_number(root_object, "gyroscope_x", gyroscope_x);
    json_object_set_number(root_object, "gyroscope_y", gyroscope_y);
    json_object_set_number(root_object, "gyroscope_z", gyroscope_z); 

    serialized_string = json_serialize_to_string_pretty(root_value);

    snprintf(payload, MESSAGE_MAX_LEN, "%s", serialized_string);
    json_free_serialized_string(serialized_string);
    json_value_free(root_value);
    return;
}

#if (DEVKIT_SDK_VERSION >= 10602)
void __sys_setup(void)
{
    // Enable Web Server for system configuration when system enter AP mode
    EnableSystemWeb(WEB_SETTING_IOT_DEVICE_CONN_STRING);
}
#endif