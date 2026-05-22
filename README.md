# Vinheria Agnello - Sistema de Monitoramento Ambiental

## Edge Computing & Computer Systems - Checkpoint 02
### FIAP - Engenharia de Software

---

## Descrição do Projeto

Este projeto é a segunda fase do sistema de monitoramento ambiental desenvolvido para a Vinheria Agnello, uma vinheria tradicional que busca expandir suas operações para o comércio eletrônico. Para garantir a qualidade dos vinhos armazenados, é essencial que o ambiente do depósito seja controlado em relação a três variáveis críticas: luminosidade, temperatura e umidade.

Nesta fase, o sistema foi ampliado com a adição de um sensor DHT11 para leitura de temperatura e umidade, e um display LCD 16x2 com comunicação I2C para exibição dos valores em tempo real. Além disso, os alertas visuais e sonoros foram estendidos para cobrir as três variáveis monitoradas.

---

## Contexto e Motivação

A qualidade do vinho é diretamente influenciada pelas condições ambientais do local de armazenamento:

- **Luminosidade**: A iluminação deve ser muito suave. Raios ultravioletas causam alterações nos compostos orgânicos do vinho, gerando resultados indesejáveis. Vinhos brancos e espumantes são especialmente vulneráveis.

- **Temperatura**: O calor excessivo deteriora o vinho rapidamente. Flutuações térmicas superiores a 3 graus Celsius podem causar o surgimento de aromas indesejáveis. A temperatura ideal é em torno de 13 graus Celsius.

- **Umidade**: A falta de umidade resseca o vedante da garrafa, causando risco de oxidação. O excesso favorece o crescimento de fungos e danifica os rótulos. A faixa ideal é entre 60% e 80%, com valor ótimo próximo a 70%.

---

## Funcionalidades Implementadas

### Monitoramento de Luminosidade
- LED verde aceso enquanto o ambiente estiver escuro (luminosidade abaixo de 30%)
- LED amarelo aceso e mensagem de alerta no display para ambiente a meia luz (entre 30% e 60%)
- LED vermelho aceso, buzzer ativo e mensagem crítica no display para ambiente muito claro (acima de 60%)

### Monitoramento de Temperatura
- Display exibe status OK quando a temperatura está na faixa adequada (abaixo de 23 graus Celsius)
- LED amarelo e buzzer intermitente para alerta (entre 23 graus e 25 graus Celsius)
- LED vermelho, buzzer em frequência elevada e mensagem crítica para temperatura acima de 25 graus Celsius

### Monitoramento de Umidade
- Display exibe status OK quando a umidade está na faixa ideal (entre 50% e 70%)
- LED amarelo e buzzer intermitente para alerta (entre 40%-50% ou 70%-80%)
- LED vermelho, buzzer em frequência elevada e mensagem crítica para umidade abaixo de 40% ou acima de 80%

### Display LCD
- Exibe mensagens de status, alerta e crítico para cada variável
- Prioriza a exibição da condição mais grave detectada
- Animação de coração na inicialização com mensagem de boas-vindas da Vinheria Agnello

### Buzzer
- Sem som em condição normal
- Bipe intermitente a cada 5 segundos em nível de alerta
- Bipe intermitente a cada 2 segundos em nível crítico

---

## Componentes Utilizados

| Componente         | Descrição                                       |
|--------------------|-------------------------------------------------|
| Arduino Uno        | Microcontrolador principal                      |
| Sensor DHT11       | Leitura de temperatura e umidade                |
| Sensor LDR         | Leitura de luminosidade ambiente                |
| Display LCD 16x2   | Exibição de mensagens (comunicação I2C)         |
| LED Verde          | Indicador de condição normal                    |
| LED Amarelo        | Indicador de alerta                             |
| LED Vermelho       | Indicador de condição crítica                   |
| Buzzer             | Alarme sonoro para alertas e condições críticas |
| Resistores         | Proteção dos LEDs e do LDR                      |

---

## Mapeamento de Pinos

| Pino Arduino | Componente        |
|--------------|-------------------|
| D4           | DHT11 (Data)      |
| A2           | LDR               |
| D8           | LED Verde         |
| D9           | LED Amarelo       |
| D10          | LED Vermelho      |
| D11          | Buzzer            |
| SDA / SCL    | LCD I2C (A4 / A5) |

---

## Bibliotecas Necessárias

- **Wire.h** - Comunicação I2C (nativa do Arduino IDE)
- **LiquidCrystal_I2C.h** - Controle do display LCD via I2C
- **DHT.h** - Leitura do sensor DHT11 (biblioteca DHT sensor library by Adafruit)

Para instalar a biblioteca DHT no Arduino IDE:
1. Abra o Arduino IDE
2. Acesse Sketch > Incluir Biblioteca > Gerenciar Bibliotecas
3. Pesquise por "DHT sensor library" e instale a versão da Adafruit
4. Instale também a dependência "Adafruit Unified Sensor" quando solicitado

---

## Como Executar

### Simulação
O projeto pode ser simulado no Wokwi utilizando o sensor DHT11 (compatível com o código). Importe o arquivo `.ino` e monte o circuito conforme o diagrama disponível no repositório.

### Hardware Físico
1. Monte o circuito conforme o diagrama de conexões
2. Instale as bibliotecas necessárias no Arduino IDE
3. Abra o arquivo `vinheria_agnello.ino`
4. Selecione a porta COM correta e o modelo da placa (Arduino Uno)
5. Faça o upload do código

---

## Lógica de Níveis de Alerta

O sistema utiliza três níveis hierárquicos:

- **Nível 0 - OK**: Todas as variáveis dentro dos limites ideais. LED verde aceso, sem som.
- **Nível 1 - Alerta**: Pelo menos uma variável em zona de atenção. LED amarelo aceso, buzzer intermitente (5s).
- **Nível 2 - Crítico**: Pelo menos uma variável fora dos limites seguros. LED vermelho aceso, buzzer intermitente (2s).

O nível exibido é sempre o mais grave detectado entre as três variáveis.

---

## Estrutura do Repositório

```
vinheria-agnello-cp02/
|-- vinheria_agnello.ino     # Código principal do Arduino
|-- diagram.json             # Diagrama do circuito (Wokwi)
|-- circuit_image.png        # Imagem do circuito montado
|-- README.md                # Este arquivo
```

---

## Participantes

| Nome                      | RM     |
|---------------------------|--------|
| Leonardo Scalisse Silva   | 569114 |
| Allan Freire              | 569534 |
| Valdemar Neto             | 573382 |
| Pietro Schimidt Ruotolo   | 570632 |
| Danilo                    | 573831 |

---

## Disciplina

Edge Computing & Computer Systems - Checkpoint 02
Professor: Lucas D. Augusto
FIAP - Engenharia de Software - 2026