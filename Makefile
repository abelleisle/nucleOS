debug: upload
upload:
	@echo "Starting openOCD"
	@openocd -f board/st_nucleo_h743zi.cfg &
	@arm-none-eabi-gdb -iex "target remote :3333" out/os.elf 
	@pkill -9 openocd

stop:
	@pkill -9 openocd
