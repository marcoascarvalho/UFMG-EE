/**************************************************************************/
/*        Comandos e procedimentos p/ LM629 - 629cmd.c                    */
/* Autor: Marco Antonio Santuci Carvalho                                  */
/* Ultima modificacao: 06/06/2000                                         */
/* Descricao: Esta biblioteca de funcoes implementa funcoes de uso        */
/*            do LM629 tais como leitura do byte de status e escritas no  */
/*            barramento de comando e dados.                              */
/**************************************************************************/

/**************************************************************************/
/*                 Declaração de constantes                               */
/**************************************************************************/
/* Constantes para o comando trajectory do LM629 */

// byte 1 (MSB)
#DEFINE VEL_MODE_AND_FRENTE                  0x01
#DEFINE VEL_MODE_AND_TRAS                    0x11
#DEFINE VEL_MODE_AND_MOTOR_OFF_AND_FRENTE    0x00
#DEFINE VEL_MODE_AND_MOTOR_OFF_AND_TRAS      0x10
#DEFINE POS_MODE                             0x09
#DEFINE POS_MODE_AND_MOTOR_OFF               0x08

// Word 2 (LSB)
#DEFINE LOAD_ACEL                 0X20
#DEFINE LOAD_ACEL_AND_VEL         0X28
#DEFINE LOAD_ACEL_AND_VEL_AND_POS 0X2A
#DEFINE LOAD_VEL                  0X08
#DEFINE LOAD_VEL_AND_POS          0X0A
#DEFINE LOAD_POS                  0X02

/* Constantes para o comando LFIL do LM629 */

#DEFINE LOAD_KP                   0X08
#DEFINE LOAD_KI                   0X04
#DEFINE LOAD_KD                   0X02
#DEFINE LOAD_KP_AND_KI            0X0C

/* Constantes de PWM */
#DEFINE PWM_8                     0X05
#DEFINE PWM_16                    0X06

/* Nome dos comandos */

#DEFINE  LFIL                     0x1E    // Load FILter
#DEFINE  STT                      0x01    // STarT
#DEFINE  LTRJ                     0x1F    // Load TRaJectory
#DEFINE  UDF                      0x04    // UpDate Filter
#DEFINE  RSTI                     0x1D    // ReSeT Interrupt
#DEFINE  RESET                    0x00    // Reset controler

/**************************************************************************/
/* Rotina para checar bit busy do lm629                                   */
/*                                                                        */
/* Descricao: esta rotina checa o valor do bit busy no registrador de     */
/*            status(bit 0).                                              */
/**************************************************************************/
boolean busy(boolean controler) // Le o bit busy
{
 return (read_status(controler)&0x01);
}

