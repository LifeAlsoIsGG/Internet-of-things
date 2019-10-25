
#include <RFID.h>
#include <SPI.h>
#include <Servo.h>

String RC;
RFID rfid(10,5);
unsigned char RC_size;
unsigned char blockAddr;        //ѡ������Ŀ��ַ0��63
unsigned char i,tmp;
unsigned char status;
unsigned char str[MAX_LEN];
Servo servo_A1;
char * card[]={"f08ca4a3c","30cfb4384"};

String RFID_readcardnum() {

 rfid.readCardSerial();
  String stringserNum=String(rfid.serNum[0], HEX)+String(rfid.serNum[1], HEX)+String(rfid.serNum[2], HEX)+String(rfid.serNum[3], HEX)+String(rfid.serNum[4], HEX);
      //ѡ�������ؿ�������������Ƭ����ֹ��ζ�д��
      rfid.selectTag(rfid.serNum);
  return stringserNum;
}

//4�ֽڿ����кţ���5�ֽ�ΪУ���ֽ�
//������A���룬16��������ÿ����������6Byte
unsigned char sectorNewKeyA[16][16] = {
 {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
 {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xff,0x07,0x80,0x69, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
 {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xff,0x07,0x80,0x69, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},};
unsigned char serNum[5];
//д������
//ԭ����A���룬16��������ÿ����������6Byte
unsigned char sectorKeyA[16][16] = {
 {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
 {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
 {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},};

void setup(){
  RC = "";
  Serial.begin(9600);
  SPI.begin();
  rfid.init();
  Serial.begin(9600);
  servo_A1.attach(A1);
}

void loop(){
  if ( rfid.isCard()  ) {
    RC = RFID_readcardnum();
    Serial.println(RC);
    for (int i = (1); i <= (sizeof(card)/sizeof(card[0])); i = i + (1)) {
      if (RC == card[(int)(i - 1)]) {
        servo_A1.write(90);
        delay(3000);
        servo_A1.write((-90));
        delay(3000);

      }
    }
  }

}
