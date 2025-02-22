#include <pgmspace.h>

#define SECRET
#define THINGNAME "ESP32_LED"

const char WIFI_SSID[] = "SahilA_5G";
//change this
const char WIFI_PASSWORD [] = "sahil932004";
//change this
const char AWS_IOT_ENDPOINT [] = "a2c9qlmk9dg943-ats.iot.ap-south-1.amazonaws.com";
//change this

// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM=R"EOF(

-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----

)EOF";
// Device Certificate
//change this

static const char AWS_CERT_CRT[] PROGMEM = R"KEY(

-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUGnfUBUCW3eVTeZlCEICWvIwvywowDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTI1MDEyMzE2MTk1
NVoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALVknSEI5AX3VxbAUrGK
HR4nIWnw97nVLYOVc8rXnrEqsriGJMfQmALW4oKQFG4NHot02fyR2VRRNkvQeaVO
79gQzeRvyDH18XIO/KaS81TmdGQMkkHAspwP5rS3nmEW3Y1Yke70eLhyeF7sDxOq
yNGbKpCqKK/sATJzcWWk78sbPYmn9Xqe5rEEXpdh1Rql794DJWvseKfDDsuEHmiy
SebQiKVK2JCJDG6bkpf6I19V9C1m+JMtN8dJ6CWIxXO716n0gMC3klauo75OiMKn
xVRN96lYde/7G92ghD6FLSa3TUQYbLpWvf6h+7lp8Yh5VO1cU8LK6TctkPRuhTYk
t0MCAwEAAaNgMF4wHwYDVR0jBBgwFoAUhDJ+FWP8UKgofNVmzIgJIElBQ8MwHQYD
VR0OBBYEFC5+LPOtOcVd/zuR7ihooSnAujEHMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQBLAxcCuK4FSyyBLZ2EJuNZVTAF
9pHcVqx6l9JTFuU7yw7PuEbpOAkI0419xvuKqz0EiiUzEhUibrIFp+lAhaRsHQ9N
vO6RtQ9qjlL8fnlC1FfUe+5xDXD9SkJneBjx7ICvjVASoQhAtkA53ltVjoHIHF1c
5c016UK1IK1Jtd9Ex/gkBgH3XRIbwBvKPDfPpqETV/ikNvfEHXYqAuv/lzAKsP9X
fZQNUD9UB6DnRb3Kx8yOTepf0Ty1cH6wDFFpGDc8hkie9HS0NzTLaIk19oi1bYeh
8ZcNnanNYAIG4f8nmtCc0lJ64SzSmKdORXgXFWoYSig+xHtO5vEAuSMFMLgw
-----END CERTIFICATE-----

)KEY";
// Device Private Key

static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(

-----BEGIN RSA PRIVATE KEY-----
MIIEpQIBAAKCAQEAtWSdIQjkBfdXFsBSsYodHichafD3udUtg5VzyteesSqyuIYk
x9CYAtbigpAUbg0ei3TZ/JHZVFE2S9B5pU7v2BDN5G/IMfXxcg78ppLzVOZ0ZAyS
QcCynA/mtLeeYRbdjViR7vR4uHJ4XuwPE6rI0ZsqkKoor+wBMnNxZaTvyxs9iaf1
ep7msQRel2HVGqXv3gMla+x4p8MOy4QeaLJJ5tCIpUrYkIkMbpuSl/ojX1X0LWb4
ky03x0noJYjFc7vXqfSAwLeSVq6jvk6IwqfFVE33qVh17/sb3aCEPoUtJrdNRBhs
ula9/qH7uWnxiHlU7VxTwsrpNy2Q9G6FNiS3QwIDAQABAoIBAQCnUZuu8SiEaFao
4dZldeTN/4JO2rtna0CEc8NPg/0Zpy0cEIC037CYTea6UHTH3soiETNSSqaRpCfV
XwQWe+24/CcvY/ziON7yOujKLhrOYZVTBFWU2U7nrbM9V3J8VD8hNmXGaTNB0DVA
ObbeiVacIejtcEf/nk6sXthmzfFzAqp06E0zbT8gbakdX1WH0XDnJ3xZa4eK5d8n
dS3eAu/O8c1iERpMx7evLbRiX7oeLWZukUQSNpsoeQYQz4csseKdSl8XEH6QKR5T
IKFtqwLtUMeyyr5FLj+FejRxw0kG1O6Z4DxFflta9hxeYGAYQoTYKXk4ENSNG1JG
7WNFnbyBAoGBAOtXa5ZvsV8ulJBhjsJhPouQY1EvyVIu3FwEhzNpzVXPOT4cRYJ2
2piXDa+7RijazhR/QuZQBSYqcWkKilnOGT/vy85LdFw/zOnvLLk011PJyNUXq05z
L5M/zX8mYCtxxRdBblbZ4prtnwe4H+SGz4e8NUB3yvrfwqeIzZpTQpKTAoGBAMVQ
3e1U+ZzuKnNRwU8H52Facg/Sm4PhgsQiWxfwPRi9hOkv4IJe/M+FV9Xi76ceX5K5
6jJDLdbWihMpeFBkIJac2ahoOKJpca4rwl+tvhQ9R3j6HL6IjG7Ext3QEevltJSj
FQvoxsvGHiSm5jftaPiYb+ymAS6Q8XYbUmmg5saRAoGBANCI7jSnVCxbQhmN2Mo1
EQ7qKpdOGL5R98Ex4fuUzPY0YSzAMHeiiaCceOw2rbyV5fYTrlwWm/ltsoC5bk6V
aZpWCeoKwljbz9+ap66VPBhqvSLVjl49gvKfnqAEiUL11Qb+W59qAnn2BOz6IoiF
TG+iPi2Z+KrEi9+YQVd2X48xAoGBAKNZOhCTi33WUYBci0sRAQVAajMdKK+6TpZu
1rjvorTLmK+veg6T8nkeK8Qe9kWEyJxgmzh3EwjLXU1VxIvRCIWHXk2j0lbqMjl9
cpHg9P4uaPAHJyq5QoElGHljGqMO7Dss82yDjaf+4M94+BgOzBsZn3brSwkw5yTe
o5BcqxBxAoGAVBDTeLqnSROrocEpzExM34jrVASJ4E32BtxaNHZhNdvkrKXyId7t
HDREOZrrhznB3xn2fCl7GQ7o7N8UtJnPLIqwiBcYdahUxdaz4lk2ol3PyE7vEB8U
aoXDAOORSwy0ha20y6h1yneAErBpilkSuNyWzD1DPSKflzPhZS1RU8k=
-----END RSA PRIVATE KEY-----

)KEY";