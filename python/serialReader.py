import serial
import time


def read(device):
    data = device.readline()
    return data.decode()


def main():

    baud = 9600
    interface = "/dev/tty.usbmodem14201" # Vale's adapter
    timeout = .1
    arduino_serial = serial.Serial(port=interface, baudrate=baud, timeout=timeout)
    
    
    while True:

        #Check if incoming bythes are waiting to be read from the serial input
        if (arduino_serial.in_waiting >  0):
            value = read(arduino_serial)
            print(value)

        #Sleep 10ms to let other threads run
        time.sleep(0.01)


if __name__ == "__main__":
    main()
