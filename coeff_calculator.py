from scipy.signal import firwin

# Ρυθμίσεις φίλτρου
fs = 2000               # Ρυθμός δειγματοληψίας σε Hz
num_taps = 21           # Πλήθος συντελεστών (πρέπει να είναι περιττός αριθμός)
cutoff = [10, 500]      # Εύρος συχνοτήτων ζώνης διέλευσης σε Hz

# Δημιουργία των συντελεστών
coeffs = firwin(num_taps, cutoff, fs=fs, pass_zero=False)

# Εκτύπωση σε μορφή πίνακα για Arduino
print(f"float firCoeffs[{num_taps}] = {{")
for i, c in enumerate(coeffs):
    end_char = "," if i < num_taps - 1 else ""
    print(f"  {c:.6f}{end_char}")
print("};")

