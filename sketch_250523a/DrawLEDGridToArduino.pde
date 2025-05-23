import processing.serial.*;

Serial myPort;
int cellSize = 50;
int[][] grid = new int[8][8];
boolean isButtonPressed = false;

// button setting
int btnX = 120;
int btnY = 420;
int btnW = 120;
int btnH = 40;

void settings() {
  size(8 * cellSize, 8 * cellSize + 80);
}

void setup() {
  println(Serial.list());
  myPort = new Serial(this, "COM4", 9600);
}

void draw() {
  background(255);
  drawGrid();
  drawButton("Send Image", btnX, btnY, btnW, btnH, isButtonPressed);
}

void drawGrid() {
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      stroke(0);
      fill(grid[y][x] == 1 ? 0 : 255);
      rect(x * cellSize, y * cellSize, cellSize, cellSize);
    }
  }
}

void mousePressed() {
  int x = mouseX / cellSize;
  int y = mouseY / cellSize;
  if (x >= 0 && x < 8 && y >= 0 && y < 8) {
    grid[y][x] = 1 - grid[y][x];
  }

  if (mouseX > btnX && mouseX < btnX + btnW &&
      mouseY > btnY && mouseY < btnY + btnH) {
    isButtonPressed = true;
  }
}

void mouseReleased() {
  boolean wasPressed = isButtonPressed;
  isButtonPressed = false;

  if (wasPressed &&
      mouseX > btnX && mouseX < btnX + btnW &&
      mouseY > btnY && mouseY < btnY + btnH) {
    sendGridToArduino();
  }
}

void drawButton(String label, int x, int y, int w, int h, boolean pressed) {
  if (pressed) {
    fill(150); 
  } else {
    fill(200);
  }
  stroke(0);
  rect(x, y, w, h, 8);
  fill(0);
  textAlign(CENTER, CENTER);
  text(label, x + w / 2, y + h / 2);
}

void sendGridToArduino() {
  for (int y = 0; y < 8; y++) {
    int b = 0;
    for (int x = 0; x < 8; x++) {
      b |= (grid[y][x] << (7 - x));
    }
    myPort.write(b);
  }
  println("Image has been sent to Arduino");
}