/**************************************************************************/
/* Rotina para atualização dos dados da trajetória                        */
/*                                                                        */
/* Descricao: esta rotina atualiza os parametros de trajetoria para cada  */
/*            LM629 através do comando LTRJ(0x1F). Depois é passado uma   */
/*            duas palavras de controle atraves das variaveis             */
/*            trjt_ctrl_byte_1 e trjt_ctrl_byte_2.                        */
/**************************************************************************/
void atualiza_set_point(byte trjt_ctrl_byte_1, byte trjt_ctrl_byte_2)
{

  // Controlador 1
  while(busy(CTRL1));
  LM629_write_command(CTRL1, LTRJ);     // LTRJ Command: Load Trajectory Parameters
  while(busy(CTRL1));
  LM629_write_data(CTRL1, trjt_ctrl_byte_1);
  LM629_write_data(CTRL1, trjt_ctrl_byte_2);

  while(busy(CTRL1));
  LM629_write_data(CTRL1, 0);
  LM629_write_data(CTRL1, 0);
  while(busy(CTRL1));
  LM629_write_data(CTRL1, 0);
  LM629_write_data(CTRL1, sp1_acel_serial);

  while(busy(CTRL1));
  LM629_write_data(CTRL1, 0);
  LM629_write_data(CTRL1, 0);
  while(busy(CTRL1));
  LM629_write_data(CTRL1, 0);
  LM629_write_data(CTRL1, sp1_vel_serial);

  while(busy(CTRL1));
  LM629_write_data(CTRL1, 0);
  LM629_write_data(CTRL1, 0);
  while(busy(CTRL1));
  LM629_write_data(CTRL1, 0);
  LM629_write_data(CTRL1, sp1_pos_serial);
  while(busy(CTRL1));


  // Controlador 2
  while(busy(CTRL2));
  LM629_write_command(CTRL2, LTRJ);     // LTRJ Command: Load Trajectory Parameters
  while(busy(CTRL2));
  LM629_write_data(CTRL2, trjt_ctrl_byte_1);        // carrega o 1 byte de configuracao
  LM629_write_data(CTRL2, trjt_ctrl_byte_2);        // carrega o 2 byte de configuracao

  while(busy(CTRL2));
  LM629_write_data(CTRL2, 0x00);
  LM629_write_data(CTRL2, sp2_acel_serial);
  while(busy(CTRL2));
  LM629_write_data(CTRL2, 0x00);
  LM629_write_data(CTRL2, 0x00);
  while(busy(CTRL2));

  while(busy(CTRL2));
  LM629_write_data(CTRL2, 0x00);
  LM629_write_data(CTRL2, sp2_vel_serial);
  while(busy(CTRL2));
  LM629_write_data(CTRL2, 0x00);
  LM629_write_data(CTRL2, 0x00);
  while(busy(CTRL2));

  while(busy(CTRL2));
  LM629_write_data(CTRL2, 0x00);
  LM629_write_data(CTRL2, sp2_pos_serial);
  while(busy(CTRL2));
  LM629_write_data(CTRL2, 0x00);
  LM629_write_data(CTRL2, 0x00);
  while(busy(CTRL2));

}

/**************************************************************************/
/* Rotina para movimentacao do motor                                      */
/*                                                                        */
/* Descricao: esta rotina executa o comando STT no controlador Lm629 que  */
/*            faz com os parametros de trajetoria pre carregados sejam    */
/*            executados.                                                  */
/**************************************************************************/
void run_motor()
{
  while(busy(CTRL1));
  LM629_write_command(CTRL1, STT);   // Start Motion Control - Comando STT
  while(busy(CTRL2));
  LM629_write_command(CTRL2, STT);   // Start Motion Control - Comando STT
}


/**************************************************************************/
/* Rotina para setar tamanho dos bits de PWM p/ motor                     */
/*                                                                        */
/* Descricao: esta rotina seta o tamanho da resolucao do PWM              */
/*            que ira sera enviado para o driver do motor. Os tamanhos    */
/*            possiveis são 8 e 16 bits                                   */
/**************************************************************************/
void seta_pwm(byte pwm_type)
{
   while(busy(CTRL1));
   LM629_write_command(CTRL1, pwm_type);
   while(busy(CTRL2));
   LM629_write_command(CTRL2, pwm_type);
}


/**************************************************************************/
/* Rotina para resetar o controlador LM629                                */
/*                                                                        */
/* Descricao: esta rotina reseta os controladores lm629 escrevendo 0x00   */
/*            na portas de comando.                                       */
/**************************************************************************/
void rst_controlador(void)
{
   while(busy(CTRL1));
   LM629_write_command(CTRL1, 0x00);
   while(busy(CTRL2));
   LM629_write_command(CTRL2, 0x00);
   delay_us(1500);             // Obrigatorio --> 1.5ms
}


/**************************************************************************/
/* Rotina para resetar interrupcao do LM629                               */
/*                                                                        */
/* Descricao: esta rotina reseta as interrupcoes do LM629                 */
/*                                                                        */
/**************************************************************************/
void reset_interrupt(byte irq)
{
  while(busy(CTRL1));
  LM629_write_command(CTRL1, RSTI);
  while(busy(CTRL1));
  LM629_write_data(CTRL1, 0x00);
  LM629_write_data(CTRL1, irq);
  while(busy(CTRL2));
  LM629_write_command(CTRL2, RSTI);
  while(busy(CTRL2));
  LM629_write_data(CTRL2, 0x00);
  LM629_write_data(CTRL2, irq);
}

