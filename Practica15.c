
#include <18F4550.h>                             
#include <stdbool.h>
#fuses XT, NOPROTECT, NOPUT, NOWDT, NOLVP    // Incluye el microcontrolador con el que se va a trabajar
#use delay(clock=48Mhz, crystal)             // Tipo de oscilador y frecuencia dependiendo del microcontrolador
#build(reset = 0x02000, interrupt = 0x02008) // Asigna los vectores de reset e interrupci�n para la versi�n con bootloader
#org 0x0000, 0x1FFF {}
#define ENCENDER_LED bit_set(portD, 1)
#define APAGAR_LED bit_clear(portD, 1)
#define ENCENDER_LED1 bit_set(portD, 0)
#define APAGAR_LED2 bit_clear(portD, 0)
#BYTE PORTB = 0xf81
#BYTE PORTD = 0xF83
#USE FAST_IO(B)
bool foco = false;
#INT_EXT1
void PortB_Interrupt()
{
   output_toggle(pin_b0);
   for (int n = 1; n < 6; n++)
   {
      (foco == false) ? ENCENDER_LED : APAGAR_LED;
      delay_ms(500);
      foco = !foco;
   }
   foco = false;
   APAGAR_LED;
}
void main()
{
   set_tris_b(0b11111111); 
   set_tris_d(0b00000000);
   PORTB = 0;
   PORTD = 0;
   port_b_pullups(true);
   enable_interrupts(INT_EXT1);
   enable_interrupts(global);
   ext_int_edge(L_TO_H);
   

   while (1)
   {

      ENCENDER_LED1;
      delay_ms(1000);
      APAGAR_LED2;
      delay_ms(500);
   }
}

