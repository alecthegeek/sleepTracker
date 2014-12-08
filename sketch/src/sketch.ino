#define MAX_AXIS 3
#define MAX_RECORDS 4
#define MAX_INDEX (MAX_RECORDS-1)
#define DELAY 1000 // millisends
#define POST_MOVE_DELAY 1000 // 1 seconds

static const byte PIN_X_AXIS = A0;
static const byte PIN_Y_AXIS = A1;
static const byte PIN_Z_AXIS = A2;

static int rolling[MAX_AXIS][MAX_RECORDS];
static int current = 0;

void setup() {
  for (byte i = 0 ; i < MAX_AXIS; i++)
      for (byte j = 0 ; j < MAX_RECORDS; j++)
            rolling[i][j] = 0;

  Serial.begin(38400);
}

void loop() {
  delay(DELAY);
  int delta1 = 0;
  int delta2 = 0;

  for (byte i = 0; i < MAX_AXIS; i++) {
     int r =  analogRead(PIN_X_AXIS+i);
     Serial.print("Read from Pin ");
     Serial.print(r);
     rolling[i][current?current-1:MAX_INDEX] = abs(rolling[i][current?current-1:MAX_INDEX]-r);
     rolling[i][current] = r;
     delta1+=rolling[i][current?current-1:MAX_INDEX];  
     delta2+=rolling[i][current-1?current-2:MAX_INDEX]; 
  }

  if ((delta2+delta1)/3 > 100) {
     Serial.println(" Movement detected");
     delay(POST_MOVE_DELAY);
  }

  ++current %= 10;
}

