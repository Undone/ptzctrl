#include "ptzctrl.h"
#include <curl/curl.h>

PTZCtrl::PTZCtrl(std::string url)
{
    cameraURL = url;
    useHttpAuthentication = false;
}

PTZCtrl::PTZCtrl(std::string url, std::string username, std::string password)
{
    cameraURL = url;
    useHttpAuthentication = true;
    httpAuthentication = username + ":" + password;
}

void PTZCtrl::requestGET(std::string url)
{
    curl_global_init(CURL_GLOBAL_ALL);
    
    CURL *curl = curl_easy_init();
    
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        
        if (useHttpAuthentication)
        {
            curl_easy_setopt(curl, CURLOPT_USERPWD, httpAuthentication.c_str());
        }

        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);
    }
    
    curl_global_cleanup();
}

void PTZCtrl::turnUp()
{
    requestGET(cameraURL + "ptzctrl.cgi?-step=0&-act=up");
}

void PTZCtrl::turnDown()
{
    requestGET(cameraURL + "ptzctrl.cgi?-step=0&-act=down");
}

void PTZCtrl::turnLeft()
{
    requestGET(cameraURL + "ptzctrl.cgi?-step=0&-act=left");
}

void PTZCtrl::turnRight()
{
    requestGET(cameraURL + "ptzctrl.cgi?-step=0&-act=right");
}

void PTZCtrl::stop()
{
    requestGET(cameraURL + "ptzctrl.cgi?-act=stop");
}

void PTZCtrl::gotoPreset(int preset)
{
    requestGET(cameraURL + "preset.cgi?-act=goto&-number=" + std::to_string(preset));
}

void PTZCtrl::savePreset(int preset)
{
    requestGET(cameraURL + "preset.cgi?-act=set&-status=1&-number=" + std::to_string(preset));
}

void PTZCtrl::setInfrared(std::string status)
{
    requestGET(cameraURL + "param.cgi?cmd=setinfrared&-infraredstat=" + status);
}
