import serial
import comtypes
from pycaw.pycaw import AudioUtilities, ISimpleAudioVolume

ser = serial.Serial("COM3", 115200)

apps = {
    0: "spotify.exe",
    1: "discord.exe",
    2: "opera.exe"
}

def set_volume(process_name, level):
    
    sessions = AudioUtilities.GetAllSessions()
    for session in sessions:
        if session.Process and process_name.lower() in session.Process.name().lower():
            volume = session._ctl.QueryInterface(ISimpleAudioVolume)
            volume.SetMasterVolume(level, None)

comtypes.CoInitialize()
while True:
    line = ser.readline().decode().strip()
     
    if ":" not in line:
        continue
    
    if ":" in line:
        parts = line.split(":")

    if len(parts) >= 2:
        idx = int(parts[0])
        if parts[1] == "mute":
            vol = 0
        elif parts[1] == "unmute":
            vol = 1 #TODO turn it to the vol before mute
        else:
            val = int(parts[1])
            if val < 0:
                val = 0
            elif val > 100:
                val = 100
            vol = val / 100

        if idx in apps:
            print(apps[idx], vol)
            set_volume(apps[idx], vol)