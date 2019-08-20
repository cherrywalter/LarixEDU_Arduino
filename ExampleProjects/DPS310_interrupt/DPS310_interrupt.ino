#include <Dps310.h>

// Dps310 Opject
Dps310 Dps310PressureSensor = Dps310();

void fifoFull();

//FIFO can store 32 values 
//If you measure Temperature and Pressure, there will be 
//16 temperature values and 16 pressure values

uint8_t pressureCount = 32;
float pressure[32];

uint8_t temperatureCount = 32;
float temperature[32];

volatile int measurements_available = 0;

int16_t ret;

void setup() 
{
  Serial.begin(9600);
  while (!Serial);
  delay(100);

  //Call begin to initialize Dps310PressureSensor
  //The parameter 0x76 is the bus address. The default address is 0x77 and does not need to be given.
  //Dps310PressureSensor.begin(Wire, 0x76);
  //Use the commented line below instead to use the default I2C address.
  Dps310PressureSensor.begin(Wire);

  /*
   * Interrupt Sources:
   * NO_INTR = 0,
   * PRS_INTR = 1,
   * TEMP_INTR = 2,
   * BOTH_INTR = 3,
   * FIFO_FULL_INTR = 4,
   */
  ret = Dps310PressureSensor.setInterruptSources(4, 0);
  if(ret == 0)
  {
    Serial.println("Interrupt Source Set");
  }

   //clear interrupt flag by reading
  ret = Dps310PressureSensor.getIntStatusFifoFull();
  if(ret == 0)
  {
      Serial.println("FIFO Flag cleared ");
  }

   //initialization of Interrupt for Controller unit
  //SDO pin of Dps310 has to be connected with interrupt pin
  int16_t interruptPin = 35;
  pinMode(interruptPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), fifoFull, FALLING);

  //temperature measure rate (value from 0 to 7)
  //2^temp_mr temperature measurement results per second
  int16_t temp_mr = 2;
  //temperature oversampling rate (value from 0 to 7)
  //2^temp_osr internal temperature measurements per result
  //A higher value increases precision
  int16_t temp_osr = 2;
  //pressure measure rate (value from 0 to 7)
  //2^prs_mr pressure measurement results per second
  int16_t prs_mr = 2;
  //pressure oversampling rate (value from 0 to 7)
  //2^prs_osr internal pressure measurements per result
  //A higher value increases precision
  int16_t prs_osr = 2;
  //startMeasureBothCont enables background mode
  //temperature and pressure ar measured automatically
  //High precision and hgh measure rates at the same time are not available.
  //Consult Datasheet (or trial and error) for more information
   ret = Dps310PressureSensor.startMeasureBothCont(temp_mr, temp_osr, prs_mr, prs_osr);

  //Use one of the commented lines below instead to measure only temperature or pressure
  //For example if you want to use an other interrupt source
  //int16_t ret = Dps310PressureSensor.startMeasureTempCont(temp_mr, temp_osr);
  //int16_t ret = Dps310PressureSensor.startMeasurePressureCont(prs_mr, prs_osr);

  if (ret != 0)
  {
    Serial.print("Init FAILED! ret = ");
    Serial.println(ret);
  }
  else
  {
    Serial.println("Init complete!");
  }
  
}

void loop() 
{
  Serial.println("loop running");
  Serial.println("");

  //ISR was called
  if(measurements_available == 1)
  {
    Serial.println("Start Reading Measurements");
    Serial.println();

    Serial.print(temperatureCount);
    Serial.println(" temperature values found: ");

    for (int16_t i = 0; i < temperatureCount; i++)
    {
      Serial.print(temperature[i]);
      Serial.println(" degrees of Celsius");
    }

    Serial.println();
    Serial.print(pressureCount);
    Serial.println(" pressure values found: ");

    for (int16_t i = 0; i < pressureCount; i++)
    {
      Serial.print(pressure[i]);
      Serial.println(" Pascal");
    } 

    Serial.println();
    //Clear Flag
    measurements_available = 0;
  }
  delay(200);
}

void fifoFull()
{
  //This function writes the results of continuous measurements to the arrays given as parameters
  //The parameters temperatureCount and pressureCount should hold the sizes of the arrays temperature and pressure when the function is called
  //After the end of the function, temperatureCount and pressureCount hold the numbers of values written to the arrays
  //Note: The Dps310 cannot save more than 32 results. When its result buffer is full, it won't save any new measurement results
  Dps310PressureSensor.getContResults(temperature, temperatureCount, pressure, pressureCount);

  //clear interrupt flag by reading
  Dps310PressureSensor.getIntStatusFifoFull();

  measurements_available = 1;
}
