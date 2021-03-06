/** 
 * <p>application name： yongci.h.c</p> 
 * <p>application describing： 永磁控制器主要逻辑</p> 
 * <p>copyright： Copyright (c) 2017 Beijing SOJO Electric CO., LTD.</p> 
 * <p>company： SOJO</p> 
 * <p>time： 2017.05.20</p> 
 * 
 * @updata:[日期YYYY-MM-DD] [更改人姓名][变更描述]
 * @author Zhangxiaomou 
 * @version ver 1.0
 */

#ifndef XC_YONGCI_H
#define	XC_YONGCI_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "../Driver/tydef.h"

#define RUN_STATE   0x77    //运行状态
#define READY_STATE 0x88    //准备状态
    
//远方就地
#define YUAN_STATE  0xA1    //远方状态
#define BEN_STATE   0xA5    //就地状态
    
    
//工作模式和调试模式
#define WORK_STATE  0x3F    //工作状态
#define DEBUG_STATE 0xCF    //调试状态
    
#define IDLE_ORDER   0x0000     //空闲命令

#define HEZHA_TIME  50 //合闸时间 默认
#define FENZHA_TIME 30 //分闸时间 默认

#define NO_ERROR    0x00
    
//IGBT工作状态
#define HE_ORDER  0xAAAA  //执行同时合闸动作
#define FEN_ORDER 0xAA55  //执行同时分闸动作
    
//以下用于按键
#define CHECK_1_HE_ORDER  0xAA24  //执行机构1合闸动作
#define CHECK_1_FEN_ORDER 0xAA25  //执行机构1分闸动作
    
#define CHECK_2_HE_ORDER  0xAA26  //执行机构2合闸动作
#define CHECK_2_FEN_ORDER 0xAA27  //执行机构2分闸动作
    
#define CHECK_3_HE_ORDER  0xAA28  //执行机构3合闸动作
#define CHECK_3_FEN_ORDER 0xAA29  //执行机构3分闸动作

//************************************************
//拒动错误值
#define HE_ERROR      0xB2    //合拒动错误
#define FEN_ERROR     0xB3    //分拒动错误
//************************************************

#define ON_LOCK     0xAA55    
#define OFF_LOCK    0x0000

/**
 * 结构代号
 */    
#define  DEVICE_I  0
#define  DEVICE_II 1

#if(CAP3_STATE)
#define  DEVICE_III 2
#endif
  
 /**
  * 分合闸控制
  */
typedef struct TagSwitchConfig
{
	uint8_t   currentState;	//当前的状态
    uint8_t   alreadyAction;   //是否已经动作了
	uint16_t  order;	//分合闸命令
    uint16_t  lastOrder;  //上一次执行的指令
	uint16_t  powerOnTime;   //合闸动作时间
	uint16_t  powerOffTime;	//分闸动作时间
	uint16_t  offestTime;	//偏移时间
	uint32_t  systemTime;      //当前的系统时间
	void (*SwitchClose)(struct  TagSwitchConfig* );     //开关合闸动作函数
	void (*SwitchOpen)(struct TagSwitchConfig* );    //开关分闸动作函数
}SwitchConfig;

void YongciMainTask(void);
void YongciFirstInit(void);

void SingleCloseOperation(uint8_t index,uint16_t time);
void SingleOpenOperation(uint8_t index,uint16_t time);

uint8_t GetOffestTime(struct DefFrameData* pReciveFrame);
void OnLock(void);
void OffLock(void);
uint8_t CheckLockState(void);
void SynCloseAction(void);
void CloseOperation(void);
void OpenOperation(void);
void UpdateCount(void);
extern uint16_t _PERSISTENT g_Order;  //需要执行的命令,在单片机发生复位的情况下该值依然可以保存
extern SwitchConfig g_SwitchConfig[LOOP_COUNT];	//配置机构状态

#ifdef	__cplusplus
}
#endif

#endif	/* YONGCI_H */

