#include <Wire.h> #include <WiFi.h> #include <PubSubClient.h>

#define LED 2 #define BUZZER 4

// WiFi do Wokwi const char* ssid = “Wokwi-GUEST”; const char* password
= ““;

// Broker MQTT público const char* mqtt_server = “broker.hivemq.com”;

WiFiClient espClient; PubSubClient client(espClient);

// MPU6050 const int MPU = 0x68; int16_t AcX, AcY, AcZ;

// —- LÓGICA DE POSTURA —- const int LIMIAR_INCLINACAO = 8000; // ajuste
conforme o sensor unsigned long tempo_inclinacao = 0; bool postura_ruim
= false; bool alerta_disparado = false; int alertas = 0; unsigned long
inicio_sessao = 0;

void setup_wifi() { WiFi.begin(ssid, password); while (WiFi.status() !=
WL_CONNECTED) delay(200); }

void reconnect() { while (!client.connected()) { if
(client.connect(“ESP32_MQTT_TEST”)) {
client.subscribe(“projeto/comando”); } else { delay(1000); } } }

void callback(char* topic, byte* payload, unsigned int length) { String
msg; for (int i = 0; i < length; i++) msg += (char)payload[i];

if (msg == “led_on”) digitalWrite(LED, HIGH); if (msg == “led_off”)
digitalWrite(LED, LOW);

if (msg == “alarm_on”) tone(BUZZER, 1000); if (msg == “alarm_off”)
noTone(BUZZER); }

void setup() { Serial.begin(115200);

pinMode(LED, OUTPUT); pinMode(BUZZER, OUTPUT);

// Inicia MPU Wire.begin(); Wire.beginTransmission(MPU);
Wire.write(0x6B); Wire.write(0); Wire.endTransmission(true);

setup_wifi(); client.setServer(mqtt_server, 1883);
client.setCallback(callback);

inicio_sessao = millis();

Serial.println(“=== Sistema de Monitoramento de Postura Iniciado ===”);
}

void loop() { if (!client.connected()) reconnect(); client.loop();

// Leitura MPU6050 Wire.beginTransmission(MPU); Wire.write(0x3B);
Wire.endTransmission(false); Wire.requestFrom(MPU, 6, true);

AcX = Wire.read() << 8 | Wire.read(); AcY = Wire.read() << 8 |
Wire.read(); AcZ = Wire.read() << 8 | Wire.read();

// —– LÓGICA DE POSTURA —– bool inclinacao_excessiva = abs(AcX) >
LIMIAR_INCLINACAO || abs(AcY) > LIMIAR_INCLINACAO;

if (inclinacao_excessiva) {

    if (!postura_ruim) {
      postura_ruim = true;
      tempo_inclinacao = millis();
      alerta_disparado = false;
      Serial.println("⚠ Postura ruim detectada (início).");
    }

    if (!alerta_disparado && millis() - tempo_inclinacao > 10000) {
      digitalWrite(LED, HIGH);
      tone(BUZZER, 1500);

      alertas++;
      alerta_disparado = true;

      Serial.println("❗ ALERTA: postura ruim prolongada! Ativando aviso.");
      client.publish("projeto/postura", "ALERTA: postura ruim prolongada!");
    }

} else {

    if (postura_ruim) {
      Serial.println("✅ Postura corrigida.");
    }

    postura_ruim = false;
    alerta_disparado = false;

    digitalWrite(LED, LOW);
    noTone(BUZZER);

    Serial.println("👍 Postura boa.");

}

unsigned long tempo_total = (millis() - inicio_sessao) / 1000;

char status[120]; sprintf( status,
“postura:%s,tempo_sessao:%lus,alertas:%d”, postura_ruim ? “ruim” :
“boa”, tempo_total, alertas );

client.publish(“projeto/produtividade”, status);

delay(300); }
