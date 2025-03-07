#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <ctype.h>

#define BAUD 115200
#define MYUBRR F_CPU/8/BAUD-1

void init_rgb();
void set_rgb(uint8_t r, uint8_t g, uint8_t b);
void USART_Init(unsigned int ubrr);
char uart_rx(void);
void uart_printstr(const char* str);
uint8_t hex_to_byte(char high, char low);

char buffer[7]; // Stocke "#RRGGBB"
uint8_t count = 0;
uint8_t receiving = 0;

int main(void) {
    init_rgb();
    USART_Init(MYUBRR);
    
    sei(); 

    while (1) {

    }

    return 0;
}

void init_rgb() {
    DDRD |= (1 << PD6) | (1 << PD5) | (1 << PD3);


    TCCR0A |= (1 << WGM00) | (1 << WGM01);
    TCCR0A |= (1 << COM0A1) | (1 << COM0B1);
    TCCR0B |= (1 << CS01); 


    TCCR2A |= (1 << WGM20) | (1 << WGM21);
    TCCR2A |= (1 << COM2B1);
    TCCR2B |= (1 << CS21);
}

void set_rgb(uint8_t r, uint8_t g, uint8_t b) {
    OCR0A = r;
    OCR0B = g;
    OCR2B = b;
}

void USART_Init(unsigned int ubrr) {
    UCSR0A |= (1 << U2X0);
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0); 
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

ISR(USART_RX_vect) {
    char c = UDR0;

    if (c == '#') { 
        receiving = 1;
        count = 0;
    } else if (receiving) {
        if (count < 6 && isxdigit(c)) {
            buffer[count++] = c;
        } else if (count == 6) {
            receiving = 0;
            buffer[count] = '\0';

            uint8_t r = hex_to_byte(buffer[0], buffer[1]);
            uint8_t g = hex_to_byte(buffer[2], buffer[3]);
            uint8_t b = hex_to_byte(buffer[4], buffer[5]);

            set_rgb(r, g, b);
            uart_printstr(buffer);
            uart_printstr("\n\r");
            uart_printstr("Color set!\n\r");
        }
    }
}

void uart_printstr(const char* str) {
    while (*str) {
        while (!(UCSR0A & (1 << UDRE0)));
        UDR0 = *str++;
    }
}

uint8_t hex_to_byte(char high, char low) {
    uint8_t result = 0;
    
    if (high >= '0' && high <= '9') result += (high - '0') << 4;
    else if (high >= 'A' && high <= 'F') result += (high - 'A' + 10) << 4;
    else if (high >= 'a' && high <= 'f') result += (high - 'a' + 10) << 4;

    if (low >= '0' && low <= '9') result += (low - '0');
    else if (low >= 'A' && low <= 'F') result += (low - 'A' + 10);
    else if (low >= 'a' && low <= 'f') result += (low - 'a' + 10);

    return result;
}
