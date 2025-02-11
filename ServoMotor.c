#include "pico/stdlib.h" 
#include <stdio.h>

#include "hardware/pwm.h" // Inclui funções para controle de PWM

#define LED_PIN 12     // Pino do LED RGB para experimento

// Define constantes para configurar o PWM e o servo motor
#define PWM_GPIO 22       // Pino GPIO conectado ao servo motor
#define WRAP_VALUE 25000  // Período do sinal PWM (50Hz, 20ms). 

#define PULSE_180 1920   // Largura do pulso para 180 graus. 
#define PULSE_90  1190   // Largura do pulso para 90 graus.  
#define PULSE_0   400    // Largura do pulso para 0 graus.   

#define SWEEP_STEP 5    // Incremento/decremento da largura do pulso para movimento suave
#define SWEEP_DELAY 10  // Tempo de espera entre os passos (10ms)

// Função para configurar a largura do pulso PWM em um pino GPIO
void set_pwm_pulse(uint gpio, uint16_t pulse_width) {
    uint slice_num = pwm_gpio_to_slice_num(gpio); // Obtém o número da "fatia" PWM associada ao pino
    uint16_t level = (pulse_width * WRAP_VALUE) / 20000; // Converte a largura do pulso para o nível PWM adequado. 
    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(gpio), level); // Define o nível do PWM no canal correto
}

int main() {
    stdio_init_all(); // Inicializa as entradas e saídas padrão

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_set_function(PWM_GPIO, GPIO_FUNC_PWM); // Configura o pino PWM_GPIO para usar a função PWM
    uint slice_num = pwm_gpio_to_slice_num(PWM_GPIO); // Obtém o número da fatia PWM associada ao pino

    uint led_slice = pwm_gpio_to_slice_num(LED_PIN);
    uint led_channel = pwm_gpio_to_channel(LED_PIN);

    pwm_set_wrap(slice_num, WRAP_VALUE);      // Define o valor de "wrap" (período) para o PWM. *AJUSTAR CONFORME NECESSÁRIO*
    pwm_set_clkdiv(slice_num, 125.0f);    // Define o divisor de clock para o PWM. *CALCULAR E AJUSTAR CONFORME NECESSÁRIO*
    pwm_set_enabled(slice_num, true);     // Habilita a geração do sinal PWM

    pwm_set_wrap(led_slice, WRAP_VALUE);
    pwm_set_clkdiv(led_slice, 64.0f);
    pwm_set_enabled(led_slice, true);

    // Define o servo para algumas posições iniciais (e espera 5 segundos em cada posição)
    set_pwm_pulse(PWM_GPIO, PULSE_180); // Servo em 180 graus
    sleep_ms(5000);                     // Espera 5 segundos
    set_pwm_pulse(PWM_GPIO, PULSE_90);  // Servo em 90 graus
    sleep_ms(5000);                     // Espera 5 segundos
    set_pwm_pulse(PWM_GPIO, PULSE_0);   // Servo em 0 graus
    sleep_ms(5000);                     // Espera 5 segundos


    // Loop infinito para controlar o movimento contínuo do servo
    while (true) {
        // Loop para mover o servo de 0 a 180 graus
        for (uint16_t pulse = PULSE_0; pulse <= PULSE_180; pulse += SWEEP_STEP) {
            set_pwm_pulse(PWM_GPIO, pulse); // Define a largura do pulso para a posição atual
            printf("ligando o led\n");
            gpio_put(LED_PIN, true);
            sleep_ms(SWEEP_DELAY);         // Espera um pouco para criar o movimento suave
            printf("desligando o led apos primeiro for\n");
            gpio_put(LED_PIN, false);
        }

        // Loop para mover o servo de 180 a 0 graus
        for (uint16_t pulse = PULSE_180; pulse >= PULSE_0; pulse -= SWEEP_STEP) {
            set_pwm_pulse(PWM_GPIO, pulse); // Define a largura do pulso para a posição atual
            printf("ligando o led apos segundo for\n");
            gpio_put(LED_PIN, false);
            sleep_ms(SWEEP_DELAY);         // Espera um pouco para criar o movimento suave
            printf("desligando o led apos segundo for\n");
            gpio_put(LED_PIN, true);
        }
    }
}