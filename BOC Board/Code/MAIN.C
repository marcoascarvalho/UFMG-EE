/**************************************************************************/
/*        Programa principal BOCBoard - main.c                            */
/* Autor: Marco Antonio Santuci Carvalho                                  */
/* Ultima modificacao: 08/06/2000                                         */
/* Descricao: este é o programa principal que controla a placa BOCboard   */
/*                                                                        */
/*                                                                        */
/**************************************************************************/

#INCLUDE "MAIN.H"
#INCLUDE "9366.C"


/***********************************************************************/
/*             Declaração das Variáveis Globais                        */
/***********************************************************************/

 byte id;                   // Identificacao do robo-> lido na EEPROM
 byte i, contbyte;          // Contadores
 byte serial;
 boolean lowbat;            // Flag de bateria
 boolean notrx;             // Flag de falta de dado
 boolean wrongdata;         // Flag de dado errado
 boolean setpoint;          // Flag de dado setpoint ou parametros
 boolean pisca=0;
 byte kp, ki, kd;           // Ganhos do Controlador

 byte sp1_acel_serial, sp1_vel_serial, sp1_pos_serial,
      sp2_acel_serial, sp2_vel_serial, sp2_pos_serial; // Set-Points dos motores programado vindos da serial

 //float sp1_pos, sp2_pos;    // Set point de posicao a ser enviado para o LM629

 //long int sp1_vel, sp2_vel, sp1_acel, sp2_acel; // set point de velocidade e aceleracao a ser enviado para LM629

 BYTE time_exec;
/**********************************************************************/

/***********************************************************************/
/*                 Declaração de constantes                            */
/***********************************************************************/
#DEFINE CTRL1   1
#DEFINE CTRL2   0

#DEFINE ALL_IN   0XFF
#DEFINE ALL_OUT  0X00

#DEFINE N_LINHAS_ENCODER 16
#DEFINE RESOLUCAO  N_LINHAS_ENCODER*4

#DEFINE MAX_TIME 100;

#INCLUDE "bateria.c"
#INCLUDE "leds.c"
#INCLUDE "629ctrl.c"
#INCLUDE "629cmd.c"
#INCLUDE "eeprom.c"
#INCLUDE "serial.c"

#use fast_io(D)  // diretiva para PORTD ficar mais rapido

/***********************************************************************/
/*                          Interrupcoes                               */
/***********************************************************************/

// Timer0 (RTCC) overflow
#int_rtcc
rtcc_isr() {
        //battery_check();
        if(--time_exec==0)
        {
         output_high(LED1_RED);
         delay_ms(100);
         output_low(LED1_RED);
         time_exec=MAX_TIME;
        }
}

// Async Serial Data In
/*#int_rda
rda_isr() {

    //recebe_dados();

       disable_interrupts(GLOBAL);
       output_low(LED3_GREEN);            // Acende Led verde
       delay_ms(10);
       output_high(LED3_GREEN);           // Apaga Led verde
       dados=getc();
       enable_interrupts(INT_TIMER1);
       enable_interrupts(INT_RDA);
	    enable_interrupts(GLOBAL);

}*/


/***********************************************************************/
/*                            Função MAIN                              */
/***********************************************************************/

main() {

/***********************************************************************/
/*                     Configuração do PIC                             */
/***********************************************************************/
   set_rtcc(0);
	setup_counters(RTCC_INTERNAL,RTCC_DIV_256); //Timer 0 c/ clock interno div/256--> estouro a cada 65.53ms

   setup_port_a(RA0_RA1_RA3_ANALOG);
   setup_adc(ADC_CLOCK_INTERNAL);


   enable_interrupts(RTCC_ZERO);     // habilita interrupcao Timer0
	//enable_interrupts(INT_RDA);       // habilita interrupcao porta serial
	enable_interrupts(GLOBAL);        // habilita interrupcao Global

   //disable_interrupts(GLOBAL);

   port_b_pullups(TRUE);             // habilita resistores pull ups PortB

   init_ext_eeprom();                // Procedimento de inicializacao da memoria EEPROM

   SET_TRIS_D(ALL_OUT);    // PORTD = Output

   output_high(LM629_CS1);    //
   output_high(LM629_CS2);    //
   output_high(LM629_RD);     //  Desabilita pinos de controle
   output_high(LM629_WR);     //
   output_high(LM629_PS);     //

/***********************************************************************/
/*                     Boot da placa                                   */
/***********************************************************************/

inicializa();

//teste da interrupcao
time_exec=MAX_TIME;

kp=0xFF;
ki=0xFF;
//carrega_ganhos(LOAD_KP_AND_KI);

delay_ms(2000);

acende_led_amarelo();
stop_motor();
stop_motor();

delay_ms(2000);

//sp1_acel_serial=0xF0;
//sp2_acel_serial=0XF0;

//sp1_vel_serial=0XFF;
//sp2_vel_serial=0XFF;

//sp1_pos_serial=0XFF;
//sp2_pos_serial=0XFF;

//inicia_leds();

//carrega_ganhos(LOAD_KP_AND_KI);
//stop_motor();
//delay_ms(1000);
//atualiza_set_point(VEL_MODE_AND_MOTOR_OFF_AND_FRENTE,LOAD_ACEL_AND_VEL_AND_POS);
//run_motor();

apaga_led_amarelo();

sp1_acel_serial=0X0F;
sp2_acel_serial=0XFF;

sp1_vel_serial=0X03;
sp2_vel_serial=0X01;

carrega_ganhos(LOAD_KP_AND_KI);
delay_ms(1);
atualiza_set_point(VEL_MODE_AND_TRAS ,LOAD_ACEL_AND_VEL);
delay_ms(1);
run_motor();

acende_led_verde();

delay_ms(5000);
stop_motor();
delay_ms(5000);

carrega_ganhos(LOAD_KP_AND_KI);
delay_ms(1);
atualiza_set_point(VEL_MODE_AND_FRENTE,LOAD_ACEL_AND_VEL);
delay_ms(1);
run_motor();


apaga_led_verde();

stop_motor();
while(1);
}


