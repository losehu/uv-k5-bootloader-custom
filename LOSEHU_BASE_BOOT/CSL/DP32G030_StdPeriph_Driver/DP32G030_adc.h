#ifndef __DP32G030_ADC_H__
#define __DP32G030_ADC_H__

#include "DP32G030.h"


#define ADC_CH0		0x01
#define ADC_CH1		0x02
#define ADC_CH2		0x04
#define ADC_CH3		0x08
#define ADC_CH4		0x10
#define ADC_CH5		0x20
#define ADC_CH6		0x40
#define ADC_CH7		0x80
#define ADC_CH8		0x100
#define ADC_CH9		0x200
#define ADC_CH10    0x400
#define ADC_CH11    0x800
#define ADC_CH12    0x1000
#define ADC_CH13	0x2000
#define ADC_CH14	0x4000
#define ADC_CH15	0x8000


typedef enum
{ 
	CLK_DIV_1 =  0x00,       //ADC时钟是系统时钟1分频
	CLK_DIV_2 =  0x01,       //ADC时钟是系统时钟2分频
    CLK_DIV_4 =  0x02,       //ADC时钟是系统时钟4分频
	CLK_DIV_8 =  0x03        //ADC时钟是系统时钟8分频
} ADC_Clk_Div_TypeDef;

typedef enum
{ 
	SAMP_AVG_1 =  0x00,       //1次采样取平均
	SAMP_AVG_2 =  0x01,       //2次采样取平均
    SAMP_AVG_4 =  0x02,       //4次采样取平均
	SAMP_AVG_8 =  0x03        //8次采样取平均
} ADC_SampAvg_TypeDef;


typedef enum
{
	SAMP_MODE_SINGLE    =  0x00,   //ADC单次采样
	SAMP_MODE_CONTINUE  =  0x01    //ADC连续采样
} ADC_Samp_Mode_TypeDef;


typedef enum
{ 
	MODE_FIFO =  0x00,       //ADC数据存储为FIFO模式
	MODE_CHAN =  0x01        //ADC数据存储为通道模式
} ADC_Mode_TypeDef;


typedef enum
{
	SAMP_CLK_EXT =  0x00,    //ADC采用外部采样时钟方式
	SAMP_CLK_IN  =  0x01     //ADC采用内部采样时钟方式
} ADC_Samp_Clk_TypeDef;


typedef enum
{
	EXTSAMP_CLKWIN_1   =  0x00,   //外部采样时钟方式采样窗口1*CLK
	EXTSAMP_CLKWIN_2   =  0x01,   //外部采样时钟方式采样窗口2*CLK
	EXTSAMP_CLKWIN_4   =  0x02,   //外部采样时钟方式采样窗口4*CLK
	EXTSAMP_CLKWIN_8   =  0x03,   //外部采样时钟方式采样窗口8*CLK
	EXTSAMP_CLKWIN_16  =  0x04,   //外部采样时钟方式采样窗口16*CLK
	EXTSAMP_CLKWIN_32  =  0x05,   //外部采样时钟方式采样窗口32*CLK
	EXTSAMP_CLKWIN_64  =  0x06,   //外部采样时钟方式采样窗口64*CLK
	EXTSAMP_CLKWIN_128 =  0x07    //外部采样时钟方式采样窗口128*CLK
} ExtSamp_ClkWin_TypeDef;

typedef enum
{
	INSAMP_CLKWIN_1  =  0x00,   //内部采样时钟方式采样窗口1*CLK
	INSAMP_CLKWIN_3  =  0x01,   //内部采样时钟方式采样窗口3*CLK
	INSAMP_CLKWIN_5  =  0x02,   //内部采样时钟方式采样窗口5*CLK
	INSAMP_CLKWIN_7  =  0x03,   //内部采样时钟方式采样窗口7*CLK
	INSAMP_CLKWIN_9  =  0x04,   //内部采样时钟方式采样窗口9*CLK
	INSAMP_CLKWIN_11 =  0x05,   //内部采样时钟方式采样窗口11*CLK
	INSAMP_CLKWIN_13 =  0x06,   //内部采样时钟方式采样窗口13*CLK
	INSAMP_CLKWIN_15 =  0x07    //内部采样时钟方式采样窗口15*CLK
} InSamp_ClkWin_TypeDef;


typedef enum
{
	TRIG_CPU  =  0x00,        //ADC选择CPU触发采样
	TRIG_EXT  =  0x01         //ADC选择外部信号触发采样
} ADC_Trig_TypeDef;


