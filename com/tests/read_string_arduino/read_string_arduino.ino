String myString;
void setup(){
    Serial.begin(115200);
}
void loop(){
    if(Serial.available()){
        myString = Serial.readString();
        Serial.println(myString);
    }
}
