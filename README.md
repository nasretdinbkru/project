### Проектная работа
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
  }
]
```
## Сборка 

1. Клонировать проект:
```
git clone https://github.com/nasretdinbkru/project.git
```
2. Перейти в каталог с файлами исходных кодов:
```
cd project/hw_info_rest_api/
```
3. Установить библиотеку oatpp:
```
mkdir tmp
cd tmp
git clone --depth=1 https://github.com/oatpp/oatpp
cd oatpp
mkdir build
cd build
cmake -DOATPP_BUILD_TESTS=OFF -DCMAKE_BUILD_TYPE=Release ..
sudo make install -j 6
cd ../../../
rm -rf tmp
```
4. Установить библиотеку libudev
```
sudo apt install libudev-dev
```
5. Создать каталог для сборки и перейти в него:
```
mkdir build
cd build

```
6. Создать сборочные файлы:
```
cmake -S ../ -B .
```
7. Собрать проект:
```
cmake --build .
```
8. Запустить исполняемый файл сервиса:
```
./hw_info_rest_api-exe 
```
