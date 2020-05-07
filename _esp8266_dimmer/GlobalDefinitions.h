#ifndef _GLOBAL_DEFINITIONS_H_
#define _GLOBAL_DEFINITIONS_H_

#define STR_(x) #x
#define STR(x) STR_(x)

/* PROTOCOL CONFIGURATION (WIFI & MQTT) */

#define WIFI_SSID "MOVISTAR_4CD3"
#define WIFI_PASSWORD "iamLhr9RRQ4NkUuJVSuh"

#define MQTT_BROKER "192.168.1.69"
#define MQTT_CLIENT_ID "ESP8266Client" STR(DEVICE_ID)

/* DEVICE CONFIGURATION (NODE) */

#define DEVICE_ID 1
#define NAME_OF_DEVICE "nombre del dispositivo"
#define DESCRIPTION_OF_DEVICE "descripción del dispositivo"
#define STATUS_OF_DEVICE UNIT_ON

/* UNITS CONFIGURATION */

#define DIMMER_ID 1
#define DIMMER_NAME "nombre del atenuador"
#define DIMMER_DESCRIPTION "descripción del atenuador"
#define DIMMER_TYPE DIMMER
#define DIMMER_PIN 13

#define DIMMER_ZERO_CROSS  12

#define S_TEMPERATURE_ID 2
#define S_TEMPERATURE_NAME "nombre del sensor de temperatura"
#define S_TEMPERATURE_DESCRIPTION "descripción del sensor de temperatura"
#define S_TEMPERATURE_TYPE SENSOR
#define S_TEMPERATURE_MEASURE_RATE_MS 5000

#endif