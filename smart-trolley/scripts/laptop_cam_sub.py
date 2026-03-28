import zenoh
import cv2
import numpy as np

# Change this to your Pi's IP
PI_IP = "192.168.120.121" 

conf = zenoh.Config()
conf.insert_json5("connect/endpoints", f'["tcp/{PI_IP}:7447"]')
session = zenoh.open(conf)

def on_video(sample):
    data = np.frombuffer(sample.payload.to_bytes(), dtype=np.uint8)
    frame = cv2.imdecode(data, cv2.IMREAD_COLOR)
    if frame is not None:
        cv2.imshow('Robot Remote View', frame)
        cv2.waitKey(1)

def on_status(sample):
    print(f"[PI DATA]: {sample.payload.to_string()}")

session.declare_subscriber("pi/camera", on_video)
session.declare_subscriber("pi/status", on_status)

print("Monitoring Robot... Press Ctrl+C to stop.")
try:
    while True: pass
except KeyboardInterrupt:
    cv2.destroyAllWindows()
    session.close()
