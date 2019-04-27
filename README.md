# arduino_car02
使用esp8266控制L298N驱动小车
## 使用esp8266 和 L298N连接对应关系 
```
const uint8_t in1 = 2; //D4 

const uint8_t in2 = 14; //D5 

const uint8_t in3 = 12; //D6 

const uint8_t in4 = 13; //D7 

//上面定义了板上的4个控制端，12一组，34一组 

const uint8_t speedPinA = 5;  //D1 

const uint8_t speedPinB = 4;  //D2 
```
## 使用vue访问时，需要更改HelloFromVux.vue中，host地址
