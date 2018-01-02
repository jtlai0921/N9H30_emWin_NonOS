/**************************************************************************//**
 * @file     sensor_nt99141.c
 * @version  V1.00
 * $Revision: 1 $
 * $Date: 15/06/05 10:20a $
 * @brief    NT99141 sensor driver
 *
 * @note
 * Copyright (C) 2015 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include <stdio.h>
#include "N9H30.h"
#include "sys.h"
#include "i2c_gpio.h"

struct NT_RegValue {
    uint16_t    u16RegAddr;            /* Sensor Register Address */
    uint8_t        u8Value;            /* Sensor Register Data */
};


/* NT99050, VGA, YUV422 */
static struct NT_RegValue g_sNT99050_VGA_RegValue[]= {
 	//[InitialSetting]
    {0x3021, 0x01},
#if 0 /* BT656 */
    {0x32F0, 0x61},{0x32F1, 0x10}, 	
#else
   {0x32F0, 0x01}, 
#endif    
    {0x3024, 0x00}, {0x3270, 0x00}, //[Gamma_MDR]
    {0x3271, 0x0D}, {0x3272, 0x19}, {0x3273, 0x2A}, {0x3274, 0x3C}, {0x3275, 0x4D}, 
    {0x3276, 0x67}, {0x3277, 0x81}, {0x3278, 0x98}, {0x3279, 0xAD}, {0x327A, 0xCE}, 
    {0x327B, 0xE0}, {0x327C, 0xED}, {0x327D, 0xFF}, {0x327E, 0xFF}, {0x3060, 0x01},
    {0x3210, 0x04}, //LSC //D
    {0x3211, 0x04}, //F
    {0x3212, 0x04}, //D
    {0x3213, 0x04}, //D
    {0x3214, 0x04}, {0x3215, 0x05}, {0x3216, 0x04}, {0x3217, 0x04}, {0x321C, 0x04},
    {0x321D, 0x05}, {0x321E, 0x04}, {0x321F, 0x03}, {0x3220, 0x00}, {0x3221, 0xA0},
    {0x3222, 0x00}, {0x3223, 0xA0}, {0x3224, 0x00}, {0x3225, 0xA0}, {0x3226, 0x80},
    {0x3227, 0x88}, {0x3228, 0x88}, {0x3229, 0x30}, {0x322A, 0xCF}, {0x322B, 0x07},
    {0x322C, 0x04}, {0x322D, 0x02}, {0x3302, 0x00},//[CC: Saturation:100%]
    {0x3303, 0x1C}, {0x3304, 0x00}, {0x3305, 0xC8}, {0x3306, 0x00}, {0x3307, 0x1C},
    {0x3308, 0x07}, {0x3309, 0xE9}, {0x330A, 0x06}, {0x330B, 0xDF}, {0x330C, 0x01},
    {0x330D, 0x38}, {0x330E, 0x00}, {0x330F, 0xC6}, {0x3310, 0x07}, {0x3311, 0x3F},
    {0x3312, 0x07}, {0x3313, 0xFC}, {0x3257, 0x50}, //CA Setting
    {0x3258, 0x10}, {0x3251, 0x01}, {0x3252, 0x50}, {0x3253, 0x9A}, {0x3254, 0x00}, 
    {0x3255, 0xd8}, {0x3256, 0x60}, {0x32C4, 0x38}, {0x32F6, 0xCF}, {0x3363, 0x37},
    {0x3331, 0x08}, {0x3332, 0x6C}, // 60
    {0x3360, 0x10}, {0x3361, 0x30}, {0x3362, 0x70}, {0x3367, 0x40}, {0x3368, 0x32}, //20
    {0x3369, 0x24}, //1D
    {0x336A, 0x1A}, {0x336B, 0x20}, {0x336E, 0x1A}, {0x336F, 0x16}, {0x3370, 0x0c},
    {0x3371, 0x12}, {0x3372, 0x1d}, {0x3373, 0x24}, {0x3374, 0x30}, {0x3375, 0x0A},
    {0x3376, 0x18}, {0x3377, 0x20}, {0x3378, 0x30}, {0x3340, 0x1C}, {0x3326, 0x03}, //Eext_DIV
    {0x3200, 0x3E}, //1E
    {0x3201, 0x3F}, {0x3109, 0x82}, //LDO Open
    {0x3106, 0x07}, {0x303F, 0x02}, {0x3040, 0xFF}, {0x3041, 0x01}, {0x3051, 0xE0},
    {0x3060, 0x01},

