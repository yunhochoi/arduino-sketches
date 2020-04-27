import serial

with serial.Serial('COM3', 9600) as ser:
    x = ser.readline()
    print(x)
    message = "This is my arduino message\n"
    ser.write(message.encode())

    y = ser.readline()
    print(y)

    ser.close()