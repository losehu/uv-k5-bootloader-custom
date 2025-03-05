@REM Fires 1-handed unbricking command using cheap J-Link "baite" debug probe
@REM No need to solder. Just press the right wires on the right pads with your fingers.
@REM Restores bootloader 2.00.06 with factory firmware 2.01.27
@ECHO ******** Launching 1 shot unbricking process with OpenOCD (JLink)...
@ECHO .
@CD OpenOCD
@openocd -f interface/jlink.cfg -f target/dp32g030.cfg -c "uv_flash_bl LOSEHU_BASE_BOOTLOADER.bin" -c "shutdown"
@PAUSE
