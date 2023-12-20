/**************************************************************************/
/*        Rotinas de controle LM629 - 629ctrl.c                           */
/* Autor: Marco Antonio Santuci Carvalho                                  */
/* Ultima modificacao: 20/05/2000                                         */
/* Descricao: Esta biblioteca de funcoes implementa funcoes de uso        */
/*            do LM629 tais como leitura do byte de status e escritas no  */
/*            barramento de comando e dados.                              */
/**************************************************************************/

/**************************************************************************/
/* Rotina de leitura do byte de status do LM629                           */
/*                                                                        */
/* Descricao: esta rotina faz a leitura do byte de status do LM629 de     */
/*            acordo com o controlador passado para a funcao. O byte de   */
/*            Status indica:                                              */
/*            Bit 7 - Motor Off                                           */
/*            Bit 6 - Breakpoint Reached(Interrupt)                       */
/*            Bit 5 - Excessive Position Error(Interrupt)                 */
/*            Bit 4 - Wraparound Ocurred(Interrupt)                       */
/*            Bit 3 - Index Pulse Observed(Interrupt)                     */
/*            Bit 2 - Trajectory Complete(Interrupt)                      */
/*            Bit 1 - Command Error(Interrupt)                            */
/*            Bit 0 - Busy Bit                                            */
/**************************************************************************/
byte read_status(boolean controler)  // Le o byte de estatus
{
   byte status;
   if (controler){
      output_high(LM629_CS2);      // Desabilita o controlador 2
      output_low(LM629_CS1);       // Habilita o controlador 1
      }
   else{
      output_high(LM629_CS1);      // Desabilita o controlador 1
      output_low(LM629_CS2);       // Habilita o controlador 2
      }
   output_low(LM629_PS);
   output_low(LM629_RD);
   SET_TRIS_D(0xFF);         // PortD=input
   status=dados;
   output_high(LM629_RD);
   output_high(LM629_PS);
   output_high(LM629_CS1);
   output_high(LM629_CS2);

   return status;
}


/**************************************************************************/
/* Rotina de escrita de comandos no LM629                                 */
/*                                                                        */
/* Descricao: esta rotina escreve uma instrucao na porta de comando do    */
/*            LM629. A seguinte sequencia eh utilizada:                   */
/*            LM629_PS=0 (Port status = 0 --> comando);                         */
/*            LM629_WR=0; CS=0.                                                 */
/**************************************************************************/
void LM629_write_command(boolean controler, byte byte1)
{
  if (controler){
      output_high(LM629_CS2);      // Desabilita o controlador 2
      output_low(LM629_CS1);       // Habilita o controlador 1
      }
   else{
      output_high(LM629_CS1);      // Desabilita o controlador 1
      output_low(LM629_CS2);       // Habilita o controlador 2
      }
   output_low(LM629_PS);
   SET_TRIS_D(0x00);         // PortD = Output
   dados=byte1;
   output_low(LM629_WR);
   output_high(LM629_WR);
   output_high(LM629_PS);
   output_high(LM629_CS1);
   output_high(LM629_CS2);
}


/**************************************************************************/
/* Rotina de escrita de dados no LM629                                    */
/*                                                                        */
/* Descricao: esta rotina escreve uma instrucao na porta de dados do      */
/*            LM629. A seguinte sequencia eh utilizada:                   */
/*            LM629_PS=1 (Port status = 1 --> dado);                            */
/*            LM629_WR=0; CS=0.                                                 */
/**************************************************************************/
void LM629_write_data(boolean controler, byte byte1)
{
   if (controler){
      output_high(LM629_CS2);      // Desabilita o controlador 2
      output_low(LM629_CS1);       // Habilita o controlador 1
      }
   else{
      output_high(LM629_CS1);      // Desabilita o controlador 1
      output_low(LM629_CS2);       // Habilita o controlador 2
      }
   output_high(LM629_PS);
   SET_TRIS_D(0x00);         // PortD = Output
   dados=byte1;
   output_low(LM629_WR);
   output_high(LM629_WR);
   output_high(LM629_CS1);
   output_high(LM629_CS2);
}
