# ptzctrl
Wrapper for remote control of hi3510 based IP cameras.

## Requirements

libcurl

## Usage

```c++
PTZCtrl ptz("http://IPCAMERA_ADDRESS/web/cgi-bin/hi3510/", "admin", "admin");
ptz.turnLeft();
ptz.stop();
```
