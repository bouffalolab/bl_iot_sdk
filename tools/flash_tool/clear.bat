del /a /f /s /q "*.log"
del /a /f /s /q "*.ini"
del /a /f /s /q "iot.toml"
del /a /f /s /q "iot_linux.toml"
del /a /f /s /q "mcu.toml"
del /a /f /s /q "flash.toml"
del /a /f /s /q "storage.toml"
del /a /f /s /q "partition.bin"
del /a /f /s /q "ro_params.dtb"
del /a /f /s /q "efusedata.bin"
del /a /f /s /q "efusedata_mask.bin"
rd /s /Q .\docs\tg6210a
rd /s /Q .\chips\bl60x
rd /s /Q .\chips\bl56x
rd /s /Q .\chips\bl562
rd /s /Q .\chips\bl628
rd /s /Q .\chips\wb03
rd /s /Q .\utils\flash\bl60x
rd /s /Q .\utils\flash\bl628
rd /s /Q .\utils\flash\wb03
del /a /f /s /q .\chips\bl602\img_create_iot\*.bin
del /a /f /s /q .\chips\bl702\img_create_iot\*.bin
del /a /f /s /q .\chips\bl702l\img_create_iot\*.bin
del /a /f /s /q .\chips\bl808\img_create_iot\*.bin
del /a /f /s /q .\chips\bl606p\img_create_iot\*.bin
del /a /f /s /q .\chips\bl616\img_create_iot\*.bin
del /a /f /s /q .\chips\bl628\img_create_iot\*.bin
del /a /f /s /q .\chips\bl602\img_create_mcu\*.bin
del /a /f /s /q .\chips\bl702\img_create_mcu\*.bin
del /a /f /s /q .\chips\bl702l\img_create_mcu\*.bin
del /a /f /s /q .\chips\bl808\img_create_mcu\*.bin
del /a /f /s /q .\chips\bl606p\img_create_mcu\*.bin
del /a /f /s /q .\chips\bl616\img_create_mcu\*.bin
del /a /f /s /q .\chips\bl628\img_create_mcu\*.bin
del /a /f /s /q .\chips\bl602\img_create_linux\*.bin
del /a /f /s /q .\chips\bl702\img_create_linux\*.bin
del /a /f /s /q .\chips\bl702l\img_create_linux\*.bin
del /a /f /s /q .\chips\bl808\img_create_linux\*.bin
del /a /f /s /q .\chips\bl606p\img_create_linux\*.bin
del /a /f /s /q .\chips\bl616\img_create_linux\*.bin
del /a /f /s /q .\chips\bl628\img_create_linux\*.bin
del /a /f /s /q .\chips\bl602\efuse_bootheader\*.bin
del /a /f /s /q .\chips\bl702\efuse_bootheader\*.bin
del /a /f /s /q .\chips\bl702l\efuse_bootheader\*.bin
del /a /f /s /q .\chips\bl808\efuse_bootheader\*.bin
del /a /f /s /q .\chips\bl606p\efuse_bootheader\*.bin
del /a /f /s /q .\chips\bl616\efuse_bootheader\*.bin
del /a /f /s /q .\chips\bl628\efuse_bootheader\*.bin
del /a /f /s /q .\chips\*.pack
rd /s /Q .\chips\bl602\ota
rd /s /Q .\chips\bl702\ota
rd /s /Q .\chips\bl702l\ota
rd /s /Q .\chips\bl808\ota
rd /s /Q .\chips\bl606p\ota
rd /s /Q .\chips\bl616\ota
rd /s /Q .\chips\bl628\ota
rd /s /Q .\chips\bl606p\test_bin
rd /s /Q .\chips\bl808\test_bin
del /a /f /s /q ".DS_Store"
del /a /f /s /q "._.DS_Store"
for %%x in (bin) do (
for /r . %%a in (*_rfpa.%%x) do del /a /f /s /q %%a 
)
exit 