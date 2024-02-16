// LiquidCrystal(RS, E, D4, D5, D6, D7)

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <IRremote.hpp>
#include <IRLibSendBase.h> //We need the base code
#include <IRLib_HashRaw.h> //Only use raw senderI

IRsendRaw mySender;
IRsend aire;
#define RAW_DATA_LEN_92 92
#define RAW_DATA_LEN_96 96
#define RAW_DATA_LEN_100 100
#define D4 5
#define D5 4
#define D6 9
#define D7 2
#define E 11
#define RS 12
#define POT1 A0
#define POT2 A1
#define ALTAVOZ 8

uint32_t subidaTemp[] = {0x10006314, 0x3008FC10, 0x1101C0, 0xFE0000};
uint32_t bajadaTemp[] = {0x10006314, 0x3008FC10, 0x110180, 0x3E0000};

uint16_t aire_acon[100] = {
    3050, 1750, 250, 600, 200, 600, 200, 1350, 200, 600, 250, 1350, 200, 600, 200, 650, 200, 650, 250, 1350, 200, 1350, 250, 600, 200, 600, 200, 650, 200, 1350, 200, 1400, 200, 600, 250, 600, 250, 600, 200, 650, 200, 600, 200, 600, 250, 550, 250, 600, 200, 650, 250, 600, 200, 600, 250, 600, 200, 600, 250, 1350, 200, 650, 200, 600, 200, 650, 250, 600, 250, 550, 250, 650, 200, 600, 200, 1350, 250, 550, 200, 650, 200, 650, 250, 600, 200, 1350, 200, 650, 200, 600, 200, 600, 200, 600, 200, 600, 200, 650, 200};
uint16_t ventilador_1[RAW_DATA_LEN_100] = {

    1262, 418, 1270, 418, 426, 1270, 414, 1270,
    418, 1270, 418, 1266, 422, 1266, 418, 1270,
    418, 1270, 1262, 418, 426, 1266, 418, 8018, 1262, 422, 1266, 422, 422, 1270, 418, 1266,
    418, 1270, 422, 1266, 418, 1270, 418, 1270,
    418, 1270, 1258, 422, 426, 1266, 418, 8046,
    1234, 422, 1266, 422, 422, 1266, 418, 1274,
    414, 1270, 418, 1270, 418, 1270, 414, 1274,
    414, 1270, 1262, 422, 422, 1270, 418, 8018,
    1262, 418, 1266, 422, 422, 1270, 418, 1270,
    414, 1274, 386, 1302, 414, 1270, 414, 1274,
    390, 1298, 1258, 426, 390, 1302, 410, 8026,
    1230, 454, 1230, 1000

};

uint16_t ventilador_2[RAW_DATA_LEN_100] = {

    1262, 418, 1270, 418, 422, 1270, 418, 1270,
    418, 1270, 418, 1270, 418, 1270, 414, 1270,
    1262, 422, 422, 1270, 414, 1274, 414, 8022,
    1262, 418, 1266, 422, 422, 1270, 418, 1270,
    418, 1270, 414, 1270, 418, 1270, 418, 1270,
    1262, 422, 422, 1270, 414, 1274, 414, 8022,
    1258, 422, 1266, 422, 422, 1270, 418, 1270, 414, 1270, 422, 1266, 418, 1270, 418, 1270,
    1262, 418, 426, 1270, 414, 1270, 418, 8018,
    1262, 418, 1270, 418, 426, 1266, 422, 1270,
    414, 1274, 414, 1270, 418, 1266, 422, 1270,
    1262, 418, 422, 1270, 418, 1270, 418, 8022,
    1258, 418, 1270, 1000};

uint16_t ventilador_3[RAW_DATA_LEN_100] = {

    1230, 454, 1262, 418, 422, 1274, 414, 1270,
    390, 1298, 418, 1270, 390, 1298, 1262, 418,
    422, 1206, 454, 1298, 390, 1298, 390, 8046,
    1238, 450, 1254, 426, 394, 1302, 410, 1274,
    414, 1274, 386, 1298, 390, 1298, 1258, 426,
    418, 1274, 414, 1274, 390, 1298, 386, 8050,
    1258, 422, 1266, 422, 394, 1298, 390, 1298,
    390, 1294, 390, 1302, 414, 1270, 1262, 422,
    422, 1270, 414, 1274, 414, 1270, 418, 8022,
    1258, 422, 1262, 426, 418, 1274, 414, 1270,
    418, 1270, 414, 1274, 418, 1270, 1258, 426,
    422, 1270, 414, 1270, 418, 1270, 418, 8018,
    1262, 422, 1262, 1000};

