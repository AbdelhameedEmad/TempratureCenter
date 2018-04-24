# Temprature Center

Arduino code for NodeMCU ESP8266 ( board: nodemcu 1.0 (esp-12e module) ) to read and send readings of a Temperature sensor and it's time of reading to any device connected to it through a HC-05 bluetooth module.

If the esp received from the Client connected to it "send" which is considered an order to send all the stored readings, sends it and waits for an acknowledgement "ack" that the data is received correctly and gives the nodemcu permission to erase the data.

If the esp didn't get an acknowledgement from the reciever it will retransmit the data untill it gets an acknowledgement.

This is a part of an IOT project where an Android device connects to the HC-05 module and gets the readings and displays it. (using android app called Bluetooth Terminal)
