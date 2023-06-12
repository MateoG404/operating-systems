import csv
from faker import Faker
import random

# Crear una instancia de Faker
faker = Faker()

# Generar 1000 datos ficticios
datos = []
for _ in range(10000):
    nombre = faker.first_name()
    apellidos = faker.last_name()
    edad = random.randint(18, 65)
    universidad = faker.company()
    carrera = faker.job()
    porcentaje_avance = random.randint(0, 100)
    trabajo_sonado = faker.job()
    banda_musical = faker.word()
    datos.append([nombre, apellidos, edad, universidad, carrera, porcentaje_avance, trabajo_sonado, banda_musical])

# Definir el nombre del archivo CSV
file_name = 'informacion.csv'

# Abrir el archivo CSV en modo de escritura
with open(file_name, 'w', newline='') as csv_file:
    writer = csv.writer(csv_file)

    # Escribir las filas de encabezado
    writer.writerow(['Nombre persona', 'Apellidos', 'Edad', 'Universidad', 'Carrera que estudia', 'Porcentaje avance de carrera', 'Trabajo soñado', 'Banda musical favorita'])

    # Escribir los datos en filas
    for fila in datos:
        writer.writerow(fila)

print(f"Archivo CSV '{file_name}' creado exitosamente.")
