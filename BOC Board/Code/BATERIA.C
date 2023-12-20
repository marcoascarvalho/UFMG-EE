
/**************************************************************************/
/*        Rotinas para tratamento da medicao de bateria - bateria.c       */
/* Autor: Marco Antonio Santuci Carvalho                                  */
/* Ultima modificacao: 23/05/2000                                         */
/**************************************************************************/

/**************************************************************************/
/* Rotina p/ verificar nivel de tensao na bateria                         */
/*                                                                        */
/* Descricao: esta rotina verifica a tensao na bateria atraves da leitura */
/*            do canal 0(pino RA0) do conversor A/D do PIC. Retorna TRUE  */
/**************************************************************************/
void bateria(void)
{
   int value;

     set_adc_channel( 0 );
     value=read_adc();
     if (value>102) {  // 102= (5.75V/2/7.2V)*256
         lowbat=FALSE;
         output_high(LED1_RED);     // Apaga Led vermelho
         }
     else  lowbat=TRUE;
}

void battery_check(void)
{

bateria();
if (lowbat)
   {                      // Se bateria boa(>5.75V)
   output_low(LED1_RED);  // Acende Led vermelho
   }//if

}
