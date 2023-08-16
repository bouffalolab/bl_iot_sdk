/****************************************************************************************
* @file map.txt
*
* @brief This file is the map file (gnuarm or armgcc).
*
* Copyright (C) BouffaloLab 2018
*
****************************************************************************************
*/

/* configure the CPU type */
OUTPUT_ARCH( "riscv" )
/* link with the standard c library */
INPUT(-lc)
/* link with the standard GCC library */
INPUT(-lgcc)
/* configure the entry point */
ENTRY(Reset_Handler)

StackSize = 0x0400; /*  1KB */

MEMORY
{
    code_memory (rx)  : ORIGIN = 0x80000000, LENGTH = 5M/*64K + 16K*/
    itcm_memory (rx)  : ORIGIN = 0x3F000000, LENGTH = 0  /*FPGA NO NEED itcm code run*/
    dtcm_memory (rx)  : ORIGIN = 0x3F000000, LENGTH = 80K
    /*ram_memory  (!rx) : ORIGIN = 0x62030000, LENGTH = 112K */
    ram_memory  (!rx) : ORIGIN = 0x3F014000, LENGTH = 304K
    /*ram_wifi  (!rx) : ORIGIN = 0x3F040000, LENGTH = 144K*/
 
    /*SRAM Region*/
    SRAM_JPG_HDR        :   ORIGIN = 0x30021800, LENGTH = 768
    PSRAM_HEAP          : ORIGIN = 0x80500000, LENGTH = 32M
    FPGA_DDR            : ORIGIN = 0xB0000000, LENGTH = 32M
}

