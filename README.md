# LASTEST Version
[Ver5.4.0](https://github.com/KomKGT/LTN_Comunication/tree/main/Beta5.4_240322) Can **Read** and **Decode** Data from Device01 Serialport ,UI same Mother's Software,Reset Data Button,Disconnect serialport button</br>
Version 5.4.0</br>
![image](https://user-images.githubusercontent.com/81642936/159852978-2c846459-4b7b-4842-ab2e-37121636e0f9.png)
Version 5.3.0</br>
![image](https://user-images.githubusercontent.com/81642936/159108686-7e32e4ea-2009-439d-ade5-f792d8753d3d.png)
Version 5.2.0</br>
![image](https://user-images.githubusercontent.com/81642936/156877571-2b4baec7-bd18-4337-a8d0-d705f0dbd7c0.png)
# LTN_Comunication
LABTECH
![image](https://user-images.githubusercontent.com/81642936/147807290-22ddc751-3def-4188-a68b-abbf2c88790c.png)
The left figure is MODBUS TCP SLAVE by Qt and The right figure is MODBUS TCP MASTER
</br>a in hexa = 10 in decimal</br>
b in hexa = 11 in decimal </br>
# รหัสที่ใช้
*A0 B0 C0 D0 E0200 F0500 G0230 H0 I0# </br>
A = P2 0-9999 	เพื่อเป็นทศนิยม/10 เสมอ    ติด - ได้ </br>
B = P1 0-9999  	เพื่อเป็นทศนิยม/10 เสมอ  	 ติด - ได้ </br>
C = T2 0-9999 	ไม่หาร  ไม่ติด - </br>
D = T1 0-9999	ไม่หาร  ไม่ติด - </br>
E = Gear pump Speed /10 เสมอ ไม่ติด - </br>
F = Gear pump inlet pressure /10 เสมอ ไม่ติด - </br>
G = Filter temp input ไม่หาร ไม่ติด - </br>
H = P2 (สำรองเฉยๆ) </br>
I = P1 (สำรองเฉยๆ) </br>
