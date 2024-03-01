#include <MPU6050_tockn.h>
#include <Wire.h>
#include <DHT.h>
#include <WiFi.h>
#include <Adafruit_BusIO_Register.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <pgmspace.h>

#define THINGNAME "hackfest"
#define LED 23
#define DHTPIN 14
#define DHTTYPE DHT11 
const char *ssid  = "realme5s";     
const char *password = "error404";  
const char AWS_IOT_ENDPOINT[] = "a2jtmsm4glnf6c-ats.iot.us-east-1.amazonaws.com"; 

// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
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

// Device Certificate //change this
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUQv7wNY9S/6/SkkjAqcEzoV0zD70wDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTI0MDIyOTIxNTc1
OVoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAOMPE2s6/zrFwJm324Qq
38zLyUpNOD2n70ou4uqaTsNSlMjTbz42bNMaEneCZgiO42RnXbYE7PM86Vq5SWVM
9EfwplQ2AKGXuihcRRJRYGARQo2B6xC6Vc1s2A0opjDIM5YIqBTYnBZygDEjC5Rs
FH/lmWQX6jsFEtCuDnPTGlqD1koFFxWoObl5xcEj/vYPOo5TbEEu+MXlEubk/swP
hqozIa61bk3c9vhrmimNeaXJYO0aGvZ7yMv06KpRAT2HtQJKA48E7eAkOmbsCVT5
fP3LCAnn2ranATM2rXi05reiaBYYG3DOmEreIuOE44jtth8NGlN4Ruy3nQtPNS8o
3hcCAwEAAaNgMF4wHwYDVR0jBBgwFoAUCow7Jm/WdUsk5FQGA6VOedzWeOAwHQYD
VR0OBBYEFJYOckSsGZVJwiRmiOgxmEtQ1pUZMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQBcSSfgMcP4VO0uYOeevCevDNKW
8DD8I7qTjmrcJzP+TXXRPkxuTj3/X5YkQEz1P1cTLmAfR9TvKpJN5wzMbDjR25O7
BMWgxkuRGDKKECpvZHfdoTd/ATXiX4YNz70rk2/RsHLJsEYhWIZF05V4q+fy71HO
ZeGcfZlQV+4LLVEgL1UUDQVKgaLbYl9rQ+VYrMuMrc8bd+WuibWWiNZeI/JJNqfH
fJferUzT0UZRXKi02fOkQCFM82mqY6B2SjQCPwDA6fy56k1XaliiCKbHzW0Qfntt
oA6ftrMChPP99X+RKZKXKI9wNZXJIJUrwTgmpMxaGjadKkpKVE8t67O323jq
-----END CERTIFICATE-----


)KEY";

// Device PRIVATE Key //change this
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpAIBAAKCAQEA4w8Tazr/OsXAmbfbhCrfzMvJSk04PafvSi7i6ppOw1KUyNNv
PjZs0xoSd4JmCI7jZGddtgTs8zzpWrlJZUz0R/CmVDYAoZe6KFxFElFgYBFCjYHr
ELpVzWzYDSimMMgzlgioFNicFnKAMSMLlGwUf+WZZBfqOwUS0K4Oc9MaWoPWSgUX
Fag5uXnFwSP+9g86jlNsQS74xeUS5uT+zA+GqjMhrrVuTdz2+GuaKY15pclg7Roa
9nvIy/ToqlEBPYe1AkoDjwTt4CQ6ZuwJVPl8/csICefatqcBMzateLTmt6JoFhgb
cM6YSt4i44TjiO22Hw0aU3hG7LedC081LyjeFwIDAQABAoIBAA1XlnGHnvXKJv4h
YqHKjyoOk35tOS/OTW5TgPv+I0Cw+pMucWv7cLua3ZjuLaa1FsGQnV4TvgSxAJlX
J+vu8K/FgVCTd8gHDWZPvbNM2tfqS7na94AdIuuWSL/FMrbNHNLlIVNQQyPCiKva
flSzYST+zdum2Bmtu6RNhgXiUrscxcYuM52m0D2XaNijOySMfOvzYHNE5GPIoH1m
Ct9ICbC4DrF5YEfIYAWKcaLA4sRhbfcF+79HU8cJ3xRbNlrCPQO/NzzDg+ZQpJ5A
YOnpm/PrrkA0uc6UyZKLQaUjZ0wNUkiID0ySyEDsBll7jrEzM9LmB6X7JTMAI40z
eKDXjHkCgYEA8WQQ018NM6CErXTnmjvgqEWqIILLAPiBK5dRNp6S8XzEWJY8XH16
2tsPP5R3N7cO/DbwnRlD9Cf5kJ21cZacItDQsw1X2vCyq+NHBhKkYeKkut/bgpqN
aDRHMCODinzxVWnJcAmJoW+nroJx1Y0zeoQdl/jjEb2e8zGjj2QEdAsCgYEA8Mz1
8KC00uJFTXnEWhsP9gkXFoUQsighE6YYDTmXX+Ezhx2nSXGtcL6Z5ita5JUJ4ELD
RDY5jibDkAHRsShxZx4dLfC1NNl4aH8w3iVhabZUW6niMofAgl80WK2aXSEwr14K
vfmC/4STXs6iKpWPfK3CEc8QHD7lLJYhDlb/GaUCgYEAiICRkzW4/WzUGlJ1dZ5O
mFlsrx3HNjFQuhnDbyOU7MIlNgMe9x5uDry5jraiA/ucmbtnrS7QYo0Ib2L/a9BD
UtzKZ7Yv7DsYjmLjkueP1VqY1KQqOVy0giyt5ObwR6wHvMkphBWgoo3FQMW7IYvL
hIiZQ4sWvL2B2PxFBZ0Fd6kCgYEA7ZIpavgCrrRSj3d9QzDD9IdPYgZyTHLO/2W1
AQc603uJrNqSuyEObtd9WtqXWEG6dqknoVqmOhsAgklpKpGuIIBTZYnAHZ4Y72/d
NK5Ih1U9sRnQcu3//iATsxHD4/Hk6H+ttXQ/y/xusPDIiZ7465c6ivtw940N6YlM
n6sxD4kCgYB43EcwBw/SI12aR73LdFPixqKRo/iumN4fLvv6yNNSJfoZBtsTHYvv
PZsAfJDd88qsSVrO9uTw6QnfeZCgO+zPBLjEKxhU4Oc95K05scqLHat/sXQsdd+M
Zrad+JQstbUBq0QrS/sdyRdrtjNWFcD/dSWttc0mxekyJYeY09qxww==
-----END RSA PRIVATE KEY-----


)KEY";

