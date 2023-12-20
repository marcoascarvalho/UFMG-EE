/**************************************************************************/
/*        Rotinas para sinalizacao atraves dos leds - leds.c              */
/* Autor: Marco Antonio Santuci Carvalho                                  */
/* Ultima modificacao: 05/06/2000                                         */
/**************************************************************************/

#DEFINE TIME_LED 500

#INLINE
acende_led_vermelho()
{
 output_low(LED1_RED); 
}

apaga_led_vermelho()
{
 output_high(LED1_RED);
} 

acende_led_amarelo()
{
 output_low(LED2_YELLOW); 
}

apaga_led_amarelo()
{
 output_high(LED2_YELLOW);
} 

acende_led_verde()
{
 output_low(LED3_GREEN); 
}

apaga_led_verde()
{
 output_high(LED3_GREEN);
} 

/***********************************************************************/
/*                 Rotina para apagar leds                             */
/***********************************************************************/
void leds_off(void)
{
 output_high(LED1_RED);   // Led 1
 output_high(LED2_YELLOW);   // Led 2
 output_high(LED3_GREEN);   // Led 3
}

/***********************************************************************/
/*                 Rotina para acender leds                            */
/***********************************************************************/
void leds_on(void)
{
  output_low(LED1_RED);    // Led 1
  output_low(LED2_YELLOW);    // Led 2
  output_low(LED3_GREEN);    // Led 3
}

/***********************************************************************/
/*                 Rotina de inicializacao com leds                     */
/***********************************************************************/

void inicia_leds(void)
{
 leds_off();
 delay_ms(TIME_LED);
 leds_on();
 delay_ms(TIME_LED);
 leds_off();
 delay_ms(TIME_LED);
 leds_on();
 delay_ms(TIME_LED);
 leds_off();
 delay_ms(TIME_LED);
 }
 
