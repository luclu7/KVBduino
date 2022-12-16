# import serial and open serial port
import serial, time
ser = serial.Serial('/dev/ttyACM0', 115200, timeout=1)

# if serial port is open
if ser.isOpen():
    # TEST SEPT SEGMENTS
    time.sleep(1)
    # loop 10 times
    for i in range(10):
        # convert to bytes and write to serial port
        ser.write(bytes('{"visu": '+str(i)+'}\n', 'utf-8'))
        print('{"visu": '+str(i)+'}')
        # wait 1 second
        time.sleep(0.5)
    ser.write(bytes('{"visu": '+str(16)+'}\n', 'utf-8'))
    print('{"visu": '+str(16)+'}')
    time.sleep(0.5)

    ser.write(bytes('{"visu": '+str(0)+'}\n', 'utf-8'))
    print('{"visu": '+str(0)+'}')
    time.sleep(0.5)

    ser.write(bytes('{"visu": '+str(16)+'}\n', 'utf-8'))
    print('{"visu": '+str(16)+'}')
    ser.write(bytes('{"visu": '+str(16)+'}\n', 'utf-8'))
    time.sleep(1)

    ser.write(bytes('{"visu": '+str(1)+'}\n', 'utf-8'))
    print('{"visu": '+str(1)+'}')
           
print("done")
ser.close()