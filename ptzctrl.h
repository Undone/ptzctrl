#ifndef PTZCTRL_H
#define PTZCTRL_H

#include <string>

class PTZCtrl
{
private:
    
    std::string cameraURL;
    std::string httpAuthentication;
    bool useHttpAuthentication;

    // Make a HTTP GET request
    void requestGET(std::string url);
    
public:
    
    PTZCtrl(std::string url);
    
    PTZCtrl(std::string url, std::string username, std::string password);
    
    // Turn camera upwards
    void turnUp();
    
    // Turn camera downwards
    void turnDown();

    // Turn camera towards left
    void turnLeft();
    
    // Turn camera towards right
    void turnRight();
    
    // Stop camera movement
    void stop();
    
    /*
        Turn camera to specified preset
        @param preset number 0-7
    */
    void gotoPreset(int preset);
    
    /*
        Save current position as a preset
        @param preset number 0-7
    */
    void savePreset(int preset);
    
    /*
        Set the status of the infrared LEDs
        @param "open", "close" or "auto"
    */
    void setInfrared(std::string status);
    
};

#endif /* PTZCTRL_H */

