## Проектная работа
<p>Легкий REST API сервер на базе фреймворка oatpp https://github.com/oatpp/oatpp.
</p>
<p>
Реализована выдача данных по GET-запросу на следующие endpoints:
</p>

**/ipv4**
```json
[
  {
    "if_name": "lo",
    "ipv4add": "127.0.0.1",
    "broadcat": "",
    "prefix": 8,
    "mac_addr": "7f:00:00:01:08:00"
  },
  {
    "if_name": "enp2s0",
    "ipv4add": "192.168.1.104",
    "broadcat": "192.168.1.255",
    "prefix": 24,
    "mac_addr": "c0:a8:01:68:08:00"
  }
]
```

**/meminfo**
```json
{
  "memTotal": "32557860 kB",
  "memFree": "18537164 kB",
  "memAvailable": "23143552 kB",
  "swapTotal": "999420 kB",
  "swapFree": "999420 kB"
}
```

**/hddinfo**
```json
[
  {
    "deviceName": "\/dev\/sde",
    "model": "Samsung_SSD_870_EVO_1TB",
    "serial": "S5Y2NF0R905381F",
    "diskSize": "500"
  },
  {
    "deviceName": "\/dev\/sda",
    "model": "Samsung_SSD_860_EVO_500GB",
    "serial": "S3YANB0NB33662K",
    "diskSize": "250"
  }
]
```
**/cpuinfo**
```json
[
  {
    "model": " Intel(R) Core(TM) i5-2400 CPU @ 3.10GHz",
    "coreid": " 0",
    "frequency": " 2011.141",
    "vendor": " GenuineIntel"
  },
  {
    "model": " Intel(R) Core(TM) i5-2400 CPU @ 3.10GHz",
    "coreid": " 1",
    "frequency": " 2707.603",
    "vendor": " GenuineIntel"
  },
  {
    "model": " Intel(R) Core(TM) i5-2400 CPU @ 3.10GHz",
    "coreid": " 2",
    "frequency": " 2626.571",
    "vendor": " GenuineIntel"
  },
  {
    "model": " Intel(R) Core(TM) i5-2400 CPU @ 3.10GHz",
    "coreid": " 3",
    "frequency": " 2358.121",
    "vendor": " GenuineIntel"
  }
]
```
