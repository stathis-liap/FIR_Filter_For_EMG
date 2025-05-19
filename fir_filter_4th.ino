// Φίλτρο FIR για σήμα EMG (σύγκριση raw vs filtered)
// Ρυθμός δειγματοληψίας: 2000 Hz (κάθε 500 μικροδευτερόλεπτα)

const int emgPin = A0;  // Αναλογική είσοδος για το σήμα EMG
const unsigned long samplingInterval = 500; // Χρονικό διάστημα δειγματοληψίας σε μs
unsigned long lastSampleTime = 0; // Χρόνος τελευταίου δείγματος

// Συντελεστές FIR φίλτρου (21 taps), για bandpass 10–500 Hz
#define FIR_TAPS 21
float firCoeffs[FIR_TAPS] = {
  -0.001355, -0.002158, -0.004208, -0.006394, -0.006723,
   0.000000,  0.013069,  0.030512,  0.047408,  0.058074,
   0.060000,  0.052174,  0.036436,  0.016245, -0.003849,
  -0.018165, -0.022822, -0.018056, -0.007929, -0.000570,
  -0.000057
};

// Πίνακας κυλιόμενου buffer για τα τελευταία δείγματα εισόδου
float firBuffer[FIR_TAPS] = {0};

// Συνάρτηση εφαρμογής του FIR φίλτρου
float applyFIR(float input) {
  // Μετακίνηση των παλιών τιμών προς τα δεξιά (από το πιο πρόσφατο στο παλαιότερο)
  for (int i = FIR_TAPS - 1; i > 0; i--) {
    firBuffer[i] = firBuffer[i - 1];
  }

  // Εισαγωγή του νέου δείγματος στην αρχή του buffer
  firBuffer[0] = input;

  // Υπολογισμός συνέλιξης: άθροισμα (συντελεστής * δείγμα)
  float result = 0;
  for (int i = 0; i < FIR_TAPS; i++) {
    result += firCoeffs[i] * firBuffer[i];
  }

  return result; // Επιστροφή της φιλτραρισμένης τιμής
}

void setup() {
  Serial.begin(115200);    // Εκκίνηση σειριακής επικοινωνίας για το Plotter
  pinMode(emgPin, INPUT);  // Ορισμός του pin A0 ως είσοδος
}

void loop() {
  // Έλεγχος αν έχει περάσει χρόνος δειγματοληψίας (500μs = 2kHz)
  if (micros() - lastSampleTime >= samplingInterval) {
    lastSampleTime = micros(); // Ενημέρωση χρονικού σήματος

    // Ανάγνωση ακατέργαστης τιμής από τον ADC (0–1023)
    int rawADC = analogRead(emgPin);

    // Μετατροπή σε τάση (0–5V)
    float rawVoltage = (rawADC / 1023.0) * 5.0;

    // Εφαρμογή FIR φίλτρου στο σήμα
    float filtered = applyFIR(rawVoltage);

    // Εκτύπωση αποτελεσμάτων στο Serial Plotter
    // Γραμμή 1: rawVoltage (ακατέργαστο)
    // Γραμμή 2: filtered (φιλτραρισμένο)
    Serial.print(rawVoltage);
    Serial.print("\t");        // Διαχωρισμός με tab
    Serial.println(filtered);
  }
}
