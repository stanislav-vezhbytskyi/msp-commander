# example simple MSP packet (command = 105, payload = [1,2,3])

header = b"$M<"
payload = bytes(list(range(1, 101)))
size = len(payload)
command = 105
checksum = 0
for b in bytes([size, command]) + payload:
    checksum ^= b
packet = header + bytes([size, command]) + payload + bytes([checksum])

with open("test/resources/mock_msp.bin", "wb") as f:
    f.write(packet)
