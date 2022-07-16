import time
from random import randint
from adafruit_circuitplayground import cp

debug = 0
play_audio_threshold = 7  # 0 = vertical |
reset_audio_threshold = 9  # 9 = horizontal _
audio_is_playing = False
files = ["Sound_C.wav", "Sound_G.wav"]

while True:
    if cp.switch:
        z = abs(cp.acceleration.z)
        if debug:
            print(z, audio_is_playing)
        if z > reset_audio_threshold and audio_is_playing:
            audio_is_playing = False
        elif z < play_audio_threshold and not audio_is_playing:
            i = randint(0, len(files) - 1)
            cp.play_file(files[i])
            audio_is_playing = True
    time.sleep(0.1)
