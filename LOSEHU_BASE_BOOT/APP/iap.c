#include "iap.h"

void app_to_boot(void)
{
	FLASH_Mask_UnLock();
	FLASH_Mask_Sel(FLASH_MAIN_NO_MASK);
	FLASH_Mask_Lock();
 	__DSB(); 
	SCB->AIRCR  = ((0x5FA << SCB_AIRCR_VECTKEY_Pos)|SCB_AIRCR_SYSRESETREQ_Msk);
	__DSB();
	while(1);  
}

void boot_to_app(void)
{
	FLASH_Mask_UnLock();
	FLASH_Mask_Sel(FLASH_MAIN_4K_MASK);
	FLASH_Mask_Lock();
	__DSB(); 
	SCB->AIRCR  = ((0x5FA << SCB_AIRCR_VECTKEY_Pos)|SCB_AIRCR_SYSRESETREQ_Msk);
	__DSB();
	while(1);  
}
