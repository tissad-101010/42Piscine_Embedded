#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


#define BAUD 115200
#define MYUBRR F_CPU/8/BAUD-1
#define BUF_SIZE 7

void init_rgb();
void set_rgb(uint8_t r, uint8_t g, uint8_t b);
void uart_init(unsigned int ubrr);
uint8_t uart_rx(void);
void uart_tx(uint8_t data);
void uart_printstr(const char* str);
uint8_t hex_to_byte(char high, char low);

static char buffer[BUF_SIZE]; // Stocke "#RRGGBB"
static uint8_t i = 0; // Index du buffer

int main(void) {
    init_rgb();
    uart_init(MYUBRR);
    uart_printstr("ships>");
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

void uart_init(unsigned int ubrr) {
    UCSR0A |= (1 << U2X0);
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0); 
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

uint8_t uart_rx(void) {
	while (!(UCSR0A & (1 << RXC0)))
		;
	return UDR0;
}

uint8_t uart_ishexdigit(uint8_t c) {
	return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f');
}

void valid_entry()
{
	uint8_t r = hex_to_byte(buffer[0], buffer[1]);
	uint8_t g = hex_to_byte(buffer[2], buffer[3]);
	uint8_t b = hex_to_byte(buffer[4], buffer[5]);
	set_rgb(r, g, b);
	uart_printstr(buffer);
	uart_printstr(" Color set!\n\r");
}

uint8_t enter_pressed(uint8_t c) {
	return (c == '\n' || c == '\r');
}

uint8_t backspace_pressed(uint8_t c) {
	return (c == 0x08 || c == 0x7F);
}



ISR(USART_RX_vect) {
	static uint8_t received = 0;

	uint8_t c = uart_rx();
	uart_tx(c);
	if (backspace_pressed(c)){
		if (i > 0){
			i--;
			uart_tx(0x08);
			uart_tx(' ');
			uart_tx(0x08);
		}
	}else if (enter_pressed(c) && i == BUF_SIZE - 1){
		buffer[i] = '\0';
		valid_entry();
		i = 0;
		uart_printstr("ships>");
		return;
	}
	else if (c == '#'){
		received = 1;
	}else if (received && uart_ishexdigit(c) && i < BUF_SIZE){
		buffer[i] = c;
		i++;
	}

	else{
		received = 0;
		i = 0;
		
		uart_printstr("\n\rInvalid format\n\r");
		uart_printstr("ships>");
	}
	
}

void uart_printstr(const char* str) {
    while (*str) {
        uart_tx(*str);
        str++;
    }
}
void uart_tx(uint8_t data) {
	
    while (!(UCSR0A & (1 << UDRE0)))// Wait until data register is empty
        ;
	// UCSR0A is the USART Control and Status Register A
	// UDRE0: USART Data Register Empty
	// UDR0 is the USART buffer
	// if UDRE0 is set, the buffer is empty and can be written to
    UDR0 = data;
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
