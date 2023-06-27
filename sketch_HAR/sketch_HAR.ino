/*
  Captura de IMU
  Este ejemplo utiliza la IMU incorporada para leer datos de aceleración y giroscopio
  de la IMU incorporada y los imprime en el Monitor Serie durante un segundo
  cuando se detecta un movimiento significativo.
  También puedes utilizar el Visualizador Serie para graficar los datos.
  Circuito:
  - Placa Arduino Nano 33 BLE o Arduino Nano 33 BLE Sense.
  Creado por Don Coleman, Sandeep Mistry
  Modificado por Dominic Pajak, Sandeep Mistry
  Este código de ejemplo es de dominio público.
*/

#include <Arduino_LSM9DS1.h>

const float accelerationThreshold = 2.5; // umbral de movimiento significativo en G's
const int numSamples = 119;

int samplesRead = numSamples;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("¡Error al inicializar la IMU!");
    while (1);
  }

  // Imprime la cabecera
  Serial.println("aX,aY,aZ,gX,gY,gZ");
}

void loop() {
  float aX, aY, aZ, gX, gY, gZ;

  // Espera a que ocurra un movimiento significativo
  while (samplesRead == numSamples) {
    if (IMU.accelerationAvailable()) {
      // Lee los datos de aceleración
      IMU.readAcceleration(aX, aY, aZ);

      // Calcula la suma de los valores absolutos
      float aSum = fabs(aX) + fabs(aY) + fabs(aZ);

      // Verifica si supera el umbral
      if (aSum >= accelerationThreshold) {
        // Reinicia el contador de muestras leídas
        samplesRead = 0;
        break;
      }
    }
  }

  // Verifica si se han leído todas las muestras requeridas desde
  // la última vez que se detectó un movimiento significativo
  while (samplesRead < numSamples) {
    // Verifica si hay nuevos datos de aceleración y giroscopio
    if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {
      // Lee los datos de aceleración y giroscopio
      IMU.readAcceleration(aX, aY, aZ);
      IMU.readGyroscope(gX, gY, gZ);

      samplesRead++;

      // Imprime los datos en formato CSV
      Serial.print(aX, 3);
      Serial.print(',');
      Serial.print(aY, 3);
      Serial.print(',');
      Serial.print(aZ, 3);
      Serial.print(',');
      Serial.print(gX, 3);
      Serial.print(',');
      Serial.print(gY, 3);
      Serial.print(',');
      Serial.print(gZ, 3);
      Serial.println();

      if (samplesRead == numSamples) {
        // Agrega una línea vacía si es la última muestra
        Serial.println();
      }
    }
  }
}
