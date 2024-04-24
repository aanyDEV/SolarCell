# MPPT-SolarCell Metode-ANFIS-PSO
Project MPPT Solarcell dengan metode ANFIS-PSO untuk otomatisasi PWM Sepic Converter

![image](https://github.com/Tektek9/MPPT-SolarCell-ANFIS-PSO/blob/main/mppt.png)

Perangkat yang dipakai:
- Mikrokontroler STM32F103
- Driver Mosfet (Untuk menerima nilai PWM dari STM32F103 dan dikirim ke SEPIC Converter)
- Sepic Converter (Untuk menerima Volt yang didapatkan dari tegangan Source, yang nantinya akan memproses tegangan dan ampere outputan sesuai dengan nilai PWM yang diinputkan ke SEPIC)

Bahasa pemrograman yang digunakan:
- Python (Untuk GUI)
- C++ (Untuk Mikrokontroller)

GUI untuk Desktop:
- Python (Bahasa Pemrograman)
- Thinker (Untuk frame GUI)
- TTKBootstrap (Untuk menampilkan Meter dari tegangan inputan, tegangan outputan, ampere inputan, ampere outputan)
- Matplotlib (Untuk menampilkan Plotter)

Komunikasi:
- Python (Bahasa Pemrograman)
- Serial (Komunikasi data yang digunakan antara GUI dengan Mikrokontroler)

Metode:
- ANFIS-PSO untuk menghasilkan titik daya optimum dan nilai diconvert menjadi Digital, yang nantinya dikirim ke Mikrokontroller dan diproses lagi
- ANFIS-PSO menggunakan Bahasa pemrograman Python