#define AWS_IOT_PUBLISH_TOPIC "hackfest/01/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "hackfest/+/sub"

WiFiClientSecure net;
PubSubClient client(net);

MPU6050 mpu6050(Wire);
DHT dht(DHTPIN, DHTTYPE);

long timer = 0;

void connectAWS() {
  WiFi.begin(ssid, password);

  Serial.println("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting....");
  }

  Serial.println("Connected to WiFi network");

  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  client.setServer(AWS_IOT_ENDPOINT, 8883);

  client.setCallback(messageHandler);

  Serial.println("Connecting to AWS IOT");

  while (!client.connect(THINGNAME)) {
    Serial.print(".");
    delay(1000);
  }

  if (!client.connected()) {
    Serial.println("AWS IoT Timeout!");
    return;
  }

  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);

  Serial.println("AWS IoT Connected!");
}

int deviceIdCounter = 10000;
String generateRandomDeviceID() {
  // Generate a random 5-digit integer
  deviceIdCounter = (deviceIdCounter % 99999) + 1;

  return String(deviceIdCounter);
}

void publishMessage() {
  
  StaticJsonDocument<200> doc;
  doc["temperature"]=  mpu6050.getTemp();
  doc["vibrationX"] = mpu6050.getAccX();
  doc["vibrationY"] = mpu6050.getAccY();
  doc["vibrationZ"] = mpu6050.getAccZ();
  doc["vibrationAngleX"] = mpu6050.getAngleX();
  doc["vibrationAngleY"] = mpu6050.getAngleY();
  doc["vibrationAngleZ"]= mpu6050.getAngleZ();
  
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer);
  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}

void messageHandler(char *topic, byte *payload, unsigned int length) {
  Serial.print("incoming: ");
  Serial.println(topic);

  StaticJsonDocument<200> doc;
  deserializeJson(doc, payload);
  const char *message = doc["message"];
  Serial.println(message);
}

String uint64ToHexString(uint64_t value) {
  char buf[17];
  snprintf(buf, sizeof(buf), "%016llx", value);
  return String(buf);
}



void setup() {
  
  
  Serial.begin(9600);
  connectAWS();

  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  dht.begin();
  pinMode(LED, OUTPUT);
}

void loop() {
  
  publishMessage();
  mpu6050.update();
  float ax = mpu6050.getAccX();
  float ay = mpu6050.getAccY();
  float az = mpu6050.getAccZ();

  float gx = mpu6050.getGyroAngleX();
  float gy = mpu6050.getGyroAngleY();
  float gz = mpu6050.getGyroAngleZ();

  float Ax = mpu6050.getAngleX();
  float Ay = mpu6050.getAngleY();
  float Az = mpu6050.getAngleZ();

  if (millis() - timer > 1000) {
    Serial.println("=======================================================");

    Serial.print("accX : ");
    Serial.print(ax);
    Serial.print("\taccY : ");
    Serial.print(ay);
    Serial.print("\taccZ : ");
    Serial.println(az);

    Serial.print("gyroAngleX : ");
    Serial.print(gx);
    Serial.print("\tgyroAngleY : ");
    Serial.print(gy);
    Serial.print("\tgyroAngleZ : ");
    Serial.println(gz);

    Serial.print("angleX : ");
    Serial.print(Ax);
    Serial.print("\tangleY : ");
    Serial.print(Ay);
    Serial.print("\tangleZ : ");
    Serial.println(Az);
    Serial.println("=======================================================\n");
    timer = millis();
  }

  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
  Serial.println("deviceID"+generateRandomDeviceID());

  if (t > 40.50) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
}