/**************************************************************************/
/* Rotina para configuração dos ganhos dos controladores                  */
/*                                                                        */
/* Descricao: esta rotina carrega no controlador os ganhos kp, Ki e Kd    */
/*            através do comando LFIL(0x1E). No comando é passado uma     */
/*            palavra de configuração de 16 bits. Os primeiros 8 bits são */
/*            intervalos de amostragem do ganho derivativo e por enquanto */
/*            não sera utilizado. Os quatro bits menos significativos são */
/*            usados para informar ao controlador que ganho será          */
/*            carregado. O comando é aceito através da instrução Update   */
/*            Filter - UDF(0x04).                                         */
/**************************************************************************/
void carrega_ganhos(byte lfil_ctrl_byte_2)  //antigo configura()
{
  // Controlador 1
  while(busy(CTRL1));
  LM629_write_command(CTRL1, LFIL);     // LFIL Command: Load Filter Parameters
  while(busy(CTRL1));
  LM629_write_data(CTRL1, 0x00);
  LM629_write_data(CTRL1, lfil_ctrl_byte_2);   // byte de configuracao
  while(busy(CTRL1));
  LM629_write_data(CTRL1, 0x0F);          //  Carrega o valor
  LM629_write_data(CTRL1, kp);          //      de Kp
  while(busy(CTRL1));
  LM629_write_data(CTRL1, 0x0F);          //  Carrega o valor
  LM629_write_data(CTRL1, ki);          //      de Ki
  while(busy(CTRL1));
  LM629_write_command(CTRL1, UDF);      // Update Filter - comando UDF

  // Controlador 2
  while(busy(CTRL2));
  LM629_write_command(CTRL2, LFIL);     // LFIL Command: Load Filter Parameters
  while(busy(CTRL2));
  LM629_write_data(CTRL2, 0x00);
  LM629_write_data(CTRL2, lfil_ctrl_byte_2);   // byte de configuracao
  while(busy(CTRL2));
  LM629_write_data(CTRL2, 0x0F);          //  Carrega o valor
  LM629_write_data(CTRL2, kp);          //      de Kp
  while(busy(CTRL2));
  LM629_write_data(CTRL2, 0x0F);          //  Carrega o valor
  LM629_write_data(CTRL2, ki);          //      de Ki
  while(busy(CTRL2));
  LM629_write_command(CTRL2, UDF);      // Update Filter - comando UDF
}

/**************************************************************************/
/* Rotina para parar os motores                                           */
/*                                                                        */
/* Descricao: esta rotina programa os controladores para parar os motores */
/*                                                                        */
/**************************************************************************/
void stop_motor(void)
{

// Controlador 1
  while(busy(CTRL1));
  LM629_write_command(CTRL1, LTRJ);     // LTRJ Command: Load Trajectory Parameters
  while(busy(CTRL1));
  LM629_write_data(CTRL1, 0x00);        // 0000 Bit11=1(velocity mode) Bit8=0(Turn Off Motor)
  LM629_write_data(CTRL1, LOAD_ACEL_AND_VEL_AND_POS);        // 0000  PRA DESLIGAR O MOTOR BIT8=0!!!!!
  //while(busy(CTRL1));

while(busy(CTRL1));
  LM629_write_data(CTRL1, 0);
  LM629_write_data(CTRL1, 0);
  while(busy(CTRL1));
  LM629_write_data(CTRL1, 0);
  LM629_write_data(CTRL1, 0);

  while(busy(CTRL1));
  LM629_write_data(CTRL1, 0);
  LM629_write_data(CTRL1, 0);
  while(busy(CTRL1));
  LM629_write_data(CTRL1, 0);
  LM629_write_data(CTRL1, 0);

  while(busy(CTRL1));
  LM629_write_data(CTRL1, 0);
  LM629_write_data(CTRL1, 0);
  while(busy(CTRL1));
  LM629_write_data(CTRL1, 0);
  LM629_write_data(CTRL1, 0);
  while(busy(CTRL1));
  
  // Inicia o controle
  while(busy(CTRL1));
  LM629_write_command(CTRL1, STT);   // Start Motion Control - Comando STT


  // Controlador 2
  while(busy(CTRL2));
  LM629_write_command(CTRL2, LTRJ);     // LTRJ Command: Load Trajectory Parameters
  while(busy(CTRL2));
  LM629_write_data(CTRL2, 0x00);        // 1000 Bit11=1(velocity mode) Bit8=0(Turn Off Motor)
  LM629_write_data(CTRL2, 0x00);        // 0000  PRA DESLIGAR O MOTOR BIT8=0!!!!!
  //while(busy(CTRL2));


  while(busy(CTRL2));
  LM629_write_command(CTRL2, STT);   // Start Motion Control - Comando STT

}

