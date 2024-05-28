---

## Documentação do Código: Carrinho Robô Controlado por Blynk

### Descrição
O projeto visa desenvolver um carrinho de controle remoto utilizando o microcontrolador ESP32, que é controlado via Wi-fi. O principal objetivo é aplicar conceitos de Internet das Coisas (IoT) para criar um veículo robótico que possa ser operado remotamente através de um aplicativo de smartphone. O carrinho será construído sobre um chassi Arduino 2WD e utilizará um módulo Driver Ponte H para o controle de movimentação. Este projeto não só servirá como uma excelente ferramenta de aprendizado prático para a equipe em tecnologias emergentes de IoT, mas também proporcionará uma base para futuras inovações e implementações em automação e robótica.

### Componentes
- **Microcontrolador:** ESP32
- **Driver de Motor:** Ponte H (ou outro driver de motor compatível)
- **Motores:** Motores DC com caixa de redução
- **Alimentação:** Bateria para os motores

### Pré-requisitos
- ESP32 (ou outro microcontrolador compatível com WiFi e PWM)
- Aplicativo Blynk instalado em um dispositivo móvel
- Conexão com uma rede Wi-Fi
- Token de Autenticação do Blynk e credenciais de rede Wi-Fi configuradas no código

### Pinagem do ESP32
- **MOTOR1_IN1:** GPIO 33
- **MOTOR1_IN2:** GPIO 32
- **MOTOR2_IN1:** GPIO 25
- **MOTOR2_IN2:** GPIO 26

### Bibliotecas Utilizadas
- WiFi.h: Para conexão Wi-Fi
- BlynkSimpleEsp32.h: Para integração com o Blynk

### Instruções de Uso
1. **Configuração Inicial:**
   - Insira o Token de Autenticação do Blynk, SSID (nome da sua rede Wi-Fi) e senha (pass) no início do código.

   ```cpp
   #define BLYNK_TEMPLATE_ID ""
   #define BLYNK_TEMPLATE_NAME "Carrinho robô"
   #define BLYNK_AUTH_TOKEN ""  // Insira o token de autenticação do Blynk
   #define BLYNK_PRINT Serial
   
   #include <WiFi.h>
   #include <BlynkSimpleEsp32.h>
   
   char auth[] = "INSIRA_SEU_TOKEN_AQUI";
   char ssid[] = "INSIRA_NOME_SSID_AQUI"; 
   char pass[] = "INSIRA_SENHA_WIFI_AQUI";
   ```

2. **Inicialização dos Motores:**
   - Configure os pinos dos motores como saídas e inicialize o PWM para cada pino.

   ```cpp
   void setup() {
     Serial.begin(9600);
     
     pinMode(MOTOR1_IN1, OUTPUT);
     pinMode(MOTOR1_IN2, OUTPUT);
     pinMode(MOTOR2_IN1, OUTPUT);
     pinMode(MOTOR2_IN2, OUTPUT);
     
     ledcAttachPin(MOTOR1_IN1, 0);
     ledcSetup(0, 5000, 8);  // Canal 0, frequência 5000Hz, resolução 8 bits
     ledcAttachPin(MOTOR1_IN2, 1);
     ledcSetup(1, 5000, 8);  // Canal 1, frequência 5000Hz, resolução 8 bits
     ledcAttachPin(MOTOR2_IN1, 2);
     ledcSetup(2, 5000, 8);  // Canal 2, frequência 5000Hz, resolução 8 bits
     ledcAttachPin(MOTOR2_IN2, 3);
     ledcSetup(3, 5000, 8);  // Canal 3, frequência 5000Hz, resolução 8 bits
     
     Blynk.begin(auth, ssid, pass);
   }
   ```

3. **Funções de Controle:**
   - As funções `carForward()`, `carBackward()`, `carLeft()`, `carRight()` e `carStop()` controlam a direção do carrinho com base nos valores recebidos dos pinos virtuais do Blynk.

   ```cpp
   void carForward() {
     ledcWrite(0, Speed);
     ledcWrite(1, 0);
     ledcWrite(2, Speed);
     ledcWrite(3, 0);
   }
   
   void carBackward() {
     ledcWrite(0, 0);
     ledcWrite(1, Speed);
     ledcWrite(2, 0);
     ledcWrite(3, Speed);
   }
   
   void carLeft() {
     ledcWrite(0, 0);
     ledcWrite(1, Speed);
     ledcWrite(2, Speed);
     ledcWrite(3, 0);
   }
   
   void carRight() {
     ledcWrite(0, Speed);
     ledcWrite(1, 0);
     ledcWrite(2, 0);
     ledcWrite(3, Speed);
   }
   
   void carStop() {
     ledcWrite(0, 0);
     ledcWrite(1, 0);
     ledcWrite(2, 0);
     ledcWrite(3, 0);
   }
   ```

4. **Função `smartcar()` e Loop Principal:**
   - `smartcar()` interpreta os valores de x e y recebidos do Blynk para decidir o movimento do carrinho.
   - `loop()` mantém o Blynk rodando e executa a função de controle `smartcar()`.

   ```cpp
   void smartcar() {
     if (y > 70) {
       carForward();
       Serial.println("carForward");
     } else if (y < 30) {
       carBackward();
       Serial.println("carBackward");
     } else if (x < 30) {
       carLeft();
       Serial.println("carLeft");
     } else if (x > 70) {
       carRight();
       Serial.println("carRight");
     } else if (x < 70 && x > 30 && y < 70 && y > 30) {
       carStop();
       Serial.println("carStop");
     }
   }
   
   void loop() {
     Blynk.run();  // Executa o Blynk
     smartcar();   // Executa a lógica de controle do carrinho
   }
   ```

### Funcionamento
- O carrinho robô é controlado pelos valores de x e y recebidos através do aplicativo Blynk.
- Movimentos possíveis são para frente, para trás, para a esquerda, para a direita e parar.
- Os movimentos são controlados através do ajuste dos sinais PWM para os motores.

### Exemplo de Aplicativo Blynk
- No aplicativo Blynk, adicione três widgets do tipo `Joystick`:
  - Widget V0: Controla o eixo x (de 0 a 100)
  - Widget V1: Controla o eixo y (de 0 a 100)
  - Widget V2: Controla a velocidade (de 0 a 255)

### Observações
- Certifique-se de configurar corretamente o projeto no Blynk e que o token de autenticação e as credenciais de Wi-Fi estejam corretas.
- Ajuste os valores de x, y e Speed no aplicativo Blynk para controlar o movimento do carrinho robô.

### Conclusão
Este código proporciona uma base para controlar um carrinho robô via Wi-Fi usando o ESP32 e o aplicativo Blynk. Ele pode ser expandido para incluir mais funcionalidades, como sensores adicionais ou um controle mais refinado dos motores.

---
