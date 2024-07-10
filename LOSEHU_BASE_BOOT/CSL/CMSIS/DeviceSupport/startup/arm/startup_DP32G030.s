
; Amount of memory (in bytes) allocated for Stack
Stack_Size      EQU     0x00000080

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; Amount of memory (in bytes) allocated for Heap
Heap_Size       EQU     0x00000000

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB

; Vector Table Mapped to Address 0 at Reset
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp               ; Top of Stack
                DCD    Reset_Handler              ; Reset Handler
                DCD    NMI_Handler                ; NMI Handler
                DCD    HardFault_Handler          ; Hard Fault Handler
                DCD    0                          ; Reserved
                DCD    0                          ; Reserved
                DCD    0                          ; Reserved
                DCD    0                          ; Reserved
                DCD    0                          ; Reserved
                DCD    0                          ; Reserved
                DCD    0
                DCD    SVC_Handler                ; SVCall Handler
                DCD    0                          ; Reserved
                DCD    0                          ; Reserved
                DCD    PendSV_Handler             ; PendSV Handler
                DCD    SysTick_Handler            ; SysTick Handler

                ; External Interrupts
				DCD    WWDT_Handler          
				DCD    IWDT_Handler         
				DCD    RTC_Handler          
				DCD    DMA_Handler          
				DCD    ADC_Handler           
				DCD    TIMBASE0_Handler          
				DCD    TIMBASE1_Handler            
				DCD    TIMPLUS0_Handler           
				DCD    TIMPLUS1_Handler          
				DCD    PWMBASE0_Handler          
				DCD    PWMBASE1_Handler          
				DCD    PWMPLUS0_Handler            
				DCD    PWMPLUS1_Handler         
				DCD    UART0_Handler           
				DCD    UART1_Handler         
				DCD    UART2_Handler          
				DCD    SPI0_Handler   
				DCD    SPI1_Handler     
				DCD    IIC0_Handler      
				DCD    IIC1_Handler    
				DCD    CMP_Handler 
				DCD    TIMBASE2_Handler 					
				DCD    GPIOA5_Handler       
				DCD    GPIOA6_Handler   
				DCD    GPIOA7_Handler  
				DCD    GPIOB0_Handler     
				DCD    GPIOB1_Handler       
				DCD    GPIOC0_Handler   
				DCD    GPIOC1_Handler     
				DCD    GPIOA_Handler     
				DCD    GPIOB_Handler   
				DCD    GPIOC_Handler  
				
__Vectors_End

__Vectors_Size  EQU  __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

Reset_Handler    PROC
                 EXPORT  Reset_Handler          [WEAK]
				 IMPORT  __main
			 
				 LDR     R0, =__main
                 BX      R0
				 
                 ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler             [WEAK]
                B       .
                ENDP

HardFault_Handler PROC
                EXPORT  HardFault_Handler       [WEAK]
                B       .
                ENDP
				
SVC_Handler     PROC
                EXPORT  SVC_Handler             [WEAK]
                B       .
                ENDP

PendSV_Handler  PROC
                EXPORT  PendSV_Handler          [WEAK]
                B       .
                ENDP

SysTick_Handler PROC
                EXPORT  SysTick_Handler         [WEAK]
                B       .
                ENDP

WWDT_Handler           PROC
                EXPORT  WWDT_Handler           [WEAK]
                B       .
                ENDP

IWDT_Handler          PROC
                EXPORT  IWDT_Handler          [WEAK]
                B       .
                ENDP

RTC_Handler           PROC
                EXPORT  RTC_Handler           [WEAK]
                B       .
                ENDP

DMA_Handler           PROC
                EXPORT  DMA_Handler           [WEAK]
                B       .
                ENDP

ADC_Handler            PROC
                EXPORT  ADC_Handler            [WEAK]
                B       .
                ENDP

TIMBASE0_Handler           PROC
                EXPORT  TIMBASE0_Handler           [WEAK]
                B       .
                ENDP

TIMBASE1_Handler             PROC
                EXPORT  TIMBASE1_Handler             [WEAK]
                B       .
                ENDP

TIMPLUS0_Handler            PROC
                EXPORT  TIMPLUS0_Handler            [WEAK]
                B       .
                ENDP

TIMPLUS1_Handler          PROC
                EXPORT  TIMPLUS1_Handler          [WEAK]
                B       .
                ENDP

PWMBASE0_Handler          PROC
                EXPORT  PWMBASE0_Handler          [WEAK]
                B       .
                ENDP

PWMBASE1_Handler           PROC
                EXPORT  PWMBASE1_Handler           [WEAK]
                B       .
                ENDP

PWMPLUS0_Handler             PROC
                EXPORT  PWMPLUS0_Handler             [WEAK]
                B       .
                ENDP

PWMPLUS1_Handler          PROC
                EXPORT  PWMPLUS1_Handler          [WEAK]
                B       .
                ENDP

UART0_Handler            PROC
                EXPORT  UART0_Handler            [WEAK]
                B       .
                ENDP

UART1_Handler          PROC
                EXPORT  UART1_Handler          [WEAK]
                B       .
                ENDP

UART2_Handler          PROC
                EXPORT  UART2_Handler          [WEAK]
                B       .
                ENDP

SPI0_Handler    PROC
                EXPORT  SPI0_Handler    [WEAK]
                B       .
                ENDP

SPI1_Handler     PROC
                EXPORT  SPI1_Handler     [WEAK]
                B       .
                ENDP

IIC0_Handler       PROC
                EXPORT  IIC0_Handler       [WEAK]
                B       .
                ENDP

IIC1_Handler     PROC
                EXPORT  IIC1_Handler     [WEAK]
                B       .
                ENDP

CMP_Handler       PROC
                EXPORT  CMP_Handler       [WEAK]
                B       .
                ENDP
					
TIMBASE2_Handler             PROC
                EXPORT  TIMBASE2_Handler             [WEAK]
                B       .
                ENDP

GPIOA5_Handler       PROC
                EXPORT  GPIOA5_Handler        [WEAK]
                B       .
                ENDP

GPIOA6_Handler    PROC
                EXPORT  GPIOA6_Handler    [WEAK]
                B       .
                ENDP

GPIOA7_Handler   PROC
                EXPORT  GPIOA7_Handler   [WEAK]
                B       .
                ENDP

GPIOB0_Handler      PROC
                EXPORT  GPIOB0_Handler      [WEAK]
                B       .
                ENDP

GPIOB1_Handler     PROC
                EXPORT  GPIOB1_Handler     [WEAK]
                B       .
                ENDP

GPIOC0_Handler    PROC
                EXPORT  GPIOC0_Handler    [WEAK]
                B       .
                ENDP

GPIOC1_Handler        PROC
                EXPORT  GPIOC1_Handler      [WEAK]
                B       .
                ENDP

GPIOA_Handler      PROC
                EXPORT  GPIOA_Handler      [WEAK]
                B       .
                ENDP

GPIOB_Handler    PROC
                EXPORT  GPIOB_Handler    [WEAK]
                B       .
                ENDP

GPIOC_Handler   PROC
                EXPORT  GPIOC_Handler   [WEAK]
                B       .
                ENDP

                ALIGN


;*******************************************************************************
; User Stack and Heap initialization
;*******************************************************************************
                IF      :DEF:__MICROLIB
                
                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit
                
                ELSE
                
                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
                 
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF

                END
