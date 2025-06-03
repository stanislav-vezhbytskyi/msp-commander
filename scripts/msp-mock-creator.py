# MSP packet generator for PID data and STATUS data
def generate_packet(command: int, payload: bytes) -> bytes:
    header = b"$M<"
    size = len(payload)
    checksum = 0
    for b in bytes([size, command]) + payload:
        checksum ^= b
    return header + bytes([size, command]) + payload + bytes([checksum])

# PID packet (command 105)
pid_payload = bytes([1, 2, 3, 4, 5, 6, 7, 8, 9])  # 3 PID sets
pid_packet = generate_packet(105, pid_payload)

with open("./test/resources/mock_msp_pid.bin", "wb") as f:
    f.write(pid_packet)

# STATUS packet (command 101)
# Example values:
# cycleTime = 1000 -> 0x03E8 -> low byte: 0xE8, high byte: 0x03
# i2c_errors_count = 5 -> 0x0005
# sensor = BARO + GPS = (1<<1) | (1<<3) = 0x0A
# flag = 0x00000001 (BOXARM active)
# currentSet = 2

status_payload = bytes([
    0xE8, 0x03,      # cycleTime = 1000
    0x05, 0x00,      # i2c_errors_count = 5
    0x0A, 0x00,      # sensor = BARO + GPS
    0x01, 0x00, 0x00, 0x00,  # flag = 1
    0x02             # currentSet = 2
])
status_packet = generate_packet(101, status_payload)

with open("./test/resources/mock_msp_status.bin", "wb") as f:
    f.write(status_packet)

print("Generated PID and STATUS MSP packets.")
