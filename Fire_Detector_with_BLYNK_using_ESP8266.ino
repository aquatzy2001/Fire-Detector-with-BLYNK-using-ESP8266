#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//Bagian ini untuk mengeluarkan output dari Blynk ke Serial Monitor
#define BLYNK_PRINT Serial

// inialisasi variabel data
int Api;
float vref = 3.3;
float resolution = vref / 1023.0;
float temperature;
//Bagian ini untuk login ke server Blynk
char auth[] = "auth token"; //Isi token yang didapat dari email
char ssid[] = "nama wifi"; //Nama wifi yang dipakai
char pass[] = "password wifi"; //Nama password wifi yang dipakai

//Bagian ini untuk menentukan pin dari sensor, buzzer, relay dan LED
#define LM35 A0
#define LED1 1
#define LED2 2
#define FLAME 6
#define BUZZER 7
#define RELAY 4

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  
  // Inialisasi status Input/Output pin
  pinMode(LM35, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(FLAME, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode (RELAY, OUTPUT);
}

//Bagian ini untuk membaca dan mengirim nilai sensor suhu ke aplikasi Blynk
void sendUptime()
{
  int brightness = temperature;
  analogWrite(LED2, brightness);
}
//Bagian ini adalah bagian yang akan dieksekusi secara looping oleh Wemos
  void loop()
  {
    Blynk.run();
    Api = digitalRead(FLAME);
    // Jika data pada sensor API bernilai logic LOW (ada api)
    if (Api == LOW)
    {
      // Alarm dinyalakan
      tone (BUZZER, 2000 , 50);
      digitalWrite(LED1, HIGH);
      Blynk.notify (" ADA API !!! ");
      digitalWrite (RELAY, HIGH);
    }
    // Jika data tidak bernilai logic LOW (tidak ada api)
    else
    {
      //LED dimatikan
      digitalWrite(LED1, LOW);
      // Alarm dimatikan
      analogWrite (BUZZER, 0);
      digitalWrite(RELAY, LOW);
    }
    }
