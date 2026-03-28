import zenoh
import time
import random

# 1. Create default config
conf = zenoh.Config()

# 2. Open session with config
session = zenoh.open(conf)

key = 'demo/pi5/sensor'
pub = session.declare_publisher(key)

print(f"Sending data on {key}... Press Ctrl+C to stop.")

try:
    while True:
        temp = 40 + random.random() * 10
        print(f"Putting Data: {temp:.2f}")
        # In Zenoh 1.0+, put takes the payload directly
        pub.put(f"{temp:.2f}")
        time.sleep(1)
except KeyboardInterrupt:
    session.close()
