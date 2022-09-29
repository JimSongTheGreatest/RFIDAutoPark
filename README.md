### RFID Auto Park

1. Before assembling anything, first of all, scan the card and read the Unique ID of every card, and note the values of RFID Cards

2. 5 Cards used in the code, so scan all the cards and enter the IDs in the code

3. We are using 2 I2C LCDs, so must change the I2C address of one LCD and Change the I2C Address of that LCD in the code

Let's Start
1. Make the circuit as shown in the circuit diagram, Do not connect the 1st RFID Reader(whose pin is connected to the Tx Pin Of Arduino), because programming is not possible when this pin is connected.

2. Now compile the code and upload it to Arduino, if any error is showing, check the error and resolve it, Also check the libraries.

3. After successful Uploading connect the 1st RFID Reader to Arduino and test if

Note :
1. Code is fully tested and everything is working great. if it's not working, it may be a loose connection, so must check the connection twice.

2. If you are using Breadboard, then must use a "good quality and new" breadboard and must use "good quality and new" jumper wires.
