

/*************************
* global variables         *
*************************/
unsigned long time_since_last_reset = 0;  
int interval_one = 5000;                  //5 seconds, 1st while loop
int interval_two = 3000;                  //3 seconds, 2nd while loop

/**************************
* setup                     *
**************************/
void setup(){
  Serial.begin(9600);        
  delay(150);
}
/**************************
* main loop                 *
**************************/
void loop(){
  
//1st while loop  
  time_since_last_reset = millis();                 //obtain reference  
  while((millis() - time_since_last_reset) < interval_one){ 
    Serial.println("Inside 1st while loop.");      //task one wants repeated
                                                                     //for interval_one  
  } 
  
  Serial.println(""); Serial.println("");
  
  //2nd while loop
  time_since_last_reset = millis();                //obtain reference 
  while((millis() - time_since_last_reset) < interval_two){ 
    Serial.println("Inside 2nd while loop.");   //task one wants repeated
                                                                   //for interval_two 
  } 

  Serial.println(""); Serial.println("");  
  
}  // <--- end of main loop﻿
