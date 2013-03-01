/* Arduino USB Joystick HID demo */

/* Author: Darran Hunt
 * Released into the public domain.
 */

struct {
    uint8_t TipSwitch;
    uint8_t ContactId; 
    int16_t  x; /**< Current absolute touch X position, as a signed 16-bit integer */
    int16_t  y; /**< Current absolute touch Y position, as a signed 16-bit integer */
    int16_t  ScanTime; 
    uint8_t ContactCount; 
} touchReport;

void setup();
void loop();

void setup() 
{
    Serial.begin(115200);
    delay(200);
}

/* Move the joystick in a clockwise square every 5 seconds,
 * and press button 1 then button 2.
 */
void loop() 
{
    int ind;
    delay(5000);

    touchReport.TipSwitch = 0;
    touchReport.x = 0;
    touchReport.y = 0;
    touchReport.ContactId = 0;
    touchReport.ContactCount = 1;
    
    touchReport.ScanTime = (int16_t) (micros() / 100);
    /* Move the joystick in a clockwise direction */
    touchReport.x = 100;
    Serial.write((uint8_t *)&touchReport, sizeof(touchReport));
    delay(1000);

    touchReport.ScanTime = (int16_t) (micros() / 100);
    touchReport.x = 0;
    touchReport.y = 100;
    Serial.write((uint8_t *)&touchReport, sizeof(touchReport));
    delay(1000);

    touchReport.ScanTime = (int16_t) (micros() / 100);
    touchReport.x = 200;
    touchReport.y = 0;
    Serial.write((uint8_t *)&touchReport, sizeof(touchReport));
    delay(1000);

    touchReport.ScanTime = (int16_t) (micros() / 100);
    touchReport.x = 0;
    touchReport.y = 200;
    Serial.write((uint8_t *)&touchReport, sizeof(touchReport));
    delay(1000);

    /* Send button 1 then button 2 */

     touchReport.ScanTime = (int16_t) (micros() / 100);
     touchReport.y = 0;
    touchReport.TipSwitch = 1;
    Serial.write((uint8_t *)&touchReport, sizeof(touchReport));
    delay(1000);

    
    touchReport.ScanTime = (int16_t) (micros() / 100);
    touchReport.TipSwitch = 0;
    Serial.write((uint8_t *)&touchReport, sizeof(touchReport));

}
