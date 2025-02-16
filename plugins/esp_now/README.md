# ESP-NOW

ปลั๊กอิน ESP-NOW รับ-ส่งข้อมูลระหว่างบอร์ด KidBright สำหรับโปรแกรม KidBrightIDE และ KBIDE (แพลตฟอร์ม ESP-IDF) นำไปประยุกต์ทำโครงงานได้หลากหลาย เช่น ทำรีโมทรถบังคับ และรถบังคับด้วยบอร์ด KidBright

## การติดตั้ง

แนะนำให้ใช้โปรแกรม KidBrightIDE เวอร์ชั่นล่าสุด (New UI, Plugins beta version) มีขั้นตอนการติดตั้งดังนี้

 1. ดาวน์โหลดไฟล์ปลั๊กอิน `esp-now-plugin-v1.1.zip` ได้ที่ด้านล่างของหน้านี้
 2. เปิดโปรแกรม KidBrightIDE กด `Plugins > Install Plugins`
 3. เลือกไฟล์ปลั๊กอินที่ดาวน์โหลดไว้
 4. โปรแกรม KidBrightIDE จะปิดแล้วเปิดใหม่ บล็อกใหม่จะอยู่ในเมนู `เซ็นเซอร์วัดฝุ่น KidPM25` หรือ `KidPM25`
 
กรณีใช้โปรแกรม KBIDE ให้เลือกใช้แพลตฟอร์ม ESP-IDF แล้วติดตั้งได้จาก Plugin Manager (ค้นหา ESP-NOW)

## บล็อกที่มีให้ใช้งาน