#define ADC_EXTTRIG_NOSIGNAL        0x00
#define ADC_EXTTRIG_PWMPLUS0_TRIG0  0x01
#define ADC_EXTTRIG_PWMPLUS0_TRIG1  0x02
#define ADC_EXTTRIG_PWMPLUS0_TRIG2  0x04
#define ADC_EXTTRIG_PWMPLUS0_TRIG3  0x08
#define ADC_EXTTRIG_PWMPLUS1_TRIG0  0x10
#define ADC_EXTTRIG_PWMPLUS1_TRIG1  0x20
#define ADC_EXTTRIG_PWMPLUS1_TRIG2  0x40
#define ADC_EXTTRIG_PWMPLUS1_TRIG3  0x80
#define ADC_EXTTRIG_TIMPLUS0_LOW    0x100
#define ADC_EXTTRIG_TIMPLUS0_HIGH   0x200
#define ADC_EXTTRIG_TIMPLUS1_LOW    0x400
#define ADC_EXTTRIG_TIMPLUS1_HIGH   0x800

//断言ADC时钟分频系数
#define IS_ADC_CLKDIV(ADC_CLKDIV)  (((ADC_CLKDIV) >= CLK_DIV_1) && ((ADC_CLKDIV) <= CLK_DIV_8))

//断言ADC通道
#define IS_ADC_CH(ADC_CH)   ((ADC_CH) == ADC_CH0)  || ((ADC_CH) == ADC_CH1)  || ((ADC_CH) == ADC_CH2)  || ((ADC_CH) == ADC_CH3)  || \
                            ((ADC_CH) == ADC_CH4)  || ((ADC_CH) == ADC_CH5)  || ((ADC_CH) == ADC_CH6)  || ((ADC_CH) == ADC_CH7)  || \
							((ADC_CH) == ADC_CH8)  || ((ADC_CH) == ADC_CH9)  || ((ADC_CH) == ADC_CH10) || ((ADC_CH) == ADC_CH11) || \
							((ADC_CH) == ADC_CH12) || ((ADC_CH) == ADC_CH13) || ((ADC_CH) == ADC_CH14) || ((ADC_CH) == ADC_CH15)
							
                             

//断言ADC采样取平均
#define IS_ADC_SAMP_AVG(ADC_SAMP_AVG)  (((ADC_SAMP_AVG) >= SAMP_AVG_1) && ((ADC_SAMP_AVG) <= SAMP_AVG_8))

//断言ADC采样模式
#define IS_ADC_SAMP_MODE(ADC_SAMP_MODE)  (((ADC_SAMP_MODE) == SAMP_MODE_SINGLE) || ((ADC_SAMP_MODE) == SAMP_MODE_CONTINUE))

//断言ADC模式
#define IS_ADC_MODE(ADC_MODE)  (((ADC_MODE) == MODE_FIFO) || ((ADC_MODE) == MODE_CHAN))

//断言ADC采样时钟
#define IS_ADC_SAMP_CLOCK(ADC_SAMP_CLOCK)   (ADC_SAMP_CLOCK == SAMP_CLK_EXT || ADC_SAMP_CLOCK == SAMP_CLK_IN)

//断言ADC外部采样时钟窗口
#define IS_ADC_EXTSAMP_CLKWIN(ADC_EXTSAMP_CLKWIN)  (ADC_EXTSAMP_CLKWIN >= EXTSAMP_CLKWIN_1 && ADC_EXTSAMP_CLKWIN <= EXTSAMP_CLKWIN_128)

//断言ADC内部采样时钟窗口
#define IS_ADC_INSAMP_CLKWIN(ADC_INSAMP_CLKWIN)  (ADC_INSAMP_CLKWIN >= INSAMP_CLKWIN_1 && ADC_INSAMP_CLKWIN <= INSAMP_CLKWIN_15)

//断言ADC的offset数据使能
#define IS_ADC_OFFSET_EN(ADC_OFFSET_EN) (((ADC_OFFSET_EN) == ENABLE) || ((ADC_OFFSET_EN) == DISABLE))

//断言ADC的kd数据使能
#define IS_ADC_KD_EN(ADC_KD_EN) (((ADC_KD_EN) == ENABLE) || ((ADC_KD_EN) == DISABLE))

//断言ADC的DMA使能
#define IS_ADC_DMA_EN(ADC_DMA_EN) (((ADC_DMA_EN) == ENABLE) || ((ADC_DMA_EN) == DISABLE))

//断言ADC的FIFO半满中断使能
#define IS_ADC_FIFO_HALFFULL_IEN(ADC_FIFO_HALFFULL_IEN) (((ADC_FIFO_HALFFULL_IEN) == ENABLE) || ((ADC_FIFO_HALFFULL_IEN) == DISABLE))

