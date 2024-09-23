#ifndef WIFIMANAGERANDOTAUPDATE_H
#define WIFIMANAGERANDOTAUPDATE_H

class WifiManager {
public:
    static void init();
    static void update();
};

class OTAUpdate {
public:
    static void init();
    static void handleUpdate();
};

#endif // WIFIMANAGERANDOTAUPDATE_H

