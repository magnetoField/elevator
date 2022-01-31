#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
//volatile  unsigned long last_interrupt_time = 0;
//volatile unsigned long interrupt_time = millis();
volatile boolean mojstate;



ISR (PCINT0_vect)
{
 cli();
 
 //sei();
  static unsigned long last_interrupt_time = 0;
  //delay(10);
 // delay(0.1);
  unsigned long  interrupt_time = millis();
   // delay(0.1);
  //interrupt_time = millis();
  //m=millis();
  //if (m - last_millis > 10)
  // { 
  //   PORTB ^= (1<<PB0);    // Toggling the PB2 pin
  //   PORTB ^= (1<<PB1);    // Toggling the PB2 pin
  // }

    if (interrupt_time - last_interrupt_time < 300 ) 
  {
    //PORTB ^= (1<<PB0);    // Toggling the PB2 pin
    //PORTB ^= (1<<PB1);    // Toggling the PB2 pin,
    //mojstate=false;
   
  } else
  {
    PORTB ^= (1<<PB1);    // Toggling the PB2 pin
  //  PORTB ^= (1<<PB3);    // Toggling the PB2 pin,
    
    mojstate=!mojstate;    // Toggling the PB2 pin,
    //delay(0.1);
  }
  delay(0.5);
  last_interrupt_time = interrupt_time+1;
  //last_millis = m;
 //sei();
 //cli();
}




void external_interrupt()
{
  DDRB |= (1<<PB1)|(1<<PB3);     // set PB2 as output(LED)
  PORTB |= (1<<PB0);
  sei();     //enabling global interrupt
  GIMSK |= (1<<PCIE);    // enabling the INT0 (external interrupt) 
  MCUCR |= (1<<ISC01);    // Configuring as falling edge 
  //MCUCR |=(1<<ISC01);
  PCMSK|=(1<<PCINT0);
  TIMSK &= ~(1<<TOIE0);
  //sei();
}


int main()
{
  external_interrupt();
  while(1)
  {
    delay(0.01);
    //sei();
        //last_interrupt_time = 0;
    if(mojstate){
     //  PORTB |=(1<<PB1)|(1<<PB3);
       PORTB ^= (1<<PB3);
    }
    
  }
}
