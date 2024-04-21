//instantiates GPS and speaker
//GPS
SoftwareSerial mySerial(3, 2); //TX, RX
Adafruit_GPS GPS(&mySerial);

//Speaker
SoftwareSerial mySoftwareSerial(10, 11); //RX, TX
DFRobotDFPlayerMini speaker;

void setup() {
  //gps
Serial.begin(9600);
GPS.begin(9600);

GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
delay(1000);

//speaker
mySoftwareSerial.begin(9600);
  Serial.begin(115200);

  if (!speaker.begin(mySoftwareSerial)) {
    Serial.println(F("DFPlayer Mini not found."));
    while (true);
  }

  speaker.volume(1);  // Set volume level (0~30).
  speaker.playMp3Folder(1); // Play the audio file "TestAudio.mp3" in the root directory.
}