uint16_t ventilador_apagar[RAW_DATA_LEN_100] = {

    1230, 454, 1234, 454, 386, 1302, 386, 1302,
    386, 1302, 386, 1302, 386, 1298, 390, 1298,
    386, 1302, 386, 1302, 386, 1302, 1226, 7210,
    1230, 454, 1230, 458, 386, 1302, 414, 1274,
    386, 1298, 390, 1298, 390, 1298, 390, 1298,
    386, 1302, 386, 1298, 390, 1298, 1234, 7202,
    1234, 454, 1234, 454, 386, 1298, 398, 1290,
    390, 1298, 390, 1298, 386, 1302, 410, 1274,
    390, 1302, 386, 1298, 390, 1298, 1230, 7206,
    1230, 458, 1230, 454, 390, 1298, 390, 1298,
    390, 1298, 386, 1302, 386, 1298, 390, 1298,
    386, 1302, 386, 1302, 386, 1298, 1234, 7206,
    1230, 454, 1234, 1000};

uint16_t luz_ventilador[RAW_DATA_LEN_96] = {

    1262, 422, 1266, 418, 426, 1266, 418, 1270,
    418, 1270, 418, 1270, 414, 1270, 418, 1270,
    414, 1274, 418, 1270, 1262, 418, 422, 8022,
    1258, 422, 1266, 422, 422, 1270, 414, 1274,
    414, 1270, 418, 1270, 418, 1270, 418, 1270,
    414, 1270, 418, 1270, 1262, 418, 426, 8018,
    1258, 422, 1266, 422, 422, 1270, 414, 1274,
    414, 1270, 418, 1270, 414, 1274, 414, 1274,
    414, 1274, 386, 1298, 1262, 422, 418, 8022,
    1234, 454, 1230, 454, 402, 1286, 414, 1274,
    390, 1298, 414, 1270, 414, 1278, 386, 1298,
    414, 1274, 398, 1290, 1230, 454, 390, 1000

};

LiquidCrystal LCD(RS, E, D4, D5, D6, D7);
bool aire_on = false;
bool vent_on = false;
bool frio = false;
int valor_pot1 = 0;
int valor_pot2 = 0;

void setup()
{

  Serial.begin(9600);
  LCD.begin(16, 2);
  pinMode(POT1, INPUT);
  pinMode(POT2, INPUT);
  pinMode(ALTAVOZ, OUTPUT);
  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.print("Unidad Control");
  LCD.setCursor(0, 1);
  LCD.print("De Temperatura");
  delay(5000);
  aire.begin(3);
  delay(500);
}


