#include <Arduino_LSM9DS1.h>

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }
  if (!IMU.begin()) {
    Serial.println("No se pudo encontrar el sensor LSM9DS1");
    while (1);
  }
}


void loop() {
  // Definición de variables para valores de acelerómetro y giroscopio
  float ax, ay, az;
  float gx, gy, gz;

  // Se verifica que los sensores estén disponibles
  if (IMU.gyroscopeAvailable()&&IMU.accelerationAvailable()) {
    IMU.readAcceleration(ax, ay, az);
    IMU.readGyroscope(gx, gy, gz);  
    String datosString = String(ax) + "," +
                         String(ay) + "," +
                         String(az) + "," +
                         String(gx) + "," +
                         String(gy) + "," +
                         String(gz) + ",";
    Serial.print(datosString);
  }
  
  delay(10);
}
