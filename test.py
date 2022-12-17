# import serial and open serial port
import serial, time
ser = serial.Serial('/dev/ttyACM0', 115200, timeout=1)


# structure of different buttons
class Buttons:        
    def __init__(self, buttons):
        self.VAL = buttons  & 0b00001 != 0
        self.MV = buttons   & 0b00010 != 0
        self.FC = buttons   & 0b00100 != 0
        self.TEST = buttons & 0b01000 != 0
        self.SF = buttons   & 0b10000 != 0

    def __str__(self) -> str:
        return f"VAL: {self.VAL}, MV: {self.MV}, FC: {self.FC}, TEST: {self.TEST}, SF: {self.SF}"

    

# if serial port is open, wait for # to be received
if ser.isOpen():
    print("Serial port is open")
    time.sleep(1)
    count = 2
    while True:
        # read serial port
        line = ser.readline()
        # if line is longer than 0 and first character is #
        if len(line) > 0 and line[0] == 35:
            print("init: "+ str(line).rstrip())
            count -= 1
        
        # if count is 0, break
        if count == 0: 
            break

    while True:
        # read serial port
        line = ser.readline()
        # if # is received, break
        # if first character of line is #, break
        # if line is longer than 0 and first character is #
        if type(line) == bytes and len(line) > 0:
            if len(line) > 0 and line[0] == 35:
                print("Comment: "+ str(line).rstrip())
            else:
                buttonsInt = line[0]
                print(f"{buttonsInt:#07b}"[2:])
                buttons = Buttons(buttonsInt)
                print(buttons)

    print("Start test")
    time.sleep(1)


# if serial port is open
if ser.isOpen():
    time.sleep(1)
    # TEST SEPT SEGMENTS
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

    # test LSSF 3 times
    for i in range(3):
        ser.write(bytes('{"LSSF": '+str(1)+'}\n', 'utf-8'))
        print('{"LSSF": '+str(1)+'}')
        time.sleep(1)
        ser.write(bytes('{"LSSF": '+str(0)+'}\n', 'utf-8'))
        print('{"LSSF": '+str(0)+'}')
        time.sleep(1)
           
print("done")
ser.close()


