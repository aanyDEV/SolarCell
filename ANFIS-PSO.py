import tkinter as tk
import ttkbootstrap as ttk
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from tkinter import IntVar
import serial as sr
import numpy as np
from datetime import datetime
from termcolor import colored
import re
import time
import serial.tools.list_ports

inputSensorIN = []
porttt = 9600

def detekAktifPort():
    actPort = [] #portAktif
    for port in serial.tools.list_ports.comports():
        try:
            ser = serial.Serial(port.device, porttt, timeout=1)
            data = ser.read(10)
            ser.close()
            if data:
                actPort.append(port.device)
        except serial.SerialException:
            pass
        
    return actPort

class ANFIS:
    def __init__(self):
        # Inisialisasi atribut
        self.input_layer = np.zeros(2)
        self.membership_layer = np.zeros(2)

    def triangular_mf(self, x, a, b, c):
        return max(0, min((x - a) / (b - a), (c - x) / (c - b)))

    def evaluate_membership_functions(self, x):
        self.membership_layer[0] = self.triangular_mf(x[0], 10, 12, 14)  # Fungsi keanggotaan triangular untuk Voltage
        self.membership_layer[1] = self.triangular_mf(x[1], 8, 12, 16)   # Fungsi keanggotaan triangular untuk Current

    def forward_pass(self, x):
        self.input_layer = x
        self.evaluate_membership_functions(x)

    def defuzzify(self):
        weighted_sum = sum(self.input_layer[i] * self.membership_layer[i] for i in range(2))
        total_weight = sum(self.membership_layer)
        if total_weight !=0:
            return weighted_sum / total_weight
        else:
            return 0

    def evaluate_fitness(self, position, voltage, current):
        # Proses hasil ANFIS menggunakan forward_pass
        self.forward_pass(position)
        # Hitung nilai fitness, misalnya dengan menggunakan selisih dengan target
        target = target_function(voltage, current)  # Definisikan target_function sesuai kebutuhan
        fitness = abs(target - self.defuzzify())  # Misalnya, kita gunakan selisih absolut
        return fitness

    def modeConverter(self, voltage):
        if voltage > 12.00:
            return "Buck"
        elif voltage < 12.00:
            return "Boost"
        elif voltage == 12.00:
            return "Normal"
        else:
            return None

class Particle:
    def __init__(self, position_dim):
        self.position = np.random.rand(position_dim)  # Inisialisasi posisi secara acak
        self.velocity = np.random.rand(position_dim)  # Inisialisasi kecepatan secara acak
        self.pBest = np.copy(self.position)  # Posisi terbaik pribadi
        self.fitness = 0

    def update_velocity(self, gBest, max_velocity, acceleration_factor):
        r1 = np.random.rand(len(self.velocity))
        r2 = np.random.rand(len(self.velocity)) 
        cognitive_component = acceleration_factor * r1 * (self.pBest - self.position)
        social_component = acceleration_factor * r2 * (gBest - self.position)
        self.velocity = self.velocity + cognitive_component + social_component

        # Batasi kecepatan maksimum
        self.velocity = np.clip(self.velocity, -max_velocity, max_velocity)
    
    def update_position(self):
        self.position = self.position + self.velocity

def pso_anfis(num_particles, num_iterations, max_velocity, acceleration_factor, voltage, current):
    try:
        anfis = ANFIS()
        position_dim = 2

        particles = [Particle(position_dim) for _ in range(num_particles)]
        gBest = np.copy(particles[0].position)

        for _ in range(num_iterations):
            for particle in particles:
                fitness = anfis.evaluate_fitness(particle.position, voltage, current)
                if fitness < anfis.evaluate_fitness(particle.pBest, voltage, current):
                    particle.pBest = np.copy(particle.position)
                    particle.fitness = fitness

                if fitness < anfis.evaluate_fitness(gBest, voltage, current):
                    gBest = np.copy(particle.position)

                particle.update_velocity(gBest, max_velocity, acceleration_factor)
                particle.update_position()

        return gBest
    except RuntimeWarning:
        result = 0

