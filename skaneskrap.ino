#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>

#define BREAKOUT_RESET  9
#define BREAKOUT_CS     10
#define BREAKOUT_DCS    8

#define SHIELD_RESET    -1
#define SHIELD_CS       7
#define SHIELD_DCS      6

#define CARDCS          4
#define DREQ            3

#define SENSOR_PIN      A0 // 0,1,2,5,8,9,10,A0,A1,A2,A3,A4,A5
#define NUM_FILES       6

Adafruit_VS1053_FilePlayer musicPlayer = Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

bool prev;
bool trackPlaying = false;
String files[NUM_FILES] = {"/track001.mp3","/track002.mp3","/track003.mp3","/track004.mp3","/track005.mp3","/track006.mp3"};

void setup() {
  Serial.begin(9600);
  Serial.println("Adafruit VS1053 Simple Test");

  pinMode(SENSOR_PIN, INPUT_PULLUP);

  if (! musicPlayer.begin()) {
    Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
    while (1);
  }

  Serial.println(F("VS1053 found"));

  if (!SD.begin(CARDCS)) {
    Serial.println(F("SD failed, or not present"));
    while (1);
  }

  musicPlayer.setVolume(10, 10);
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);
}

void loop() {

  bool lidOpen = digitalRead(SENSOR_PIN);
  bool lidClosed = !lidOpen;

  if (lidOpen != prev) {
    if (lidOpen) Serial.println("Lid open…");
    if (lidClosed) Serial.println("Lid closed……");
  }

  if (lidClosed) {
    if (trackPlaying) {
      //musicPlayer.stopPlaying();
      trackPlaying = false;
      Serial.println("Stop playing.");
    }
  } else {
    if (!trackPlaying) {
      trackPlaying = true;
      Serial.println("Start playing.");
      int i = random(0, NUM_FILES - 1);
      const char * file = files[i].c_str();
      musicPlayer.startPlayingFile(file);
    }
  }

  prev = lidOpen;

  delay(100);


}
