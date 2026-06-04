#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// I2C OLED SSD1306 address (thường là 0x3C)
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);// Khởi động giao tiếp giữa máy tính và ESP
  Serial.println("SSD1306 OLED Test Start");//in ra màn hình dòng...
  pinMode(34,INPUT);//Thiết lập chân GPIO 34 của ESP32 thành INPUT, chân này sẽ đọc tín hiệu vào
  Wire.begin(21, 22);  // SDA, SCL — đổi nếu bạn dùng chân khác

  // ===== OLED INIT =====
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) //Nếu OLED khởi tạo thất bại → trả về true . Dấu "!" ở đầu chỉ là không
  {
    Serial.println("Failed to initialize SSD1306!");
    for(;;);//vòng lặp vô hạn
   
  }

  display.clearDisplay();//xóa toàn bộ nội dung đang có trên màn hình
  display.setTextColor(SSD1306_WHITE);//đặt màu chữ trong màn hình

  // ===== TEST 1: Text cơ bản =====
  display.setTextSize(1); //kích cỡ
  display.setCursor(0, 0);//vị trí in chữ đầu tiên . (0,0) là góc trên bên trái màn hình
  display.println("OLED SSD1306 Test");//lệnh in 
  display.println("Hello ESP32!");
  display.display();//rất quan trọng, đẩy bộ nhớ đệm lên màn hình
  delay(1500);

  // ===== TEST 2: Fill screen =====
  display.clearDisplay();
  display.fillRect(0, 0, 128, 64, SSD1306_WHITE);
  display.display();
  delay(800);

  display.clearDisplay();

  // ===== TEST 3: Draw shapes =====
  display.drawRect(0, 0, 128, 64, SSD1306_WHITE);
  display.drawCircle(64, 32, 20, SSD1306_WHITE);
  display.drawLine(0, 63, 127, 0, SSD1306_WHITE);
  display.display();
  delay(1500);

  // ===== TEST 4: FPS test =====
  display.clearDisplay();
  for (int i = 0; i < 100; i++) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Frame: ");
    display.println(i);
    display.drawCircle(random(10,120), random(10,50), 5, SSD1306_WHITE);
    display.display();
  }

  display.clearDisplay();
  display.fillRect(0, 0, 128, 64, SSD1306_WHITE);
  display.display();
  delay(800);
  display.clearDisplay();
  display.setTextSize(1,3);
  display.setCursor(0,0);
  display.print("WATER SENSOR CIRCUIT");
  display.drawLine(0, 31, 128, 31, SSD1306_WHITE);
  display.setTextSize(1,3);
  display.setCursor(0,35);
  display.print("TDS Value: ");
   display.setCursor(85,35);
  display.println("ppm");
}


void loop() {
  display.fillRect(64,35,20,35, SSD1306_BLACK);
  int tdsValue = analogRead(34);
  display.setTextSize(1,3);
  display.setCursor(64,35);
  display.print(tdsValue);
  display.display();
  delay(1000);
  
}