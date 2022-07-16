import time
import board

from random import randint
from audiomp3 import MP3Decoder
from audiopwmio import PWMAudioOut as AudioOut
from adafruit_circuitplayground import cp

debug = 1
play_audio_threshold = 7  # 0 = vertical |
reset_audio_threshold = 9  # 9 = horizontal _
audio_is_playing = False

files = ["begins.mp3", "xfiles.mp3"]
filename = open(files[0], "rb")
decoder = MP3Decoder(filename)

audio = AudioOut(board.SPEAKER)

while True:
    if cp.switch:
        z = abs(cp.acceleration.z)
        if debug:
            print(z, audio_is_playing)
        if z > reset_audio_threshold and audio_is_playing:
            audio_is_playing = False
        elif z < play_audio_threshold and not audio_is_playing and not audio.playing:
            i = randint(0, len(files) - 1)
            filename = files[i]
            if debug:
                print("Playing",filename)
            decoder.file = open(filename, "rb")
            audio.play(decoder)
            audio_is_playing = True

    time.sleep(0.2)
