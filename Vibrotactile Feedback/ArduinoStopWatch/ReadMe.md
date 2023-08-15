# How to Run the StopWatch
This stopwatch is triggered at set intervals and stopped using a footpedal button. 

## Exporting Aduino Serial Output: PuTTY
PuTTY is a terminal emulator which we can use to export and save the stopwatch times from participants. It requires specific config and operating order to use. 

### Config
1. Launch PuTTY
2. On the **Session Tab**: Set **Serial Line** to the COM you are using for the Arduino (IDE will show this). Set **Connection Type** to Serial. Check the speed matches the one in arduino void setup.
3. On the **Logging Tab**: Select **Printable output**, for **Log file name**, click browse and pick a CSV file. Below, select **Always append to the end of it**.
4. On the **Serial Tab**: Check that the Serial line and Speed match those on the Session tab. 
5. Return to the **Session Tab**: Under **Saved Sessions**, name your session and click save. 
6. Whenever you next launch PuTTY, select your saved session and click **Load** to restore this config.

### Operating Order
1. Run the arduino RunCondition.ino file, PuTTY, the csv file and the serial monitor must be closed. 
2. Run PuTTY, load your saved session, click open. 
3. The black terminal screen will appear, wait for the first line to appear indicating void setup has complete.
4. You can now proceed with the trial. 
5. to begin a new trial, press the reset button on the arduino board, again wait for the first line to appear to indicate the setup is finished.
6. Once finished, the times should all have printed to the terminal. After this you can close the terminal and the session, those times will be logged to the csv. 
7. For each participant, begin a new putty session.