/**************************************************************************/
/* Rotina para inicialização do LM629                                     */
/*                                                                        */
/* Descricao: esta rotina é necessária para inicializar o controlador.    */
/*            Primeiro é feito o reset por hardware atraves do pino de    */
/*            RESET(27). Depois é feito o reset por software. Depois      */
/*            o valor do registro de status eh checado e dependendo do    */
/*            seu valor(0x84 ou 0xC4) o reset é considerado OK. Esta      */
/*            rotina faz ainda o reset das interrupcoes do lm629.         */
/**************************************************************************/
void inicializa(void)
{
  boolean reset_ok;
  byte status;
  output_high(LM629_RESET);
  reset_ok=FALSE;
  output_low(LM629_RESET);
  //rst_controlador();
  while(!reset_ok)   // Faz o reset dos controladores
    {
      status=read_status(CTRL1);
      if ((status==0x84)||(status==0xC4)) // 0x84 - Bit7=1(Motor Off) Bit2=1(Trajectory Complete)
        {                                 // 0xC4 - Bit7=1(Motor Off) Bit6=1(Breakpoint Reached)
          reset_ok=TRUE;                  //        Bit 2=1(Trajectory Complete)
          status=read_status(CTRL2);
          if (!((status==0x84)||(status==0xC4)))
              reset_ok=TRUE;
         }
      if (!reset_ok)
         {
          output_low(LM629_RESET);
          delay_us(10);                 // Tem que esperar pelo menos 8 pulsos de clock
          output_high(LM629_RESET);
          delay_us(1500);               // Obrigatorio--> 1.5ms
         }
     }
   output_high(LM629_RESET);
   rst_controlador();
   seta_pwm(PWM_8);
   reset_interrupt(0x00);
   acende_led_verde();
   delay_ms(10);
   apaga_led_verde();
   stop_motor();
}


/**************************************************************************/
/* Rotina para codificar posicao recebida                                 */
/*                                                                        */
/* Descricao: esta rotina codifica o setpoint de posicao que eh recebido  */
/*            pela serial                                                 */
/*                                                                        */
/**************************************************************************/
void codifica_posicao(byte sp1, byte sp2)
{

   //sp1_pos_serial=RESOLUCAO*sp1;
   //sp2_pos_serial=RESOLUCAO*sp2;

}

/**************************************************************************/
/* Rotina para codificar velocidade recebida                              */
/*                                                                        */
/* Descricao: esta rotina codifica o setpoint de velocidade que eh        */
/*            recebido pela serial                                        */
/*                                                                        */
/**************************************************************************/
void codifica_velocidade(byte sp1, byte sp2)
{

   //sp1_vel_serial=(float)RESOLUCAO*sp1;
   //sp2_vel_serial=(float)RESOLUCAO*sp2;

}

