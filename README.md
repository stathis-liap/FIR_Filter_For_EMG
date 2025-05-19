# ⚡ FIR Band-Pass Filter for EMG Signal (Arduino Uno)

This project implements a **digital FIR band-pass filter** on an **Arduino Uno** to process and clean up **EMG (Electromyography) signals** in real time.

---

## 🎯 Objective

To filter the EMG signal and retain only the frequencies between **10–500 Hz**, removing:

- Low-frequency drift and motion artifacts (e.g., baseline or DC offset)
- High-frequency electronic and environmental noise

---

## ⚙️ Specifications

| Parameter              | Value                           |
|------------------------|---------------------------------|
| Filter Type            | FIR (Finite Impulse Response)   |
| Filter Band            | 10 Hz – 500 Hz                  |
| Sampling Rate          | 2000 Hz (every 500 µs)          |
| Number of Taps         | 21                              |
| ADC Resolution         | 10-bit (0–1023)                 |
| Voltage Range          | 0–5 V                           |
| Output Display         | Arduino Serial Plotter          |

---

## 🧠 How the Arduino Code Works

1. Reads the EMG signal from analog pin `A0` using `analogRead()`.
2. Converts the raw value to voltage (0–5V).
3. Maintains a **circular buffer** of the last 21 input values.
4. Applies **convolution** between the buffer and FIR filter coefficients.
5. Outputs the **filtered signal** to the Serial Plotter for visualization.

---

## ✅ Why FIR?

- **Simple to implement**: No feedback or recursion required.
- **Stable**: Always stable regardless of coefficient values.
- **Linear phase**: Preserves the shape of the EMG waveform.

---

## 🚀 Getting Started

### 🧰 Hardware

- Arduino Uno
- EMG sensor (e.g. MyoWare, Olimex EMG, etc.)
- USB cable

### 🧪 Software

- Arduino IDE
- Python (for filter coefficient generation)

---

## 🔌 How to Use It

1. Connect the EMG sensor output to analog pin `A0` on the Arduino Uno.
2. Upload `fir_filter_4th.ino` to the Arduino Uno.
3. Open **Tools > Serial Plotter** in the Arduino IDE.
4. Set **baud rate** to `115200`.
5. You’ll see the real-time **filtered EMG signal** plotted live.

---

## 🧮 FIR Coefficient Generator (Python)

The Python script `coeff_calculator.py` generates FIR filter coefficients in **C array format** that can be pasted into the Arduino sketch.

### 📦 Install dependencies

```bash
pip install scipy numpy
```

## 📁 File Structure

```
.
├── fir_filter_4th.ino         # Arduino sketch with FIR filter
├── coeff_calculator.py        # Python script to generate FIR coefficients
└── README.md                  # Project documentation
```

---

## 📝 License

This project is released under the [MIT License](LICENSE).

---
