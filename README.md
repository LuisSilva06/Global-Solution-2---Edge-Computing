📘 Sistema de Monitoramento de Postura e Produtividade
ESP32 + MPU6050 + MQTT

🧩 Descrição do Problema

Profissionais que trabalham em home office frequentemente passam longos períodos sentados, muitas vezes mantendo posturas inadequadas, como inclinação excessiva da coluna ou cabeça projetada para frente.

Essas más posturas podem gerar:

Dores lombares e cervicais

Fadiga muscular

Redução de produtividade

Riscos ergonômicos a longo prazo

Sem supervisão ou lembretes, manter uma postura correta torna-se ainda mais difícil.

🎯 Objetivo da Solução

Este projeto implementa um sistema IoT de monitoramento postural utilizando:

ESP32

Sensor MPU6050 (acelerômetro + giroscópio)

Comunicação MQTT

LED e buzzer como alertas locais

O sistema é capaz de:

✔ Monitorar a inclinação do usuário
✔ Identificar más posturas
✔ Emitir alertas após 10 segundos de postura inadequada
✔ Enviar dados via MQTT para dashboards ou automações
✔ Permitir comandos remotos (ligar LED, buzzer, etc.)
🔧 4. Instruções de Uso
4.1 Simulação no Wokwi

Abra o projeto no Wokwi.

https://wokwi.com/projects/448257548864290817

Pressione ▶️ Play.

Clique no MPU6050 e arraste para simular inclinação.

Observe no terminal:

“Postura boa”

“Postura ruim detectada”

Alertas após 10s

O LED acende e o buzzer toca quando a postura é ruim por mais de 10 segundos.

4.2 Como testar
Ação	Resultado
Inclinar o sensor	“Postura ruim detectada”
Manter >10s inclinado	LED acende + buzzer toca
Corrigir postura	Alerta desliga automaticamente

📡 Comunicação MQTT

O sistema usa o broker público:

Broker: broker.hivemq.com
Porta: 1883

📤 Tópicos Publicados
Tópico	Descrição	Exemplo
projeto/sensores	Dados brutos do acelerômetro	X: 1500, Y: -200, Z: 9000
projeto/postura	Estado da postura	Postura boa
projeto/alerta	Alerta após má postura	Postura ruim por 10 segundos
📥 Tópico Assinado (Subscribe)
Tópico	Função	Comandos
projeto/comando	Controle remoto do ESP32	led_on, led_off, alarm_on, alarm_off
Hardware

ESP32 DevKit V1

MPU6050

LED + resistor 220Ω

Buzzer piezo

🤖 Funcionamento da Lógica de Postura

O ESP32 lê continuamente valores do MPU6050.

Se a inclinação exceder o limite → postura considerada ruim.

Se permanecer ruim por 10 segundos:

LED acende

Buzzer toca

Mensagem enviada via MQTT

Se o usuário corrige a postura:

Alertas são desligados

O contador é resetado

🏁 Conclusão

Este projeto demonstra um sistema IoT completo que:

✔ Lê sensores
✔ Aciona atuadores
✔ Se comunica via MQTT
✔ Integra-se ao tema “Postura e Produtividade para Escritório Remoto”

Ele fornece uma solução de baixo custo, expansível e prática para melhorar hábitos ergonômicos no trabalho remoto.

Luis Gustavo RM:561672
Kauan Benites RM:562115
Mateus Nunes RM:562008
