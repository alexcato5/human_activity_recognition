import serial
import pandas as pd
from pathlib import Path
import time

# Nombre del archivo y ruta donde se guardarán los resultados
nombre_archivo = 'resultados'
ruta_resultados = './' + nombre_archivo + '/'
Path(ruta_resultados).mkdir(parents=True, exist_ok=True)

# Definición del DataFrame para guardar los resultados
formato = { 'GIR_X':[0.00], 'GIR_Y':[0.00], 'GIR_Z':[0.00] }
resultados_df = pd.DataFrame(formato)

lectura = [] # Lista donde se guarda el número leído
escritura = [] # Lista donde se guardarán los 3 valores leídos
puerto = serial.Serial('COM4')
tiempo_de_inicio = time.time()

# Se leerán 15 segundos de datos
while time.time() - tiempo_de_inicio <= 15.0:
	caracter_leido = puerto.read()
	caracter_leido = caracter_leido.decode('utf-8')
	if caracter_leido != ',':
		lectura.append(caracter_leido)
	else:
		escritura.append(float(''.join(lectura)))
		lectura.clear()

		if len(escritura) == 3:
			resultados_df.loc[len(resultados_df.index)] = escritura
			print(escritura)
			escritura.clear()

			# Guardar resultados en formato CSV
			resultados_df.to_csv(ruta_resultados + nombre_archivo + '.csv', encoding='utf-8', index=False)
