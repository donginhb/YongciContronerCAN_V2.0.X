/** 
 * <p>application name： Header.h</p> 
 * <p>application describing： 主函数宏定义</p> 
 * <p>copyright： Copyright (c) 2017 Beijing SOJO Electric CO., LTD.</p> 
 * <p>company： SOJO</p> 
 * <p>time： 2017.05.20</p> 
 * 
 * @updata:[日期YYYY-MM-DD] [更改人姓名][变更描述]
 * @author Zhangxiaomou 
 * @version ver 1.0
 */
#ifndef _Header_H_
#define _Header_H_

#define FCY 4e6


#include <libpic30.h>
//此处针对第三个控制器做一个全局判断，方便以后更改程序
//**************************************
#define SMALL_CHOSE 0xF1 
//#define BIG_CHOSE   0xF2

//**************************************
#ifdef	SMALL_CHOSE
    #define ADCS()  {ADCSSL = 0x000F;}  //ADC扫描通道数,AN0--AN3全部扫描
    #define ADPC()  {ADPCFG = 0xFFF0;}  //AN0--AN3
    #define CAP3_DROP_VOLTAGE() {g_SystemVoltageParameter.capDropVoltage3 = ADCBUF3 * LOCAL_CAP_MODULUS * g_SystemCalibrationCoefficient.capVoltageCoefficient3;}    
    #define CAP3_STATE  0xFF    //用于判断其是否被激活
    #define NUM_CHS2SCAN 4 //扫描几路ADC就相应的赋值即可
    #define CHECK_ORDER3()    (g_SwitchConfig[DEVICE_III].order == IDLE_ORDER)   
    #define CHECK_LAST_ORDER3()     ( g_SwitchConfig[DEVICE_III].alreadyAction == TRUE)
    #define MAC_ID (0x10)   //缺省A相

#elif BIG_CHOSE
    #define ADCS()  {ADCSSL = 0x0007;}  //ADC扫描通道数，扫描AN0--AN2
    #define ADPC()  {ADPCFG = 0xFFF8;}  //AN0--AN2
//在不使用第三个控制器时，使其变量值始终为0，方便函数CheckAllLoopCapVoltage（）的移植，以及状态更新
    #define CAP3_DROP_VOLTAGE() {g_SystemVoltageParameter.capDropVoltage3 = 0;}
    #define CAP3_STATE  0x00    //用于判断其是否被激活
    #define NUM_CHS2SCAN 3 //扫描几路ADC就相应的赋值即可
    #define CHECK_ORDER3()          (0xFF)
    #define CHECK_LAST_ORDER3()     (0x00)
    #define MAC_ID                  (0x10) //A-0x10   B-0x12  C-0x14
#endif
//**************************************

//**************************************
#if(CAP3_STATE)

#define LOOP_COUNT   3   //与下面的宏定义一起使用
#define LOOP_ID_ALL 0x07

#else

#define LOOP_COUNT  2   //与下面的宏定义一起使用
#define LOOP_ID_ALL 0x03

#endif

#define LOOP_ID_I   0x01
#define LOOP_ID_II  0x02
#define LOOP_ID_III 0x04
//**************************************

#include "Driver/tydef.h"
#include "Driver/AdcSample.h"
#include "Driver/DevicdIO.h"
#include "Driver/Usart.h"
#include "Driver/Timer.h"
#include "Driver/EEPROMOperate.h"
#include "Driver/CAN.h"
#include "Driver/InitTemp.h"
#include "Driver/Delay.h"
#include "Driver/ImitationIIC.h"
#include "Driver/SD2405.h"
#include "Driver/buffer.h"

#include "Yongci/SwtichCondition.h"
#include "Yongci/yongci.h"
#include "Yongci/DeviceParameter.h"

#include "SerialPort/Action.h"

#define LOCAL_ADDRESS   0xA2 //双路调试控制板子地址

#define LOCAL_CAP_MODULUS   0.125732421875f



//选择使用何种通信方式 判断开启何种中断
//**************************************
//#define USE_RS485 0xB2
#define USE_CAN 0xB1
#ifdef  USE_CAN
    #define ON_COMMUNICATION_INT()  {IEC2bits.C2IE = 1; C2INTE = 0xBF; C1INTE = 0;}  //C2INTE = 0xBF;
    #define OFF_COMMUNICATION_INT() {IEC2bits.C2IE = 0; C2INTE = 0; C1INTE = 0;}
    #define APPLY_CAN    TRUE
    #define APPLY_485    FALSE

#elif   USE_RS485
    #define ON_COMMUNICATION_INT()  {ON_UART_INT();}
    #define OFF_COMMUNICATION_INT() {OFF_UART_INT();}
    #define APPLY_CAN    FALSE
    #define APPLY_485    TRUE

#endif
//**************************************

#define OPEN_STATE    0x01  //机构分闸状态
#define CLOSE_STATE   0x02  //机构合闸状态
#define ERROR_STATE   0x03  //机构错误,分合位同时存在，或者同时不存在

extern uint8_t g_LastSwitchState[LOOP_COUNT];   //获取上一次开关分合位状态
extern uint8_t g_LastcapState[LOOP_COUNT];   //获取上一次开关分合位状态

#define Reset() {__asm__ volatile ("RESET");}

#endif
