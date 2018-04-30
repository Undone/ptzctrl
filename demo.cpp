#include <unistd.h>
#include "joystick.h" // https://github.com/drewnoakes/joystick
#include "ptzctrl.h"

using namespace std;

int main(int argc, char** argv)
{
    Joystick joystick("/dev/input/js0");
 
    if (!joystick.isFound())
    {
        printf("open failed.\n");
        exit(1);
    }
    
    PTZCtrl ptz("http://192.168.1.2/web/cgi-bin/hi3510/", "admin", "password");

    while (true)
    {
        usleep(1000);

        JoystickEvent event;
        
        if (joystick.sample(&event))
        {
            if (event.isButton())
            {
                if (event.number == 6 && event.value == 1) // back
                {
                    ptz.gotoPreset(1);
                }
                else if (event.number == 7 && event.value == 1) // start
                {
                    ptz.savePreset(1);
                }
                else if (event.number == 4 && event.value == 1) // left bumper
                {
                    ptz.setInfrared("open");
                }
                else if (event.number == 5 && event.value == 1) // right bumper
                {
                    ptz.setInfrared("close");
                }
                else
                {
                    // If button is released, stop movement
                    
                    if (event.value == 0)
                    {
                        ptz.stop();
                    }
                    else
                    {
                        // If the button is pushed, send a turn command
                        
                        if (event.number == 2) // button X
                        {
                            ptz.turnRight();
                        }
                        else if (event.number == 1) // button B
                        {
                            ptz.turnLeft();
                        }
                        else if (event.number == 3) // button Y
                        {
                            ptz.turnUp();
                        }
                        else if (event.number == 0) // button A
                        {
                            ptz.turnDown();
                        }
                    }
                }
            }
        }
    }
    
    return 0;
}

