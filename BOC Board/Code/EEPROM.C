/**************************************************************************/
/*        Comandos e procedimentos p/ LM629 - eeprom.c                    */
/* Autor: Marco Antonio Santuci Carvalho                                  */
/* Ultima modificacao: 23/05/2000                                         */
/* Descricao: Esta biblioteca de funcoes implementa funcoes de escrita    */
/*            e leitura dos ganhos na memoria EEPROM.                      */
/*                                                                        */
/**************************************************************************/



/**************************************************************************/
/* Rotina para salvar ganhos na EEPROM                                    */
/*                                                                        */
/* Descricao:  salva os ganhos do controlador na EEPROM                  */
/*                                                                        */
/**************************************************************************/
void salva_ganhos_EEPROM(void)
{
  WRITE_EXT_EEPROM( 0x1, kp );
  WRITE_EXT_EEPROM( 0x2, ki );
  //WRITE_EXT_EEPROM( 0x3, kd );
}

/**************************************************************************/
/* Rotina para ler ganhos da EEPROM                                       */
/*                                                                        */
/* Descricao: le os ganhos kp, ki e kd da EEPROM                          */
/*                                                                        */
/**************************************************************************/
void le_ganhos_EEPROM(void)
{
  id=READ_EXT_EEPROM( 0x0 );
  kp=READ_EXT_EEPROM( 0x1 );
  ki=READ_EXT_EEPROM( 0x2 );
 // kd=READ_EXT_EEPROM( 0x3 );
 output_low(LED2_YELLOW);           // Acende Led amarelo
}