SECTIONS
{
    PROVIDE(__metal_chicken_bit = 0);

    .text :
    {
        . = ALIGN(4);
        __text_code_start__ = .;

        KEEP (*(SORT_NONE(_start)))
        KEEP (*(SORT_NONE(Reset_Handler)))

        *(.text)
        *(.text.*)

        *(.rodata)
        *(.rodata.*)

        *(.srodata)
        *(.srodata.*)

        *(.tcm_code)
        *(.tcm_const)
        *(.sclock_rlt_code)
        *(.sclock_rlt_const)

        /* static cli cmds */
        . = ALIGN(8);
        _bl_static_cli_cmds_start = .;
        KEEP(*(.static_cli_cmds))
        *(.static_cli_cmds)
        _bl_static_cli_cmds_end = .;

        /* static fw attribute entry */
        . = ALIGN(4);
        _bl_static_fw_cfg_entry_start = .;
        KEEP(*(.wifi.cfg.entry))
        _bl_static_fw_cfg_entry_end = .;

        /* static blog code1 */
        . = ALIGN(4);
        _bl_static_blogcomponent_code_start = .;
        KEEP(SORT(*)(.static_blogcomponent_code*))
        *(.static_blogcomponent_code*)
        _bl_static_blogcomponent_code_end = .;

        /* static blog code2 */
        . = ALIGN(4);
        _bl_static_blogfile_code_start = .;
        KEEP(SORT(*)(.static_blogfile_code*))
        *(.static_blogfile_code*)
        _bl_static_blogfile_code_end = .;

        /* static blog code3 */
        . = ALIGN(4);
        _bl_static_blogpri_code_start = .;
        KEEP(SORT(*)(.static_blogpri_code*))
        *(.static_blogpri_code*)
        _bl_static_blogpri_code_end = .;

        . = ALIGN(4);
        _bl_driver_sensor_start = .;
        KEEP(*(.sensor_desc))
        _bl_driver_sensor_end = .;

        . = ALIGN(4);
        _bl_img_param_desc_start = .;
        KEEP(*(.img_param_desc))
        _bl_img_param_desc_end = .;
 
        . = ALIGN(4);
        __text_code_end__ = .;
    } > code_memory

    . = ALIGN(4);
    __itcm_load_addr = .;

    .itcm_region : AT (__itcm_load_addr)
    {
        . = ALIGN(4);
        __tcm_code_start__ = .;

        . = ALIGN(4);
        __tcm_code_end__ = .;
    } > itcm_memory

    __dtcm_load_addr = __itcm_load_addr + SIZEOF(.itcm_region);

    .dtcm_region : AT (__dtcm_load_addr)
    {
        . = ALIGN(4);
        __tcm_data_start__ = .;

        *(.tcm_data)
        /* *finger_print.o(.data*) */

        . = ALIGN(4);
        __tcm_data_end__ = .;
    } > dtcm_memory

    __jpg_hdr_load_addr = __dtcm_load_addr + SIZEOF(.dtcm_region);
    
    .sram_jpg_hdr : AT(__jpg_hdr_load_addr) ALIGN(4)
    {
        __sram_jpg_hdr_start__ = .;
        *(.jpg_hdr_data*)
        __sram_jpg_hdr_end__ = .;
    } > SRAM_JPG_HDR

    /*************************************************************************/
    /* .stack_dummy section doesn't contains any symbols. It is only
     * used for linker to calculate size of stack sections, and assign
     * values to stack symbols later */
    .stack_dummy (NOLOAD):
    {
        . = ALIGN(0x4);
        . = . + StackSize;
        . = ALIGN(0x4);
    } > dtcm_memory

    /* Set stack top to end of RAM, and stack limit move down by
     * size of stack_dummy section */
    __StackTop = ORIGIN(dtcm_memory) + LENGTH(dtcm_memory);
    PROVIDE( __freertos_irq_stack_top = __StackTop);
    __StackLimit = __StackTop - SIZEOF(.stack_dummy);

    /* Check if data + heap + stack exceeds RAM limit */
    ASSERT(__StackLimit >= __tcm_data_end__, "region RAM overflowed with stack")
    /*************************************************************************/

    __system_ram_load_addr = __jpg_hdr_load_addr + SIZEOF(.sram_jpg_hdr);

    .system_ram_data_region : AT (__system_ram_load_addr)
    {
        . = ALIGN(4);
        __system_ram_data_start__ = .;

        *(.system_ram)

        . = ALIGN(4);
        __system_ram_data_end__ = .;
    } > ram_memory

    __ram_load_addr = __system_ram_load_addr + SIZEOF(.system_ram_data_region);

    /* Data section */
    RAM_DATA : AT (__ram_load_addr)
    {
        . = ALIGN(4);
        __ram_data_start__ = .;

        PROVIDE( __global_pointer$ = . + 0x800 );

        *(.data)
        *(.data.*)
        *(.sdata)
        *(.sdata.*)
        *(.sdata2)
        *(.sdata2.*)
        PROVIDE(_fpga_ddr_start = .);
        *(.fgpa_ddr*)
        PROVIDE(_fpga_ddr_stop = .);
        *(.wifi_ram)
        . = ALIGN(4);
        __ram_data_end__ = .;
    } > ram_memory

    __etext_final = (__ram_load_addr + SIZEOF (RAM_DATA));
    ASSERT(__etext_final <= ORIGIN(code_memory) + LENGTH(code_memory), "code memory overflow")

    .bss (NOLOAD) :
    {
        . = ALIGN(4);
        __bss_start__ = .;

        *(.bss*)
        *(.sbss*)
        *(COMMON)
    	*(.ram_img*)

        . = ALIGN(4);
        __bss_end__ = .;
    } > ram_memory

    .noinit_data (NOLOAD) :
    {
        . = ALIGN(4);
        __noinit_data_start__ = .;

        *(.noinit_data*)

        . = ALIGN(4);
        __noinit_data_end__ = .;
    } > ram_memory

    .heap (NOLOAD):
    {
        . = ALIGN(4);
        __HeapBase = .;

        /*__end__ = .;*/
        /*end = __end__;*/
        KEEP(*(.heap*))

        . = ALIGN(4);
        __HeapLimit = .;
    } > ram_memory
    __HeapLimit = ORIGIN(ram_memory) + LENGTH(ram_memory);

    .ram_fpga_ddr (NOLOAD) :
	{
        *(.img_buf*)
	} > FPGA_DDR
 
    PROVIDE( _heap_start = ORIGIN(PSRAM_HEAP) );
    PROVIDE( _heap_size = LENGTH(PSRAM_HEAP) );
   
    PROVIDE(_heap_start_tcm = __HeapBase);
    PROVIDE(_heap_size_tcm = ORIGIN(ram_memory) + LENGTH(ram_memory) - __HeapBase);

    /* sensor driver */
    PROVIDE( _ld_bl_driver_sensor_start = _bl_driver_sensor_start );
    PROVIDE( _ld_bl_driver_sensor_end   = _bl_driver_sensor_end );

    /* image param desc */
    PROVIDE( _ld_bl_img_param_desc_start = _bl_img_param_desc_start );
    PROVIDE( _ld_bl_img_param_desc_end   = _bl_img_param_desc_end );
    
    /*SYMOBOL used in code*/
    PROVIDE( _ld_bl_static_cli_cmds_start = _bl_static_cli_cmds_start );
    PROVIDE( _ld_bl_static_cli_cmds_end   = _bl_static_cli_cmds_end );

    /*CFG FW used in code*/
    PROVIDE( _ld_bl_static_cfg_entry_start = _bl_static_fw_cfg_entry_start );
    PROVIDE( _ld_bl_static_cfg_entry_end   = _bl_static_fw_cfg_entry_end );

    /* blog */
    PROVIDE( _ld_bl_static_blogcomponent_code_start = _bl_static_blogcomponent_code_start );
    PROVIDE( _ld_bl_static_blogcomponent_code_end   = _bl_static_blogcomponent_code_end );
    PROVIDE( _ld_bl_static_blogfile_code_start = _bl_static_blogfile_code_start );
    PROVIDE( _ld_bl_static_blogfile_code_end   = _bl_static_blogfile_code_end );
    PROVIDE( _ld_bl_static_blogpri_code_start = _bl_static_blogpri_code_start );
    PROVIDE( _ld_bl_static_blogpri_code_end   = _bl_static_blogpri_code_end );
}

