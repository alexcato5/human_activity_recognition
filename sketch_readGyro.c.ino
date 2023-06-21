//#include <Wire.h>
#include <Arduino_LSM9DS1.h>

void setup() {
  Serial.begin(115200);
  //IMU.setGyroScale(245); // Configura la escala del giroscopio (opciones: 245, 500, 2000)
  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }
  if (!IMU.begin()) {
    Serial.println("No se pudo encontrar el sensor LSM9DS1");
    while (1);
  }
}


void loop() {
  float gx, gy, gz;
  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(gx, gy, gz);  
    String gyroString = String(gx) + "," +
                        String(gy) + "," +
                        String(gz);
    Serial.println(gyroString);
  }
  
  delay(10);
}
