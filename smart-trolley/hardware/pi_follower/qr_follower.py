import cv2
import serial
import time
from gpiozero import LED

TARGET_QR = "target_person_1"

ser = serial.Serial('/dev/ttyUSB0', 115200)
time.sleep(2)

led = LED(17)

cap = cv2.VideoCapture(0)
cap.set(3, 640)
cap.set(4, 480)

qr_detector = cv2.QRCodeDetector()

prev_cx = None
MOVE_THRESHOLD = 40
TOLERANCE = 80
AREA_THRESHOLD = 10000
AREA_MARGIN = 1500

last_sent = 0

while True:
    ret, frame = cap.read()
    if not ret:
        continue

    height, width, _ = frame.shape
    FRAME_CENTER_X = width
    FRAME_CENTER_Y = height 

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    data, points, _ = qr_detector.detectAndDecode(gray)

    if data:
        print("Detected:", data)

    if points is not None and data == TARGET_QR:
        led.on()   # LED ON when QR detected

        pts = points.astype(int).reshape(4, 2)

        cx = int(pts[:,0].mean())
        cy = int(pts[:,1].mean())

        print(f"Target at: ({cx}, {cy})")

        for i in range(4):
            cv2.line(frame, tuple(pts[i]), tuple(pts[(i+1)%4]), (0,255,0), 2)

        w = abs(pts[0][0] - pts[1][0])
        h = abs(pts[0][1] - pts[2][1])
        area = w * h

        if prev_cx is None:
            prev_cx = cx

        movement = abs(cx - prev_cx)

        if movement < MOVE_THRESHOLD:
            print("IGNORING SMALL MOVEMENT")
            cmd = 'S'
        else:
       
            if area > AREA_THRESHOLD + AREA_MARGIN:
                print("STOP - TOO CLOSE")
                cmd = 'S'
            elif area < AREA_THRESHOLD - AREA_MARGIN:
             
                if cx < FRAME_CENTER_X - TOLERANCE:
                    print("LEFT")
                    cmd = 'L'
                elif cx > FRAME_CENTER_X + TOLERANCE:
                    print("RIGHT")
                    cmd = 'R'
                else:
                    print("FORWARD")
                    cmd = 'F'
            else:
                print("HOLD POSITION")
                cmd = 'S'

        prev_cx = cx

        if time.time() - last_sent > 0.2:
            ser.write(cmd.encode())
            last_sent = time.time()

    else:
        led.off()   # LED OFF when no QR
        ser.write(b'S')

    cv2.imshow("QR Tracker", frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
led.off()
ser.write(b'S')
