"""
Serial Communication Module
Example Send: $000027
Example Receive: 123#456

-Install
sudo apt-get install python3-serial
sudo usermod -a -G tty murtaza
-Allow read and write access to port
sudo chmod 666 /dev/ttyACM0
Main shows the example of send and recieve
with arduino connected to Potentiometer and
Servo Motor. (Servo Knob Example)

by: Murtaza Hassan
Website: www.murtazahassan.com
Youtube: Murtaza's Workshop - Robotics and AI
"""

import serial


def initConnection(portNo, baudRate):
    """
    :param portNo: COM port No e.g.
           Win: 'COM3'
           Linux: '/dev/ttyACM0'
           mac: '/dev/cu.usbmodem14201'
    :param baudRate: BaudRate set in the Serial Device
    :return: Initialzed Serial Object
    """
    try:
        ser = serial.Serial(portNo, baudRate)
        print("Device Connected ")
        return ser
    except:
        print("Not Connected ")
        pass


def sendData(se, data, digits):
    """
    :param se: Serial Object already Initialized
    :param data: Data List that needs to be transmitted
    :param digits: digits per value  eg digits = 3  will give 024  for value 24
    :return: null
    """
    myString = "$"
    for d in data:
        myString += str(int(d)).zfill(digits)

    try:
        se.write(myString.encode())
        print(myString)
    except:
        print("Data Transmission Failed ")


def getData():
    """
    :param numOfVals: number of vals to retrieve
    :return: list of data received
    """
    data = ser.readline()
    data = data.decode("utf-8")
    data = data.split('#')
    dataList = []
    [dataList.append(d) for d in data]
    return dataList[:-1]

def main():

    data = getData()  # Get List of Arduino Value
    print(data[0])    # Print First value which is potentiometer
    sendData(ser, [data[0], 0], 4) # Send the Pot Value back

if __name__ == "__main__":
    # Connect to Arduino Device
    ser = initConnection('/dev/ttyACM0', 9600)
    while True:
        main()