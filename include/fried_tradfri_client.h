#pragma once

#include "fried_coaps_client.h"
#include "fdata.h"

//These have to be defined!
//#define FRIED_TRADFRI_GATEWAY_IP "192.168.2.9"
//#define FRIED_TRADFRI_IDENTITY "tradfri_12345"
//#define FRIED_TRADFRI_KEY "IaY5AQRXw1awfqEt"

void tradfri_init();
char* join_url(const char* base, const char* sub);
char* Tradfri_send(coap_pdu_code_t method, bool wait, const char* suburl, const char* data, size_t data_len);
char* Tradfri_GET(const char* suburl);
char* Tradfri_PUT(const char* suburl, const char* data);
char* GetTradfriDevices();
char* GetTradfriDeviceInfo(const char* deviceId);
void UpdateTradfriDeviceInfo(const char* deviceId, fdata json);
void SetBrightnessTradfriLamp(const char* deviceId, uint8_t brightness);
void SetColorTradfriLamp(const char* deviceId, uint16_t x, uint16_t y);