#include "my_key.h"


Show_state show_state=cam;

void update_state()
{
  if(1==Key_Scan())
  {
      show_state = (Show_state)(show_state + 1);
      if(show_state>=max_state)
      {
        show_state=cam;
      }
  }
}

void Key_Init()
{
    pinMode(boot_pin,INPUT);
}
int Key_Scan()
{
    if(digitalRead(boot_pin)==LOW){
        delay(5);
        if (digitalRead(boot_pin)==LOW)
        {
            while (digitalRead(boot_pin)==LOW);
            return 1;
        }
    }
    return 0;
}