| บล็อกภาษาไทย | บล็อกภาษาอังกฤษ |
|--|--|
| ![ปลั๊กอิน ESP-NOW](https://sv1.picz.in.th/images/2019/08/19/ZwJN0I.png) | ![ESP-NOW Plugin for KidBrightIDE](https://sv1.picz.in.th/images/2019/08/19/ZwJz8Z.png) |

### บล็อกอ่านค่า MAC Address

ใช้อ่านค่า MAC Address ของตัวเอง เพื่อใช้เป็นข้อมูลให้บอร์ดอื่นส่งข้อมมูลมาหาได้

### บล็อกส่งข้อมูล

ใช้ส่งข้อความ ตัวเลข ไปยังบอร์ด KidBrightIDE ตัวอื่น (Broadcast)

### บล็อกส่งข้อมูลไปยัง...

ใช้ส่งข้อความ ตัวเลข ไปยังบอร์ด KidBrightIDE เฉพาะตัวที่กำหนด (Unicast) โดยใช้ MAC Address

### บล็อกเมื่อได้รับข้อมูล

ใช้ใส่บล็อกที่จะให้ทำงานเมื่อบอร์ด KidBright ได้รับข้อมูลจากบอร์ดอื่น

### บล็อกอ่านข้อความ

ใช้อ่านข้อความที่ส่งมาจากบอร์ด KidBright บอร์ดอื่น ใช้กับบล็อกแอลอีดี 16x8 แบบเลื่อนเมื่อพร้อม

### บล็อกอ่านตัวเลข

ใช้อ่านตัวเลขที่ส่งมาจากบอร์ด KidBright บอร์ดอื่น กรณีข้อมูลที่รับมาจากบอร์ดอื่นไม่ใช่ตัวเลข จะให้ค่าเป็น 0

## ตัวอย่างโปรแกรม 1

ใช้บอร์ด KidBright ตัวที่ 1 ส่งค่าแสงที่วัดได้ ไปแสดงผลที่ KidBright ตัวที่สอง

### ฝั่งส่ง

| บล็อกภาษาไทย | บล็อกภาษาอังกฤษ |
|--|--|
| ![Z9I91n.png](https://sv1.picz.in.th/images/2019/08/17/Z9I91n.png) | ![Z9I3WS.png](https://sv1.picz.in.th/images/2019/08/17/Z9I3WS.png) |

### ฝั่งรับ

| บล็อกภาษาไทย | บล็อกภาษาอังกฤษ |
|--|--|
| ![Z9Iuee.png](https://sv1.picz.in.th/images/2019/08/17/Z9Iuee.png) | ![Z9In3l.png](https://sv1.picz.in.th/images/2019/08/17/Z9In3l.png) |

## ตัวอย่างโปรแกรม 2

ใช้บอร์ด KidBright ตัวที่ 1 ส่งตัวเลขไปบอร์ด KidBright ตัวที่ 2 และตัวที่ 3 (แต่ละตัว ได้รับข้อมูลไม่เหมือนกัน)

### ฝั่งส่ง

| บล็อกภาษาไทย | บล็อกภาษาอังกฤษ |
|--|--|
| ![ZKQ9uq.png](https://sv1.picz.in.th/images/2019/08/19/ZKQ9uq.png) | ![ZKQTMz.png](https://sv1.picz.in.th/images/2019/08/19/ZKQTMz.png) |

หมายเหตุ: ต้องใช้ปลั๊กอิน theIO เพิ่มเติม

### ฝั่งรับ

| บล็อกภาษาไทย | บล็อกภาษาอังกฤษ |
|--|--|
| ![ZKQww8.png](https://sv1.picz.in.th/images/2019/08/19/ZKQww8.png) | ![ZKQ1DR.png](https://sv1.picz.in.th/images/2019/08/19/ZKQ1DR.png) |

## การแก้ปัญหาใช้งานไม่ได้

### ปัญหาบอร์ดรีเซ็ตตลอดเวลา (ติด WDT reset)

ให้ทดสอบอัพโหลดโปรแกรมตามรูปด้านล่างนี้

| บล็อกภาษาไทย | บล็อกภาษาอังกฤษ |
|--|--|
| ![ZTWzSN.png](https://sv1.picz.in.th/images/2019/08/17/ZTWzSN.png) | ![ZTWSHE.png](https://sv1.picz.in.th/images/2019/08/17/ZTWSHE.png) |

หากไม่ขึ้น AA ที่จอแอลอีดี 16x8 แสดงว่าบอร์ดอาจได้รับความเสียหายจากการอัพโหลดโปรแกรมหลายรอบ ทำให้พื้นที่เก็บข้อมูลบางส่วนของ ESP32 เสียหาย แก้ไขได้โดยทำตามขั้นตอนดังนี้

 1. ดาวน์โหลดโปรแกรม Flash Download Tools จาก https://www.espressif.com/sites/default/files/tools/flash_download_tools_v3.6.6_0.zip
 2. คลายไฟล์ zip ออกมา แล้วเข้าไปในโฟลเดอร์ที่คลายไฟล์มา ดับเบิลคลิกเปิดไฟล์ `flash_download_tools_v3.6.5.exe`
 3. กดปุ่ม ESP32 DownloadTool จะมีหน้าต่างโปรแกรมใหม่เปิดขึ้นมา
 4. ในหน้าต่างใหม่ ส่วนล่างของหน้าต่าง ให้กดเลือก COM: ให้ถูกต้อง (หากต่อบอร์ด KidBright ไว้บอร์ดเดียว จะขึ้นให้เลือกอันเดียว)
 5. กดปุ่ม ERASE แล้วรอจนกว่าจะขึ้น FINISH
 6. ทดสอบอัพโหลดโค้ดโปรแกรมลงไปใหม่อีกครั้ง
 
 ### ปัญหาส่งข้อมูลได้ครั้งเดียว
 
 เกิดจากเปิดใช้งานไอโอทีไว้ ให้ปิดใช้งาน และลบข้อมูลช่อง SSID และ Password ออก (ในหน้าต่าง ตั้งค่า WIFI)
 
 ![การปิดใช้งานไอโอที](https://sv1.picz.in.th/images/2019/08/17/Z9FgIt.png)
 
 
