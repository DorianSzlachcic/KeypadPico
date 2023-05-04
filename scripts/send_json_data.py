import time
import serial

ser = serial.Serial('COM11')

with open('example.json', "rb") as file:
    start = time.time()

    while True:
        buf = file.read(64)
        if not buf:
            break

        ser.write(buf)
        print('Sending: ', buf, "Size: ", len(buf))
        resp = None
        while resp != b'Ack\n':
            resp = ser.readline()
        print('Ack')

    stop = time.time()
    print("Elapsed time: ", stop - start)
