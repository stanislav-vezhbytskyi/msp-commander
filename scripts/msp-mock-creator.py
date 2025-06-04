# MSP packet generator for PID, STATUS, and RAW_IMU data
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

# RAW_IMU packet (command 102)
# accX = 256, accY = -256, accZ = 512
# gyroX = 128, gyroY = -128, gyroZ = 64
# magX = 10, magY = 20, magZ = 30

def to_bytes_16(val: int) -> bytes:
    return val.to_bytes(2, byteorder='little', signed=True)

raw_imu_payload = (
        to_bytes_16(256) + to_bytes_16(-256) + to_bytes_16(512) +
        to_bytes_16(128) + to_bytes_16(-128) + to_bytes_16(64) +
        to_bytes_16(10) + to_bytes_16(20) + to_bytes_16(30)
)
raw_imu_packet = generate_packet(102, raw_imu_payload)
with open("./test/resources/mock_msp_raw_imu.bin", "wb") as f:
    f.write(raw_imu_packet)

print("Generated PID, STATUS, and RAW_IMU MSP packets.")
