# MSP packet generator for PID data (example payload with 3 PID sets)
header = b"$M<"

# Example: 3 PID sets (Roll, Pitch, Yaw), each with P, I, D (values 1-9)
payload = bytes([1, 2, 3, 4, 5, 6, 7, 8, 9])

size = len(payload)
command = 105  # MSP_PID (for example)
checksum = 0

for b in bytes([size, command]) + payload:
    checksum ^= b

packet = header + bytes([size, command]) + payload + bytes([checksum])

with open("./test/resources/mock_msp.bin", "wb") as f:
    f.write(packet)

print(f"Generated MSP packet with command={command}, size={size}, checksum={checksum}")
