 /**************************************************************************/
/*        Programa cabecalho BOCBoard - main.h                            */
/* Autor: Marco Antonio Santuci Carvalho                                  */
/* Ultima modificacao: 30/05/2000                                         */
/* Descricao: este é o programa de cabecalho que controla a placa         */
/* BOCboard. Contem definicao de constantes e nome de pinos.              */
/*                                                                        */
/**************************************************************************/

#device PIC16C74A
#use delay(clock=20000000)
#nolist

/**************************************************************************/
/*                       Definicao dos pinos                              */
/* Descricao: Esta parte do programa descreve a configuracao dos pinos.   */
/*            Duas possibilidades estao presentes:                        */
/*            - a primeira é a default que é a dos pinos do portA         */
/*              configurados como analógicos. Neste caso o LM629_CS1 deve */
/*              ser colocado no pino RES3 (RC3-->16) e o pino RA3(5) nao  */
/*              podera ser utilizado.                                     */
/*            - A segunda possibilidade sao todos os pinos configurados   */
/*              como I/O digitais. Neste caso nenhum pino podera ser      */
/*              utilizado com entrada analogica.                          */
/**************************************************************************/
#define LED3_GREEN  42

/***********************************************************************/
/*                 configuracao dos pinos port_A como analogicos       */
/***********************************************************************/
#if 1
#define BATLOW  0
#define RES1  1
#define NOT_USED  3
#define LM629_CS1  57

/***********************************************************************/
/*                 configuracao dos pinos port_A como I/O digitais     */
/***********************************************************************/
#else
#define BATLOW  40
#define RES1  41
#define LM629_CS1  43
#define RES3  57
#byte port_A=5
#endif

#define RES2  44
#define LM629_RD  45


#define RES4  48
#define LED1_RED  49
#define LED2_YELLOW  50
#define RDMT_CD_PGM  51
#define LM629_HI2  52
#define LM629_HI1  53
#define RDMT_RXSEL_PGC  54
#define RDMT_TXSEL_PGD  55
#byte port_B=6

#define LM629_CS2  56

#define LM629_RESET  58
#define EEPROM_CLK  59
#define EEPROM_DI  60
#define EEPROM_DO  61
#define RDMT_TX  62
#define RDMT_RX  63
#byte port_C=7

#define D0  64
#define D1  65
#define D2  66
#define D3  67
#define D4  68
#define D5  69
#define D6  70
#define D7  71
#byte DADOS=8   // dados= 1 byte do endereco 0x08h --> port D

#define LM629_WR  72
#define LM629_PS  73
#define EEPROM_SELECT  74
#use fixed_io(E_OUTPUTS=LM629_WR,LM629_PS,EEPROM_SELECT)
#byte port_E=9

/***********************************************************************/
/*                 configuracao da porta serial                        */
/***********************************************************************/

#use rs232(baud=9600 ,xmit=RDMT_TX,rcv=RDMT_RX)


/***********************************************************************/
/*                 definicao de constantes                             */
/***********************************************************************/
#define FALSE 0
#define TRUE 1

#define BYTE int
#define BOOLEAN short int

#define getc getch
#define getchar getch
#define puts(s) {printf(s); putchar(13); putchar(10);}
#define putc putchar

/***********************************************************************/
/*                 Constants used for RESTART_CAUSE()                  */
/***********************************************************************/

#define WDT_FROM_SLEEP  0
#define WDT_TIMEOUT     8
#define MCLR_FROM_SLEEP 16
#define NORMAL_POWER_UP 24

/***********************************************************************/
/*                 Constants used for SETUP_COUNTERS()                 */
/***********************************************************************/

#define RTCC_INTERNAL   0
#define RTCC_EXT_L_TO_H 32
#define RTCC_EXT_H_TO_L 48
#define RTCC_DIV_2      0
#define RTCC_DIV_4      1
#define RTCC_DIV_8      2
#define RTCC_DIV_16     3
#define RTCC_DIV_32     4
#define RTCC_DIV_64     5
#define RTCC_DIV_128    6
#define RTCC_DIV_256    7
#define WDT_18MS        8
#define WDT_36MS        9
#define WDT_72MS       10
#define WDT_144MS      11
#define WDT_288MS      12
#define WDT_576MS      13
#define WDT_1152MS     14
#define WDT_2304MS     15
#define L_TO_H              0x40
#define H_TO_L                 0

#define RTCC_ZERO           0x0B20    // Used for ENABLE/DISABLE INTERRUPTS
#define RB_CHANGE           0x0B08    // Used for ENABLE/DISABLE INTERRUPTS
#define EXT_INT             0x0B10    // Used for ENABLE/DISABLE INTERRUPTS