    {0x32BF, 0x04}, {0x32C0, 0x6A},	{0x32C1, 0x6A},	{0x32C2, 0x6A}, {0x32C3, 0x00},
		{0x32C4, 0x20}, {0x32C5, 0x20}, {0x32C6, 0x20},	{0x32C7, 0x00},	{0x32C8, 0x95},
		{0x32C9, 0x6A},	{0x32CA, 0x8A},	{0x32CB, 0x8A},	{0x32CC, 0x8A},	{0x32CD, 0x8A},
		{0x32D0, 0x01},	{0x3200, 0x3E},	{0x3201, 0x0F},	{0x302A, 0x00},	{0x302B, 0x09},
		{0x302C, 0x00},	{0x302D, 0x04},	{0x3022, 0x24},	{0x3023, 0x24},	{0x3002, 0x00},
		{0x3003, 0x00},	{0x3004, 0x00},	{0x3005, 0x00},	{0x3006, 0x02},	{0x3007, 0x83},
		{0x3008, 0x01},	{0x3009, 0xE3},

		{0x300A, 0x03},	{0x300B, 0x28},	{0x300C, 0x01},	{0x300D, 0xF4},
		
		{0x300E, 0x02},	{0x300F, 0x84},	{0x3010, 0x01},	{0x3011, 0xE4},	{0x32B8, 0x3B},
		{0x32B9, 0x2D},	{0x32BB, 0x87},	{0x32BC, 0x34},	{0x32BD, 0x38},	{0x32BE, 0x30},
		{0x3201, 0x3F},	{0x320A, 0x01},	{0x3021, 0x06},	{0x3060, 0x01},	
};

static void Delay(uint32_t nCount)
{
    volatile uint32_t i;
    for(; nCount!=0; nCount--)
       for(i=0; i<200; i++);
}

static void SnrReset(void)
{
	/* GPIOI7 reset:	H->L->H 	*/
	outpw(REG_SYS_GPI_MFPL,(inpw(REG_SYS_GPI_MFPL) & ~0xF0000000));
	outpw((GPIO_BA+0x200),(inpw(GPIO_BA+0x200) | 0x0080)); /* GPIOI7 Output mode */
	outpw((GPIO_BA+0x204),(inpw(GPIO_BA+0x204) | 0x0080)); /* GPIOI7 Output to high */
	Delay(100);
	outpw((GPIO_BA+0x204),(inpw(GPIO_BA+0x204) & ~0x0080)); /* GPIOI7 Output to low */
	Delay(100);
	outpw((GPIO_BA+0x204),(inpw(GPIO_BA+0x204) | 0x0080)); /* GPIOI7 Output to high */
}

static void SnrPowerDown(BOOL bIsEnable)
{/* GPI0 power down, HIGH for power down */
	outpw( REG_SYS_GPI_MFPL,(inpw(REG_SYS_GPI_MFPL) & ~0x0000000F));
	outpw((GPIO_BA+0x200),(inpw(GPIO_BA+0x200) | 0x0001)); /* GPIOI0 Output mode */
	outpw((GPIO_BA+0x204),(inpw(GPIO_BA+0x204) &~ 0x0001)); /* GPIOI0 Output to low */

 	if(bIsEnable)
     outpw((GPIO_BA+0x204),(inpw(GPIO_BA+0x204) | 0x0001)); /* GPIOI0 Output to high */
 	else
     outpw((GPIO_BA+0x204),(inpw(GPIO_BA+0x204) &~ 0x0001)); /* GPIOI0 Output to low */
}

int InitNT99050_VGA(void)
{
    uint32_t i;
    uint8_t u8DeviceID=0x42;
    uint8_t u8ID[2]= {0};

    /* Enable GPIO Clock */
    outpw(REG_CLK_PCLKEN0,inpw(REG_CLK_PCLKEN0)|(1<<3));
    SnrReset();
    SnrPowerDown(FALSE);

    /* switch I2C pin function, to do... */
    SWI2C_Open(eDRVGPIO_GPIOB,eDRVGPIO_PIN0,eDRVGPIO_GPIOB,eDRVGPIO_PIN1,Delay);
    sysprintf("NT_RegNum=%3d\n",sizeof(g_sNT99050_VGA_RegValue)/sizeof(struct NT_RegValue));
    for(i=0; i<sizeof(g_sNT99050_VGA_RegValue)/sizeof(struct NT_RegValue); i++) {
        SWI2C_Write_8bitSlaveAddr_16bitReg_8bitData(u8DeviceID,g_sNT99050_VGA_RegValue[i].u16RegAddr,g_sNT99050_VGA_RegValue[i].u8Value);
    }
    u8ID[0]=SWI2C_Read_8bitSlaveAddr_16bitReg_8bitData(u8DeviceID,0x3000);  /* Chip_Version_H 0x05 */
    u8ID[1]=SWI2C_Read_8bitSlaveAddr_16bitReg_8bitData(u8DeviceID,0x3001);  /* Chip_Version_L 0x00 */
    sysprintf("Sensor Chip_Version_H = 0x%02x(0x05) Chip_Version_L = 0x%02x(0x00)\n", u8ID[0],u8ID[1]);
    if(u8ID[0]!=0x05 || u8ID[1]!=0x00 ) {
        sysprintf("NT99050 init failed!!\n");
        return 0;
    }
    return 1;
}




