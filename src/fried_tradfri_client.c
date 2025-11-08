#include "fried_tradfri_client.h"

void tradfri_init()
{
    coaps_init();
}

char* join_url(const char* base, const char* sub) {
    size_t len = strlen(base) + strlen(sub) + 1;
    char* out = (char*)malloc(len);
    if (!out) return NULL;
    strcpy(out, base);
    strcat(out, sub);
    return out;
}

char* Tradfri_send(coap_pdu_code_t method, bool wait, const char* suburl, const char* data, size_t data_len)
{
    const char* baseurl = "coaps://192.168.2.9:5684";
    char* fullurl = join_url(baseurl, suburl);
    if (!fullurl) return NULL;

    printf("%s\n", fullurl);
    if (data)
        printf("data: %s\n", data);
    char* result = CoAPsSend(method, wait, fullurl, "tradfri_12345", "IaY5AQRXw1awfqEt", data, data_len);
    free(fullurl);
    return result;
}
char* Tradfri_GET(const char* suburl)
{
    return Tradfri_send(COAP_REQUEST_CODE_GET, true, suburl, NULL, 0);
}
char* Tradfri_PUT(const char* suburl, const char* data)
{
    size_t len = data ? strlen(data) : 0;
    return Tradfri_send(COAP_REQUEST_CODE_PUT, false, suburl, data, len);
}

char* GetTradfriDevices()
{
    return Tradfri_GET("/15001");
}

char* GetTradfriDeviceInfo(const char* deviceId)
{
    const char* basepath = "/15001/";
    char* path = join_url(basepath, deviceId);
    if (!path) return NULL;

    char* result = Tradfri_GET(path);
    free(path);
    return result;
}

void UpdateTradfriDeviceInfo(const char* deviceId, fdata json)
{
    const char* basepath = "/15001/";
    char* path = join_url(basepath, deviceId);
    if (!path) return;

    char* json_str = f_serialize(json);
    if (!json_str) {
        free(path);
        return;
    }

    Tradfri_PUT(path, json_str);

    free(json_str);
    free(path);
}

void SetBrightnessTradfriLamp(const char* deviceId, uint8_t brightness)
{
    fdata obj = f_create();
    f_set_int(obj, "5851", brightness);

    fdata json = f_create();
    f_set_arr(json, "3311", &obj, 1); // single object array

    UpdateTradfriDeviceInfo(deviceId, json);

    f_free(json); // frees nested objects too
}
void SetColorTradfriLamp(const char* deviceId, uint16_t x, uint16_t y)
{
    fdata obj = f_create();
    //f_set_int(obj, "5850", 1);   // power on
    //f_set_int(obj, "5851", 254); // brightness (max)
    f_set_int(obj, "5709", x);   // X color coordinate
    f_set_int(obj, "5710", y);   // Y color coordinate
    f_set_int(obj, "5712", 25);  // 2.5-second transition

    fdata json = f_create();
    f_set_arr(json, "3311", &obj, 1);

    UpdateTradfriDeviceInfo(deviceId, json);
    f_free(json);
}