#define GLOBAL              0x0BC0    // Used for ENABLE/DISABLE INTERRUPTS


/***********************************************************************/
/*                 Constantes utilizadas pelo Timer 1 e timer 2        */
/***********************************************************************/

#define T1_DISABLED         0
#define T1_INTERNAL         5
#define T1_EXTERNAL         7
#define T1_EXTERNAL_SYNC    3
#define T1_CLK_OUT          8
#define T1_DIV_BY_1         0
#define T1_DIV_BY_2         0x10
#define T1_DIV_BY_4         0x20
#define T1_DIV_BY_8         0x30
#byte   TIMER_1_LOW=        0x0e
#byte   TIMER_1_HIGH=       0x0f
#define T2_DISABLED         0
#define T2_DIV_BY_1         4
#define T2_DIV_BY_4         5
#define T2_DIV_BY_16        6
#byte   TIMER_2=            0x11

#define INT_TIMER1          0x8C01    // Used for ENABLE/DISABLE INTERRUPTS
#define INT_TIMER2          0x8C02    // Used for ENABLE/DISABLE INTERRUPTS



/***********************************************************************/
/*                 Constants used for SETUP_CCP1()                     */
/***********************************************************************/

#define CCP_OFF                         0
#define CCP_CAPTURE_FE                  4
#define CCP_CAPTURE_RE                  5
#define CCP_CAPTURE_DIV_4               6
#define CCP_CAPTURE_DIV_16              7
#define CCP_COMPARE_SET_ON_MATCH        8
#define CCP_COMPARE_CLR_ON_MATCH        9
#define CCP_COMPARE_INT                 0xA
#define CCP_COMPARE_RESET_TIMER         0xB
#define CCP_PWM                         0xC
#define CCP_PWM_PLUS_1                  0x1c
#define CCP_PWM_PLUS_2                  0x2c
#define CCP_PWM_PLUS_3                  0x3c
#byte   CCP_1_LOW=                      0x15
#byte   CCP_1_HIGH=                     0x16

#define INT_CCP1            0x8C04    // Used for ENABLE/DISABLE INTERRUPTS

/***********************************************************************/
/*                 Constants used for SETUP_CCP2()                     */
/***********************************************************************/

#byte   CCP_2_LOW=                      0x1B
#byte   CCP_2_HIGH=                     0x1C
#define INT_CCP2            0x8D01    // Used for ENABLE/DISABLE INTERRUPTS

/***********************************************************************/
/*                 Constants used for SETUP_PSP()                     */
/***********************************************************************/

#define PSP_ENABLED                     0x10
#define PSP_DISABLED                    0
#byte   PSP_DATA=                       8
#define INT_PSP             0x8C80    // Used for ENABLE/DISABLE INTERRUPTS

/***********************************************************************/
/*                 Constants used in SETUP_SSP()                       */
/***********************************************************************/

#define SPI_MASTER       0x20
#define SPI_SLAVE        0x24
#define SPI_L_TO_H       0
#define SPI_H_TO_L       0x10
#define SPI_CLK_DIV_4    0
#define SPI_CLK_DIV_16   1
#define SPI_CLK_DIV_64   2
#define SPI_CLK_T2       3
#define SPI_SS_DISABLED  1
#define INT_SSP             0x8C08    // Used for ENABLE/DISABLE INTERRUPTS

#define INT_SSP             0x8C08    // Used for ENABLE/DISABLE INTERRUPTS

#define INT_RDA             0x8C20    // Used for ENABLE/DISABLE INTERRUPTS
#define INT_TBE             0x8C10    // Used for ENABLE/DISABLE INTERRUPTS

/***********************************************************************/
/*                 Constants used for SETUP_ADC()                      */
/***********************************************************************/

#define ALL_ANALOG             0
#define ANALOG_RA3_REF         1
#define A_ANALOG               2
#define A_ANALOG_RA3_REF       3
#define RA0_RA1_RA3_ANALOG     4
#define RA0_RA1_ANALOG_RA3_REF 5
#define NO_ANALOGS             6
#define ADC_OFF                0
#define ADC_CLOCK_DIV_2        1
#define ADC_CLOCK_DIV_8     0x41
#define ADC_CLOCK_DIV_32    0x81
#define ADC_CLOCK_INTERNAL  0xc1

#define ADC_DONE            0x8C40    // Used for ENABLE/DISABLE INTERRUPTS

#list
