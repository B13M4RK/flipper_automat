import serial
from tkinter import *
import customtkinter

ser = serial.Serial(
  port='COM4',
  baudrate=9600,
  timeout=0,
  )

root = customtkinter.CTk()
root.geometry('600x350')

label_A6 = customtkinter.CTkLabel(root,
  text="waiting for data...")
label_A6.pack()

def readData():
  data = ser.readline().decode('utf-8').rstrip()
  if data:
    label_A6.configure(text=f"A6: {data}")
  root.after(10, readData)
  
  
  
root.after(10, readData)
root.mainloop()