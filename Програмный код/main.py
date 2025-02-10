import serial
import pandas as pd
from datetime import datetime
import time
ser = serial.Serial('/dev/ttyUSB0', 9600)
ser2 = serial.Serial('/dev/ttyACM1', 9600)


db_path = 'rfid_db.xlsx'

def load_database():
    return pd.read_excel(db_path)

def validate_uid(uid, db):
    current_date = datetime.now().date()

    for _, row in db.iterrows():
        if str(uid) == str(row['UID']):
            expiry_date = pd.to_datetime(row['Дата окончания']).date()
            if current_date <= expiry_date:
                # time.sleep(10)
                ser.write(b'1\n')
                ser2.write(b'1\n')
                # time.sleep(0.1)
                return f"Доступ разрешен: {row['ФИО']}"
            else:
                # time.sleep(10)
                ser.write(b'2\n')
                ser2.write(b'2\n')

                return f"Доступ запрещен: Срок действия истёк ({expiry_date})"
    ser.write(b'0\n')
    ser2.write(b'0\n')
    return "Доступ запрещен: UID не найден в базе данных"

def main():
    print("Ожидание данных от Arduino...")
    db = load_database()

    while True:
        uid = ser.readline().decode('utf-8').strip()
        print(f"UID получен: {uid}")
        result = validate_uid(uid, db)
        print(result)

main()