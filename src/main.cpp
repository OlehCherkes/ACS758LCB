#include <Arduino.h>

#define ANALOG_PIN 13  // аналоговый PIN
const float VCC = 3.3; // подаваемое напряжение на датчик (для модуля только 5 вольт)

float Limit = 1.00; // принимаем значение 1 для отображение есть ли ток в контуре

/*
// настройки чуствительности для моделей датчика и установка покоя (для двонаправленого 0.5 для однонаправленного 0.12)
          "ACS758LCB-050B",// 40.0mV и напряжение покоя 0.5mV
          "ACS758LCB-050U",// 60.0mV и напряжение покоя 0.12mV
          "ACS758LCB-100B",// 20.0mV и напряжение покоя 0.5mV
          "ACS758LCB-100U",// 40.0mV и напряжение покоя 0.12mV
          "ACS758KCB-150B",// 13.3mV и напряжение покоя 0.5mV
          "ACS758KCB-150U",// 16.7mV и напряжение покоя 0.12mV
          "ACS758ECB-200B",// 10.0mV и напряжение покоя 0.5mV
          "ACS758ECB-200U"//  20.0mV и напряжение покоя 0.12mV
*/

const float FACTOR = 20.0 / 1000; // чуствительность датчика (0.02V)
const float QOV = 0.5 * VCC;      // установка покоя для датчика
float voltage;                    // сохраняем значение напряжения в переменную
float cutOff = FACTOR / Limit;    // convert current cut off to mV

int max_current = 0;
int min_current = 0;

void MaxMin(int frequency, int current);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  float voltage_raw = (3.3 / 4095.0) * analogRead(ANALOG_PIN); // считывем значение с датчика
  voltage = voltage_raw - QOV + 0.1;                           // 0.1 добавление коефициента что бы обнулить
  float current = voltage / FACTOR;                            // расчет тока
  if (voltage > FACTOR)
  {
    Serial.print(voltage, 2);
    Serial.print(" V");
    Serial.print("   ");
    Serial.print(current, 2);
    Serial.println(" A");
  }
  else
  {
    Serial.println("No Current");
  }
  delay(500);
}

void MaxMin(int frequency, int current)
{
  if (current > max_current)
  {
    max_current = current;
    Serial.print("Max current: "); Serial.print(max_current); Serial.print(" A"); 
    Serial.print("   Frequency"); Serial.print(frequency); Serial.println(" Hz");
  }
  else if (current <= min_current)
  {
    min_current = current;
    Serial.print("Min current: "); Serial.print(min_current); Serial.print(" A"); 
    Serial.print("   Frequency"); Serial.print(frequency); Serial.print(" Hz");
  }
}