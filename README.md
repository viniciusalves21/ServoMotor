# Controle de Servo Motor com Raspberry Pi Pico e LED

Este projeto demonstra como controlar um servo motor usando um Raspberry Pi Pico 

## Descrição

O código em C configura o Raspberry Pi Pico para gerar sinais PWM nos pinos GPIO conectados ao servo motor e ao LED. O servo motor é controlado para se mover entre 0 e 180 graus, enquanto o LED é aceso durante o movimento do servo em uma direção e apagado na direção oposta.

## Código

O código foi escrito em C e utiliza as bibliotecas `pico/stdlib.h` e `hardware/pwm.h` para controlar os pinos GPIO e gerar os sinais PWM.

### Funções

* **`set_pwm_pulse(uint gpio, uint16_t pulse_width)`:** Configura a largura do pulso PWM em um pino GPIO específico.

## Como usar

1. Clone este repositório.
2. Conecte os componentes de acordo com as conexões descritas acima.
3. Compile o código usando o SDK do Raspberry Pi Pico.
4. Envie o código para o Raspberry Pi Pico.
5. Observe o servo motor se mover entre 0 e 180 graus e o LED acender durante o movimento em uma direção e apagar na direção oposta.

## Observações

* Os valores de `PULSE_180`, `PULSE_90` e `PULSE_0` podem precisar ser ajustados dependendo do seu servo motor.
* O valor de `WRAP_VALUE` deve ser definido de acordo com o período do sinal PWM desejado (50Hz, 20ms).
* O valor de `pwm_set_clkdiv` deve ser calculado e ajustado de acordo com a frequência do clock do sistema e a frequência desejada para o PWM.

## Video

[https://www.youtube.com/shorts/sipos9cY-KA]
