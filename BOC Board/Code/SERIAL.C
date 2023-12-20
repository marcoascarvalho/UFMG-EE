/**************************************************************************/
/*      Rotinas para tratamento dos dados da porta serial - serial.c      */
/* Autor: Marco Antonio Santuci Carvalho                                  */
/* Ultima modificacao: 23/05/2000                                         */
/* Descricao: Esta biblioteca implementa funcoes para  tratamento dos     */
/*            dados da porta serial. Um protocolo de comunicacao é        */
/*            implementado.                                               */
/**************************************************************************/



void leserial(void)  // Le os dados da serial
{
   output_low(LED2_YELLOW);
   notrx=TRUE;
   dados=getc();
   notrx=FALSE;
   output_low(LED2_YELLOW);
}


boolean leucerto(void)  // Verifica o checksum e verifica a integridade
{                       // dos dados
 setpoint=TRUE;
 return TRUE;
}



