#define MAX_AXIS 3
#define MAX_RECORDS 10
#define MAX_INDEX (MAX_RECORDS-1)

static const byte PIN_X_AXIS = A0;
static const byte PIN_Y_AXIS = A1;
static const byte PIN_Z_AXIS = A2;

static int rolling[MAX_AXIS][MAX_RECORDS];
static int current = 0;

void setup() {
  for (byte i = 0 ; i < MAX_AXIS; i++)
      for (byte j = 0 ; i < MAX_RECORDS; i++)
            rolling[i][j] = 0;
            
  Serial.begin(38400);
}

void loop() {
  Serial.print("Current = ");
  Serial.println(current); 
  int delta1 = 0;
  int delta2 = 0;

  for (byte i = 0; i < MAX_AXIS; i++) {
     int r =  analogRead(PIN_X_AXIS+i);
     rolling[i][current?current-1:MAX_INDEX] = abs(rolling[i][current?current-1:MAX_INDEX]-r);
     rolling[i][current] = r;
     Serial.print(" Stored value ="); 
     Serial.print(rolling[i][current]); 
     Serial.print(" Delta1  = "); 
     Serial.print(delta1+=rolling[i][current?current-1:MAX_INDEX]); 
     Serial.print(" Delta2  = "); 
     Serial.println(delta2+=rolling[i][current-1?current-2:MAX_INDEX]); 
  }
  
  Serial.print("Total Delta1 = "); 
  Serial.println(delta1/3); 
  Serial.print("Total Delta2 = "); 
  Serial.println(delta2/3); 
  ++current %= 10;
  delay(2000);
}

