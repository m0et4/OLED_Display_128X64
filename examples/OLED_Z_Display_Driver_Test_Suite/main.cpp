/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "STM32_OLED_Display_128X64/SeeedOLED.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
static const unsigned char SeeedLogo[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x60, 0xf0, 0xc0, 0x00, 0x00, 0x00, 0xfc, 0xff, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,
    0xff, 0xfc, 0x00, 0x00, 0x00, 0x80, 0xf0, 0x20, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0x60, 0xe0, 0xc0,
    0xc0, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0xc0, 0x60, 0xe0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x80, 0xc0,
    0xc0, 0xe0, 0x60, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0xc0, 0x60, 0xe0, 0xc0, 0xc0,
    0x80, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xe0, 0xe0, 0xc0, 0xc0, 0xf8, 0xf8, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xc0, 0xc0, 0xe0, 0x60, 0xc0, 0xc0, 0x80, 0x00, 0xc0, 0xf0, 0xf0, 0xf0, 0xc0, 0x00, 0xc0,
    0xc0, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xe0, 0xe0, 0xc0, 0xc0,
    0xf8, 0xf8, 0x00, 0xd8, 0xd8, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xe0, 0x60, 0xc0, 0xc0, 0x80, 0x00,
    0x00, 0x03, 0x0f, 0x1e, 0x3c, 0x70, 0xe3, 0xcf, 0x9f, 0x30, 0x00, 0x00, 0x00, 0x00, 0x70, 0xbf,
    0xcf, 0xe3, 0x70, 0x78, 0x3e, 0x0f, 0x03, 0x00, 0x00, 0x00, 0x33, 0x77, 0x66, 0x66, 0x66, 0x6c,
    0x7d, 0x18, 0x00, 0x1f, 0x3f, 0x76, 0x66, 0x66, 0x66, 0x76, 0x37, 0x07, 0x00, 0x0f, 0x3f, 0x7f,
    0x66, 0x66, 0x66, 0x66, 0x77, 0x27, 0x07, 0x00, 0x1f, 0x3f, 0x76, 0x66, 0x66, 0x66, 0x76, 0x37,
    0x07, 0x00, 0x0f, 0x3f, 0x71, 0x60, 0x60, 0x60, 0x60, 0x31, 0x7f, 0x7f, 0x00, 0x00, 0x00, 0x00,
    0x11, 0x37, 0x67, 0x66, 0x66, 0x6c, 0x7d, 0x38, 0x00, 0x00, 0x3f, 0x7f, 0x3f, 0x00, 0x00, 0x1f,
    0x3f, 0x70, 0x60, 0x60, 0x70, 0x7f, 0x7f, 0x00, 0x0f, 0x3f, 0x71, 0x60, 0x60, 0x60, 0x60, 0x31,
    0x7f, 0x7f, 0x00, 0x7f, 0x7f, 0x00, 0x06, 0x1f, 0x3b, 0x60, 0x60, 0x60, 0x60, 0x71, 0x3f, 0x1f,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x48, 0x48, 0x48, 0xb0, 0x00, 0xc0, 0x20,
    0x20, 0x20, 0xc0, 0x00, 0xc0, 0x20, 0x20, 0x20, 0xc0, 0x00, 0x40, 0xa0, 0xa0, 0xa0, 0x20, 0x00,
    0x00, 0x20, 0xf0, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0xf8, 0x08,
    0x08, 0x00, 0xc0, 0x20, 0x20, 0x20, 0xf8, 0x00, 0xc0, 0xa0, 0xa0, 0xa0, 0xc0, 0x00, 0x20, 0xa0,
    0xa0, 0xa0, 0xc0, 0x00, 0x40, 0xa0, 0xa0, 0xa0, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x48, 0x48, 0x48, 0x08, 0x00, 0x20, 0x40, 0x80, 0x40,
    0x20, 0x00, 0x00, 0x20, 0xf0, 0x20, 0x20, 0x00, 0xc0, 0xa0, 0xa0, 0xa0, 0xc0, 0x00, 0xe0, 0x00,
    0x20, 0x20, 0xc0, 0x00, 0xc0, 0x20, 0x20, 0x20, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x02, 0x02, 0x02, 0x01, 0x00, 0x01, 0x02,
    0x02, 0x02, 0x01, 0x00, 0x01, 0x02, 0x02, 0x02, 0x01, 0x00, 0x02, 0x02, 0x02, 0x02, 0x01, 0x00,
    0x00, 0x00, 0x01, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x03, 0x02,
    0x02, 0x00, 0x01, 0x02, 0x02, 0x02, 0x03, 0x00, 0x01, 0x02, 0x02, 0x02, 0x00, 0x00, 0x01, 0x02,
    0x02, 0x02, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x00, 0x00, 0x08, 0x06, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x02, 0x02, 0x82, 0x02, 0x00, 0x02, 0x01, 0x01, 0x01,
    0x02, 0x00, 0x00, 0x00, 0x01, 0x02, 0x02, 0x00, 0x01, 0x02, 0x02, 0x02, 0x00, 0x00, 0x03, 0x00,
    0x00, 0x00, 0x03, 0x00, 0x01, 0x02, 0x02, 0x02, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x82, 0x8c, 0x60, 0x1c, 0x02, 0x00, 0x1c, 0x22, 0x22, 0x22, 0x1c, 0x00, 0x1e,
    0x20, 0x20, 0x00, 0x3e, 0x00, 0x00, 0x3e, 0x04, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x3e, 0x04, 0x02, 0x02, 0x00, 0x1c, 0x2a, 0x2a, 0x2a, 0x0c, 0x00, 0x12, 0x2a, 0x2a,
    0x2a, 0x1c, 0x20, 0x1c, 0x22, 0x22, 0x22, 0x14, 0x00, 0x3f, 0x00, 0x02, 0x02, 0x3c, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void setDisplayToOriginalState(char testCase)
{
    HAL_Delay(5000);
    SeeedOled.init(&hi2c1);                       //initialze SEEED OLED display
    SeeedOled.clearDisplay();               // clear the screen and set start position to top left corner
    SeeedOled.deactivateScroll();           // deactivete Scroll (might be activated by previous test case)
    SeeedOled.setNormalDisplay();           // Non-inverted Display
    SeeedOled.setPageMode();                // Page mode to start with
    SeeedOled.setTextXY(2, 0);              // 0 Page, 0th Column
    SeeedOled.putString("Test Case ");
    SeeedOled.putNumber(testCase);
    SeeedOled.setTextXY(3, 0);
    SeeedOled.putString("Test Case ");
    SeeedOled.putNumber(testCase);
    SeeedOled.setTextXY(4, 0);
    SeeedOled.putString("Test Case ");
    SeeedOled.putNumber(testCase);
    SeeedOled.setTextXY(5, 0);
    SeeedOled.putString("Test Case ");
    SeeedOled.putNumber(testCase);
    HAL_Delay(2000);



}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();

  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  SeeedOled.init(&hi2c1);  //initialze SEEED OLED display

  /* USER CODE END 2 */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    setDisplayToOriginalState(1);

    SeeedOled.clearDisplay();          //clear the screen and set start position to top left corner
    SeeedOled.setNormalDisplay();      //Set display to normal mode (i.e non-inverse mode)
    SeeedOled.setPageMode();           //Set addressing mode to Page Mode
    SeeedOled.setTextXY(0, 0);         //Set the cursor to Xth Page, Yth Column
    SeeedOled.putString("Hello World!"); //Print the String


    setDisplayToOriginalState(2);

    SeeedOled.clearDisplay();           //clear the screen and set start position to top left corner
    SeeedOled.setNormalDisplay();       //Set display to Normal mode
    SeeedOled.setPageMode();            //Set addressing mode to Page Mode
    SeeedOled.setTextXY(0, 0);          //Set the cursor to 0th Page, 0th Column
    SeeedOled.putNumber(123);           //Print number
    SeeedOled.setTextXY(1, 0);          //Set the cursor to 1st Page, 0th Column
    SeeedOled.putNumber(0xFFFF);        //Print number
    SeeedOled.setTextXY(2, 0);          //Set the cursor to 2nd Page, 0th Column
    SeeedOled.putNumber(0xFFFFFFFF);    //Print number
    SeeedOled.setTextXY(3, 0);          //Set the cursor to 3rd Page, 0th Column
    SeeedOled.putNumber(-12345);        //Print number


    setDisplayToOriginalState(3);

    SeeedOled.clearDisplay();           //clear the screen and set start position to top left corner
    SeeedOled.setNormalDisplay();       //Set display to Normal mode
    SeeedOled.setHorizontalMode();      //Set addressing mode to Horizontal Mode
    SeeedOled.putString("!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~");  //Print String (ASCII 32 - 126 )



    setDisplayToOriginalState(4);

    SeeedOled.clearDisplay();               // clear the screen and set start position to top left corner
    SeeedOled.drawBitmap((unsigned char*) SeeedLogo, 1024);  // 1024 = 128 Pixels * 64 Pixels / 8

    setDisplayToOriginalState(5);

    SeeedOled.setInverseDisplay();          // Set Display to inverse mode
    SeeedOled.clearDisplay();               // clear the screen and set start position to top left corner
    SeeedOled.drawBitmap((unsigned char*) SeeedLogo, 1024);  // 1024 = 128 Pixels * 64 Pixels / 8

    setDisplayToOriginalState(6);

    SeeedOled.clearDisplay();               // clear the screen and set start position to top left corner
    SeeedOled.drawBitmap((unsigned char*) SeeedLogo, 1024);  // 1024 = 128 Pixels * 64 Pixels / 8
    SeeedOled.setHorizontalScrollProperties(Scroll_Left, 4, 7, Scroll_5Frames); //Set Scrolling properties to Scroll Left
    SeeedOled.activateScroll();             // Activate Scrolling
    HAL_Delay(5000);

    setDisplayToOriginalState(7);

    SeeedOled.clearDisplay();               // clear the screen and set start position to top left corner
    SeeedOled.drawBitmap((unsigned char*) SeeedLogo, 1024);  // 1024 = 128 Pixels * 64 Pixels / 8
    SeeedOled.setHorizontalScrollProperties(Scroll_Right, 4, 7, Scroll_5Frames); //Set the properties of Horizontal Scrool
    SeeedOled.activateScroll();             // Activate Scroll
    HAL_Delay(5000);


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
