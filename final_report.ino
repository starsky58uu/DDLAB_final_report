#define ROW1 13
#define ROW2 12
#define ROW3 11
#define ROW4 10
#define ROW5 9
#define ROW6 8
#define ROW7 7
#define ROW8 6

#define COL1 5
#define COL2 4
#define COL3 3
#define COL4 A4
#define COL5 A3
#define COL6 A2
#define COL7 A1
#define COL8 A0

const int row[] = {
  ROW1, ROW2, ROW3, ROW4, ROW5, ROW6, ROW7, ROW8
};
const int col[] = {
  COL1, COL2, COL3, COL4, COL5, COL6, COL7, COL8
};

byte scan[8][8] = {
  {0, 1, 1, 1, 1, 1, 1, 1},
  {1, 0, 1, 1, 1, 1, 1, 1},
  {1, 1, 0, 1, 1, 1, 1, 1},
  {1, 1, 1, 0, 1, 1, 1, 1},
  {1, 1, 1, 1, 0, 1, 1, 1},
  {1, 1, 1, 1, 1, 0, 1, 1},
  {1, 1, 1, 1, 1, 1, 0, 1},
  {1, 1, 1, 1, 1, 1, 1, 0}
};

byte circle[8][8] = {
  {0, 0, 1, 1, 1, 1, 0, 0},
  {0, 1, 0, 0, 0, 0, 1, 0},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {0, 1, 0, 0, 0, 0, 1, 0},
  {0, 0, 1, 1, 1, 1, 0, 0}
};

void setup()
{

  for (byte i = 0; i <= sizeof(row); i++) {
    pinMode(row[i], OUTPUT);
  }
  for (byte i = 0; i <= sizeof(col); i++) {
    pinMode(col[i], OUTPUT);
  }

  Serial.begin(9600);

}

void loop()
{
  if (Serial.available() >= 8) {
    for (int row = 0; row < 8; row++) {
      byte b = Serial.read();
      for (int col = 0; col < 8; col++) {
        circle[row][col] = (b >> (7 - col)) & 0x01;
      }
    }
  }
  showPattern(circle);
}

void showPattern(byte matrix[8][8]) {
for (byte i = 0; i < 8; i++) {
  byte displayRow = 7 - i; 
  digitalWrite(row[displayRow], LOW);
  for (byte j = 0; j < 8; j++) {
    digitalWrite(col[j], matrix[i][j] ? HIGH : LOW);
  }
  delay(1);
  digitalWrite(row[displayRow], HIGH);
}
}