void manejar_aire(int *valor_pot_aire, bool mayor)
{

  LCD.clear();

/*
  String monitor_vent;


  if (*valor_pot_vent == 0)
  {
    mySender.send(ventilador_apagar, RAW_DATA_LEN_100, 38);
  }
  else if (*valor_pot_vent == 1)
  {
    mySender.send(ventilador_apagar, RAW_DATA_LEN_100, 38);
    mySender.send(luz_ventilador, RAW_DATA_LEN_100, 36);
  }
  else if (*valor_pot_vent == 2)
  {
    mySender.send(ventilador_1, RAW_DATA_LEN_100, 38);
    mySender.send(luz_ventilador, RAW_DATA_LEN_100, 36);
  }
  else if (*valor_pot_vent == 3)
  {
    mySender.send(ventilador_1, RAW_DATA_LEN_100, 38);
    mySender.send(luz_ventilador, RAW_DATA_LEN_100, 36);
  }
  else if (*valor_pot_vent == 4)
  {
    mySender.send(ventilador_2, RAW_DATA_LEN_100, 38);
    mySender.send(luz_ventilador, RAW_DATA_LEN_100, 36);
  }
  else if (*valor_pot_vent == 5)
  {
    mySender.send(ventilador_2, RAW_DATA_LEN_100, 38);
    mySender.send(luz_ventilador, RAW_DATA_LEN_100, 36);
  }
  else if (*valor_pot_vent == 6)
  {
    mySender.send(ventilador_3, RAW_DATA_LEN_100, 38);
    mySender.send(luz_ventilador, RAW_DATA_LEN_100, 36);
  }
  else if (*valor_pot_vent == 7)
  {
    mySender.send(ventilador_3, RAW_DATA_LEN_100, 38);
    mySender.send(luz_ventilador, RAW_DATA_LEN_100, 36);
  }
*/
  if (mayor)
  {

    aire.sendPulseDistanceWidthFromArray(38, 3150, 1700, 350, 1200, 350, 450, &subidaTemp[0], 120, PROTOCOL_IS_LSB_FIRST, 1024, 0);
    delay(500);
  }
  else
  {
    aire.sendPulseDistanceWidthFromArray(38, 3150, 1700, 350, 1200, 350, 450, &subidaTemp[0], 120, PROTOCOL_IS_LSB_FIRST, 1024, 0);
    delay(500);
  }

  if (*valor_pot_aire == 25)
  {

    aire_on = true;
    frio = true;

    uint32_t tRawData[] = {0x10006314, 0x3008FC10, 0x10171, 0x5D0000};
    aire.sendPulseDistanceWidthFromArray(38, 3150, 1700, 300, 1250, 300, 550, &tRawData[0], 120, PROTOCOL_IS_LSB_FIRST, 1024, 0);

    delay(500);
    uint32_t tRawData2[] = {0x10006314, 0x3008FC10, 0x110170, 0x4E0000};
    aire.sendPulseDistanceWidthFromArray(38, 3100, 1700, 400, 1200, 400, 400, &tRawData2[0], 120, PROTOCOL_IS_LSB_FIRST, 1024, 0);

    // delay(500);

    tone(ALTAVOZ, 9000);
    delay(50);
    noTone(ALTAVOZ);
  }
  else if (*valor_pot_aire == 22)
  {

    aire_on = true;
    frio = false;
    uint32_t tRawData[] = {0x10006314, 0x3008FC10, 0x10461, 0x6A0000};
    aire.sendPulseDistanceWidthFromArray(38, 3150, 1700, 350, 1200, 350, 500, &tRawData[0], 120, PROTOCOL_IS_LSB_FIRST, 1024, 0);

    //delay(500);

    tone(ALTAVOZ, 500);
    delay(200);
    noTone(ALTAVOZ);
  }
  else if (*valor_pot_aire == 23)
  {

    aire_on = false;

    mySender.send(aire_acon, RAW_DATA_LEN_100, 36);

    tone(ALTAVOZ, 200);
    delay(100);
    noTone(ALTAVOZ);
    tone(ALTAVOZ, 200);
    delay(100);
    noTone(ALTAVOZ);

    

  }

  if (aire_on)
  {
    LCD.setCursor(0, 1);
    LCD.print("Temperatura:");
    LCD.print(*valor_pot_aire);
    LCD.print("C");

  /*
  
    if(*valor_pot_vent == 0){

      monitor_vent = " 0";

    }else if(*valor_pot_vent == 1){

      monitor_vent = " 0*";
    } else if(*valor_pot_vent == 2){

      monitor_vent = " 1";
    } else if(*valor_pot_vent == 3){

      monitor_vent = " 1*";
    } else if(*valor_pot_vent == 4){

      monitor_vent = " 2 ";
    } else if(*valor_pot_vent == 5){

      monitor_vent = " 2*";
    } else if(*valor_pot_vent == 6){

      monitor_vent = " 3 ";
    } else if(*valor_pot_vent == 7){

      monitor_vent = " 3*";
    } 
  */  
    
    //LCD.print(monitor_vent);

    Serial.print("Valor del pot1:");
    Serial.println(analogRead(POT1));
    Serial.print("Valor del pot2:");
    Serial.println(analogRead(POT1));
  }
}

void loop()
{

  static unsigned long int tiempo_texto_linea_0 = 0;

  if (millis() - tiempo_texto_linea_0 > 100)
  {

    tiempo_texto_linea_0 = millis();

    LCD.setCursor(0, 0);
    if (aire_on == true && frio == true)
    {
      LCD.print("FRIO  ENCENDIDO.");
    }
    else if (aire_on == true && frio == false)
    {

      LCD.print("CALOR ENCENDIDO.");
    }
    else
    {

      LCD.print(" Aire  apagado.");
    }
    delay(500);
  }

  static unsigned long int tiempo_valor_potes = 0;

  if (millis() - tiempo_valor_potes > 30)
  {

    tiempo_valor_potes = millis();

    int valor_actual_pot1 = (analogRead(POT1) + 108) / 108.8 + 17;
    int valor_actual_pot2 = (analogRead(POT2) + 109.5) / 109.5;

    if (valor_actual_pot1 > valor_pot1)
    {

      valor_pot1 = valor_actual_pot1;

      manejar_aire(&valor_pot1, 1);
    }
    else if (valor_actual_pot1 < valor_pot1)
    {

      valor_pot1 = valor_actual_pot1;

      manejar_aire(&valor_pot1, 0);
    }

/*

    if(valor_actual_pot2 != valor_pot2){


      valor_pot2 = valor_actual_pot2;
      manejar_aire(&valor_pot1,&valor_pot2, 0);

    }


*/
  }
}