# Fungsi target_function adalah fungsi yang akan dioptimasi. Implementasikan sesuai kebutuhan.
def target_function(voltage, current):

    return voltage + current

try:
    portAktif = detekAktifPort()
    
    for portmurup in portAktif:
        global ser
        ser = sr.Serial(portmurup, porttt, timeout=1)
        app = tk.Tk()
        app.title("Aplikasi MPPT Solar Cell - ANFIS PSO")
        app.geometry("1250x750")

        frame = ttk.Frame(app)
        frame.grid(row=0, column=0, padx=20, pady=20)

        voltNow = IntVar()
        currentNow = IntVar()
        current2Now = IntVar()

        def closeApp():
            app.quit()
            app.destroy()

        def update_plot(ax, canvas, data):
            waktu1 = datetime.now()
            labelMode = tk.Label(frame, text="", font=("Helvetica", 25))
            labelMode.grid(row=1, column=0, columnspan=2, padx=50, pady=0)
            ser.close()
            ser.open()
            dataDiterima = ser.readline().decode("utf-8").strip()
            inputSensorIN = str(dataDiterima). split("=")

            inputVolt = float(inputSensorIN[0])
            inputCurr = float(inputSensorIN[1])
            print(colored(f"Dari Sensor STM: {inputVolt}, {inputCurr}","yellow"))
            
            anfis = ANFIS()
            titikoptimum = pso_anfis(num_particles=10, num_iterations=100, max_velocity=0.1, acceleration_factor=2.0, voltage=inputVolt, current=inputCurr)
            mode = anfis.modeConverter(inputVolt)
            optimumoutput = sum(titikoptimum) / len(titikoptimum)
            DigDCOpt = 255 * float(optimumoutput)
            keSTM = f"{mode}={DigDCOpt}"
            print(colored(f"Kirim mode ke STM: {mode}, {DigDCOpt}","yellow"))
            ser.close()
            ser.open()
            ser.write(keSTM.encode())
            ser.close() 
            time.sleep(0.3)
            ser.open()
            menunggu = ser.readline().decode('utf-8').strip()
            if menunggu:
                dariSTM = re.split(r'=', menunggu)
                outputMode = dariSTM[0]
                outputVolt = dariSTM[1]
                outputCurr = dariSTM[2]
                print(colored(f"Hasil dari STM32: {outputMode}, {outputVolt}, {outputCurr}", "yellow"))
                voltNow.set(outputVolt)
                currentNow.set(inputCurr)
                current2Now.set(outputCurr)

                volt.configure(amountused=float(voltNow.get()))
                current.configure(amountused=float(currentNow.get()))
                current2.configure(amountused=float(current2Now.get()))
                labelMode = tk.Label(frame, text=str(outputMode), font=("Helvetica", 25))
                labelMode.grid(row=1, column=0, columnspan=3, padx=25, pady=0)
                data = np.append(data, inputVolt) #perbaharui plot
                ax.cla()
                ax.plot(data, label=str(inputVolt))
                ax.set_xlabel("Data Voltage")
                ax.set_ylabel("Voltage Input")
                canvas.draw()
                app.after(1000, update_plot, ax, canvas, data)
                waktu2 = datetime.now()
                selisih = waktu2 - waktu1
                print(colored(f"Pengerjaan: {selisih}\n", "green"))

        def create_plot(frame):
            volt.configure(amountused=float(voltNow.get()))
            current.configure(amountused=float(currentNow.get()))
            plt.subplots_adjust(left=1, right=3)
            fig, ax = plt.subplots(figsize=(12, 2.5))
            data = np.array([])
            canvas = FigureCanvasTkAgg(fig, master=frame)
            canvas_widget = canvas.get_tk_widget()
            canvas_widget.grid(row=2, column=0, columnspan=3)
            update_plot(ax, canvas, data)
            ax.set_xlabel("Data Voltage")
            ax.set_ylabel("Voltage Input")

        waktu1 = datetime.now()
        print("")
        ser.close()
        ser.open()
        dataDiterima = ser.readline().decode('utf-8').strip()
        inputSensorIN = str(dataDiterima).split("=")
        print(inputSensorIN)
        inputVolt = float(inputSensorIN[0])
        inputCurr = float(inputSensorIN[1])
        print(colored(f"Dari Sensor STM: {inputVolt}, {inputCurr}","yellow"))
        anfis = ANFIS()
        titikoptimum = pso_anfis(num_particles=10, num_iterations=100, max_velocity=0.1, acceleration_factor=2.0, voltage=inputVolt, current=inputCurr)
        mode = anfis.modeConverter(inputVolt)
        optimumoutput = sum(titikoptimum) / len(titikoptimum)
        DigDCOpt = 255 * float(optimumoutput)
        keSTM = f"{mode}={DigDCOpt}"
        print(colored(f"Kirim mode ke STM: {mode}, {DigDCOpt}","yellow"))
        ser.close()
        ser.open()
        ser.write(keSTM.encode())
        ser.close()
        time.sleep(0.3)
        ser.open()
        menunggu = ser.readline().decode('utf-8').strip()
        if menunggu:
            print(f"hasil print {menunggu}")
            dariSTM = re.split(r'=', menunggu)
            print(len(dariSTM))
            print(dariSTM)
            outputMode = dariSTM[0]
            outputVolt = dariSTM[1]
            outputCurr = dariSTM[2]
            print(colored(f"Hasil dari STM32: {outputMode}, {outputVolt}, {outputCurr}", "yellow"))
            voltNow.set(outputVolt)         
            currentNow.set(inputCurr)
            current2Now.set(outputCurr)
            
            volt = ttk.Meter(
                frame,
                meterthickness=75,
                metersize=300,
                padding=1,
                amountused=1,
                amounttotal=50,
                metertype="semi",
                subtext="miles per hour",
                subtextfont="-size 11",
                subtextstyle= "dark",
                stripethickness=5,
            )
            volt.grid(row=0, column=0, ipadx=0, ipady=0, padx=0, pady=35)

            current = ttk.Meter(
                frame,
                meterthickness=75,
                metersize=300,
                padding=1,
                amountused=1,
                amounttotal=30,
                metertype="semi",
                subtext="miles per hour",
                subtextfont="-size 11",
                subtextstyle= "dark",
                stripethickness=10,
            )
            current.grid(row=0, column=1, ipadx=0, ipady=0, padx=0, pady=35)
            
            current2 = ttk.Meter(
                frame,
                meterthickness=75,
                metersize=300,
                padding=1,
                amountused=1,
                amounttotal=50,
                metertype="semi",
                subtext="miles per hour",
                subtextfont="-size 11",
                subtextstyle= "dark",
                stripethickness=10,
            )
            current2.grid(row=0, column=2, ipadx=0, ipady=0, padx=0, pady=35)
            
            volt.configure(amountused=float(voltNow.get()))
            current.configure(amountused=float(currentNow.get()))
            current2.configure(amountused=float(current2Now.get()))

            volt.step(0)
            current.step(0)
            current2.step(0)
            volt.configure(subtext="Voltage Output")
            current.configure(subtext="Current Input")            
            current2.configure(subtext="Current Output")
            labelMode = tk.Label(frame, text=str(outputMode), font=("Helvetica", 25))
            labelMode.grid(row=1, column=0, columnspan=3, padx=25, pady=0)
            waktu2 = datetime.now()
            selisih = waktu2 - waktu1
            print(colored(f"Pengerjaan: {selisih}\n", "green"))
            create_plot(frame)
            app.protocol("WM_DELETE_WINDOW", closeApp)
            app.mainloop()
    ser.close()
except KeyboardInterrupt:
    ser.close()
    print("Program Auto Close")