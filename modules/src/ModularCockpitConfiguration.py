import serial
import serial.tools.list_ports
import time
import tkinter as tk
from tkinter import ttk

VID = 0x16C0
PIDS = [0x0483, 0x0487]

def find_all_teensies():
    devices = []
    ports = serial.tools.list_ports.comports()
    for port in ports:
        if port.vid == VID and port.pid in PIDS:
            devices.append(port.device)
    return devices

teensy_ports = find_all_teensies()
teensy_serials = []

for p in teensy_ports:
    try:
        ser = serial.Serial(p, 9600, timeout=1)
        time.sleep(2)
        teensy_serials.append(ser)
        print(f"Conectado a {p}")
    except Exception as e:
        print(f"No se pudo abrir {p}: {e}")

def set_brightness_all(value):
    val = int(float(value))  # invertir rango
    value_label.config(text=str(val))
    for ser in teensy_serials:
        ser.write(bytes([val]))  # enviar un único byte



root = tk.Tk()
root.title("Modular Cockpit: Configuration")

mainframe = ttk.Frame(root, padding="10")
mainframe.grid(row=0, column=0, sticky="nsew")

ttk.Label(mainframe, text="Backlight Brightness", font=("Arial", 14)).grid(row=0, column=0, columnspan=2, pady=10)

# primero la etiqueta
value_label = ttk.Label(mainframe, text="128", width=4)
value_label.grid(row=1, column=1, padx=5)

# luego el slider
slider = ttk.Scale(mainframe, from_=0, to=255, orient="horizontal",
                   command=set_brightness_all, length=300)  # ancho en píxeles

slider.set(128)
slider.grid(row=1, column=0, padx=10, pady=5, sticky="ew")

root.mainloop()

