# Trabajo práctico Nº1
## Conversores AD y DA. Protocolos de comunicación serial cableados
### Objetivos
- Comprender el uso y la utilidad de conversores A/D y D/A.
- Implementar una comunicación serial entre un sistema embebido simple y una computadora.
- Integrar el sistema embebido a un sistema de IoT completo.
### Aprobación
- Mostrar en clases la aplicación funcionando correctamente.
- Enviar los programas de computación implementados a través de la plataforma Moodle.
- Escribir un breve informe y enviarlo a través de la plataforma Moodle.

# Actividad 1:
Realizar una aplicación que realice las siguientes tareas a través de una página web sencilla:
1. Controle el brillo de los led 9, 10 y 11 del Arduino UNO utilizando el conversor Digital a Analógico del mismo. El brillo de estos leds debe controlarse de forma independiente para cada led.
2. Encienda y apague el led 13 del Arduino UNO. Deberá utilizar dicho pin como salida digital.
3. Muestre la intensidad luminosa captada por el LDR (conectado al pin A3 del Arduino UNO). Deberá utilizar el conversor Analógico a Digital.
4. El control del brillo de los led 9, 10 y 11, el pin 13 y el valor de la intensidad luminosa sensado por el LDR deberá realizarse y mostrarse a través de una página web que deberá poder accederse desde otras computadoras conectadas en la misma red LAN o Internet.
5. La página web debe mostrar el valor actual del brillo de los leds, el estado del pin 13 y el valor leído por el LDR.

Si bien la salida del circuito debe calcularse en función de las especificaciones del LDR y los valores de las resistencias del circuito, en este trabajo práctico se pide solo mostrar el valor digital leído en el pin 3, sin realizar ninguna conversión.
