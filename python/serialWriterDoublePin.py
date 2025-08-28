import serial
import time
import argparse
import sys

def read_response(ser, timeout=0.2):
    """Read all lines from Arduino until no new data arrives for 'timeout' seconds."""
    lines = []
    ser.timeout = timeout
    start_time = time.time()

    while True:
        line = ser.readline().decode('ascii').strip()
        if line:
            lines.append(line)
            start_time = time.time()  # reset timer when new data arrives
        else:
            # If no new data for 'timeout' seconds, break
            if time.time() - start_time > timeout:
                break
    return lines


def main():

    parser = argparse.ArgumentParser(
        formatter_class = argparse.ArgumentDefaultsHelpFormatter,
        description="")
    parser.add_argument('-d', '--device',default="/dev/tty.usbmodem1301",help="serial device to write to")


    args = parser.parse_args()
    
    baud = 9600
    interface = args.device # Vale's adapter
    timeout = .1
    arduino_serial = serial.Serial(port=interface, baudrate=baud, timeout=timeout)
    

    # Read the serial before starting anything
    lines = read_response(arduino_serial)
    for l in lines:
        print(l)
    
    while True:
        cmd = input("Insert command for arduino... ")
        if (cmd == "exit"):
            sys.exit()
        arduino_serial.write(cmd.encode('ascii'));

        
        lines = read_response(arduino_serial)
        for l in lines:
            print(l)
        

if __name__ == "__main__":
    main()