//断言ADC的FIFO满中断使能
#define IS_ADC_FIFO_FULL_IEN(ADC_FIFO_FULL_IEN) (((ADC_FIFO_FULL_IEN) == ENABLE) || ((ADC_FIFO_FULL_IEN) == DISABLE))




typedef struct {
	ADC_Clk_Div_TypeDef Clk_Div;		   //ADC转换时钟分频，取值1 2 4 8
	
	uint16_t Channels;		               //ADC转换通道选中，ADC_CH0、ADC_CH1、... ... 、ADC_CH15及其组合（即“按位或”运算）
	
	ADC_SampAvg_TypeDef    SampAvg;	       //采样取平均，触发启动ADC转换后，ADC在一个通道上连续采样、转换多次，并将它们的平均值作为该通道转换结果
	
	ADC_Samp_Mode_TypeDef  Samp_Mode;	   //在软件触发模式下：1 连续转换模式，启动后一直采样、转换，直到软件清除START位
							               //                  0 单次转换模式，转换完成后START位自动清除停止转换

	ADC_Mode_TypeDef Mode;                 //数据存储为FIFO模式还是通道模式   0: FIFO  1:通道
	
	ADC_Samp_Clk_TypeDef   SampClk;        //ADC采样时钟选择  1:内部采样时钟   0:外部采样时钟
	
	ExtSamp_ClkWin_TypeDef ExtSamp_ClkWin; //外部采样窗口设置
	
	InSamp_ClkWin_TypeDef  InSamp_ClkWin;  //内部采样窗口设置
	
	ADC_Trig_TypeDef Trig;                 //ADC触发源选择  0  CPU   1  外部信号
	
	uint16_t  ExtTrig_Sel;                 //外部信号触发源选择
	
	FunctionalState Offset_En;             //offset数据使能   0:不使能  1:使能
	
	FunctionalState Kd_En;                 //kd数据使能       0:不使能  1:使能
	
	FunctionalState DMA_En;                //DMA使能          0:不使能 CPU读取FIFO数据 1:使能  DMA读取FIFO数据
	
	uint16_t Eoc_IEn;		               //EOC中断使能，可针对每个通道设置，其有效值为ADC_CH0、ADC_CH1、... ... 、ADC_CH15及其组合（即“按位或”运算）
	
	FunctionalState HalfFull_IEn;	       //FIFO半满中断使能
	
	FunctionalState Full_IEn;		       //FIFO  满中断使能
} ADC_InitStructure;



void ADC_Init(ADC_InitStructure * ADC_initStruct);  //ADC模数转换器初始化
void ADC_Open(void);                                //ADC开启
void ADC_Close(void);                               //ADC关闭
void ADC_Start(void);                               //ADC启动转换
void ADC_Stop(void);                                //ADC停止转换
void ADC_SoftReset(void);                           //ADC软复位
uint16_t ADC_Read(uint32_t chn);                    //从指定通道读取转换结果
void ADC_Read_FIFO(uint16_t * buffer,uint8_t num);  //从FIFO寄存器中读取转换结果
void ADC_FIFO_Clr(void);                            //清除FIFO寄存器
uint8_t ADC_IsEOC(uint32_t chn);                    //指定通道是否转换完成
void ADC_IntEOCEn(uint32_t chn);                    //转换完成中断使能
void ADC_IntEOCDis(uint32_t chn);                   //转换完成中断禁止
uint8_t ADC_IntEOCStat(uint32_t chn);               //转换完成中断状态
void ADC_IntEOCClr(uint32_t chn);                   //转换完成中断标志清除
uint8_t ADC_FIFO_Level(void);                       //获取FIFO水位
uint8_t ADC_FULLStat(void);                         //FIFO满状态
uint8_t ADC_HALFFULLStat(void);                     //FIFO半满状态
uint8_t ADC_EMPTYStat(void);                        //FIFO空状态
void ADC_IntFULLEn(void);                           //FIFO满中断使能
void ADC_IntFULLDis(void);                          //FIFO满中断禁止
uint8_t ADC_IntFULLStat(void);                      //FIFO满中断状态
void ADC_IntFULLClr(void);                          //FIFO满中断状态清除
void ADC_IntHALFFULLEn(void);                       //FIFO半满中断使能
void ADC_IntHALFFULLDis(void);                      //FIFO半满中断禁止
uint8_t ADC_IntHALFFULLStat(void);                  //FIFO半满中断状态
void ADC_IntHALFFULLClr(void);                      //FIFO半满中断状态清除



#endif //__DP32G030_ADC_H__
