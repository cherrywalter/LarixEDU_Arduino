//Include Librarys
#include <ICM20948.h>
#include <Dps310.h>
#include <SPI.h>
#include <SD.h>

#define ARRAY_ROWS 1000
#define FLOAT_COLUMN 13
#define CHAR_COLUMN 200

/*
   Not used defines
   Just column numbers with content of the column
  #define TIME 0
  #define TEMPERATURE_DPS 1
  #define PRESSURE_DPS 2
  #define ACCEL_X 3
  #define ACCEL_Y 4
  #define ACCEL_Z 5
  #define GYRO_X 6
  #define GYRO_Y 7
  #define GYRO_Z 8
  #define MAG_X 9
  #define MAG_Y 10
  #define MAG_Z 11
  #define TEMP_IMU 12
*/

// an ICM20948 object with the ICM-20948 sensor on I2C bus 0 with address 0x69
ICM20948 IMU(Wire, 0x69);

// Dps310 Opject
Dps310 Dps310PressureSensor = Dps310();

//File
File myFile;

int status; // IMU status

float temperature_dps;
float pressure_dps;

int init_time;
int measurement_time;

float buffer_float[ARRAY_ROWS][FLOAT_COLUMN];
int buffer_float_index_row = 0;

char buffer_[ARRAY_ROWS][CHAR_COLUMN];

void setup()
{
  Serial.begin(115200); //Open Serial Monitor for Debug-Messages

  pinMode(LED2, OUTPUT); //LED is lightning, if IMU init fails
  pinMode(LED3, OUTPUT); //LED is lightning, if SD Card init fails

  while (!Serial) {}
  delay(100); //Make sure Serial Monitor is open

  // start communication with IMU
  status = IMU.begin();
  Serial.print("status = ");
  Serial.println(status);
  if (status < 0)
  {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while (1)
    {
      digitalWrite(LED2, HIGH);
    }
  }

  Serial.println("Initializing SD card...");
  if (!SD.begin(28))
  {
    Serial.println("initialization failed!");
    digitalWrite(LED3, HIGH);
    while (1);
  }

  Dps310PressureSensor.begin(Wire);
  Serial.println("Init DPS complete!");

  Serial.println("initialization done.");

  //Open File Once
  myFile = SD.open("IMU.txt", FILE_WRITE);
  if (!myFile)
  {
    while (1)
    {
      digitalWrite(LED3, HIGH);
      delay(100);
      digitalWrite(LED3, LOW);
      delay(100);
    }
  }

  init_time = millis();
}



void printStringToSD(char measurements[ARRAY_ROWS][CHAR_COLUMN])
{
  for(int i = 0; i < ARRAY_ROWS; i++)
  {
    myFile.print(buffer_[i]);
  }
}

int getDPSMeasurements(int* buffer_float_index_column)
{
  uint8_t oversampling = 0;
  uint8_t error_to_return = 0x00;
  uint8_t err1 = Dps310PressureSensor.measureTempOnce(temperature_dps, oversampling);
  uint8_t err2 = Dps310PressureSensor.measurePressureOnce(pressure_dps, oversampling);

  if (err1 != 0)
  {
    Serial.println("DPS Temperature Measurement failed");
    error_to_return = error_to_return | 0x01; //Set Flag
    buffer_float[buffer_float_index_row][*buffer_float_index_column] = 0;
    (*buffer_float_index_column)++;
  }
  else
  {
    buffer_float[buffer_float_index_row][*buffer_float_index_column] = temperature_dps;
    (*buffer_float_index_column)++;
  }

  if (err2 != 0)
  {
    Serial.println("DPS Pressure Measurement failed");
    error_to_return = error_to_return | 0x08; //Set Flag
    buffer_float[buffer_float_index_row][*buffer_float_index_column] = 0;
    (*buffer_float_index_column)++;
  }
  else
  {
    buffer_float[buffer_float_index_row][*buffer_float_index_column] = pressure_dps;
    (*buffer_float_index_column)++;
  }

  return error_to_return;
}

int getIMUMeasurements(int* buffer_float_index_column)
{
  uint8_t err3 = IMU.readSensor();
  uint8_t error_to_return = 0x00;

  if (err3 != 1)
  {
    Serial.println("IMU Measurement failed");
    error_to_return = error_to_return | 0x01; //Set Flag

    for (int i = 0; i < FLOAT_COLUMN-3; i++)
    {
      buffer_float[buffer_float_index_row][*buffer_float_index_column] = 0;
      (*buffer_float_index_column)++;
    }
  }
  else
  {
    buffer_float[buffer_float_index_row][*buffer_float_index_column] = IMU.getAccelX_mss();
    (*buffer_float_index_column)++;

    buffer_float[buffer_float_index_row][*buffer_float_index_column] = IMU.getAccelY_mss();
    (*buffer_float_index_column)++;

    buffer_float[buffer_float_index_row][*buffer_float_index_column] = IMU.getAccelZ_mss();
    (*buffer_float_index_column)++;

    buffer_float[buffer_float_index_row][*buffer_float_index_column] = IMU.getGyroX_rads();
    (*buffer_float_index_column)++;

    buffer_float[buffer_float_index_row][*buffer_float_index_column] = IMU.getGyroY_rads();
    (*buffer_float_index_column)++;

    buffer_float[buffer_float_index_row][*buffer_float_index_column] = IMU.getGyroZ_rads();
    (*buffer_float_index_column)++;

    buffer_float[buffer_float_index_row][*buffer_float_index_column] = IMU.getMagX_uT();
    (*buffer_float_index_column)++;

    buffer_float[buffer_float_index_row][*buffer_float_index_column] = IMU.getMagY_uT();
    (*buffer_float_index_column)++;

    buffer_float[buffer_float_index_row][*buffer_float_index_column] = IMU.getMagZ_uT();
    (*buffer_float_index_column)++;

    buffer_float[buffer_float_index_row][*buffer_float_index_column] = IMU.getTemperature_C();
    (*buffer_float_index_column)++;
  }
  return error_to_return;
}

void Float_to_String()
{
  int total_characters_copied = 0;
  int currently_copied = 0;

  for (int i = 0; i < ARRAY_ROWS; i++)
  {
    for (int j = 0; j < FLOAT_COLUMN; j++)
    {
      if (j != FLOAT_COLUMN - 1)
      {
        if (buffer_float[i][j] < 0.0 && buffer_float[i][j] > -0.9999999)
        {
          currently_copied =  sprintf(buffer_[i] + total_characters_copied, "-%d.%06d;", (int)buffer_float[i][j], abs((int)(buffer_float[i][j] * 1000000) % 1000000));
        }
        else
        {
          currently_copied =  sprintf(buffer_[i] + total_characters_copied, "%d.%06d;", (int)buffer_float[i][j], abs((int)(buffer_float[i][j] * 1000000) % 1000000));
        }
      }
      else
      {
        if (buffer_float[i][j] < 0.0 && buffer_float[i][j] > -0.9999999)
        {
          currently_copied =  sprintf(buffer_[i] + total_characters_copied, "-%d.%06d\r\n", (int)buffer_float[i][j], abs((int)(buffer_float[i][j] * 1000000) % 1000000));
        }
        else
        {
          //Last Value -> No ; in the End; Put New Line in the End (\r because Windows)
          currently_copied =  sprintf(buffer_[i] + total_characters_copied, "%d.%06d\r\n", (int)buffer_float[i][j], abs((int)(buffer_float[i][j] * 1000000) % 1000000));
        }
      }
      total_characters_copied += currently_copied;
    }
    //Reset Values for copied characters
    total_characters_copied = 0;
    currently_copied = 0;
  }
}

void loop()
{
  int buffer_float_index_column = 0; //Column must be reset

  //Safe Time
  measurement_time = millis() - init_time;
  buffer_float[buffer_float_index_row][buffer_float_index_column] = measurement_time;
  buffer_float_index_column++;

  //Safe Measurements
  getDPSMeasurements(&buffer_float_index_column);
  getIMUMeasurements(&buffer_float_index_column);

  buffer_float_index_row++;

  //Print when Float Array = FULL
  if(buffer_float_index_row == ARRAY_ROWS)
  {
    Float_to_String();
    printStringToSD(buffer_);
   
   while (1)
   {
      // close the file:
      myFile.close();
      digitalWrite(LED2, HIGH);
      delay(100);
      digitalWrite(LED2, LOW);
      delay(100);
    }
  }
}
