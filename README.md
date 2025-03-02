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
## Платформы
* Debian 12
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
## Создание сервиса
8. Перейти в корневой каталог проекта
```
cd ../
```
9. Создать каталог для файла сервиса и скопировать в него файл сервиса
```
sudo mkdir /opt/rest_api_srv
sudo cp build/hw_info_rest_api-exe /opt/rest_api_srv/
```
10. Скопировать сервисный файл в каталог /etc/systemd/system, добавить сервис в автозапуск и запустить сервис
```
sudo cp utility/simple_rest_api_srv.service /etc/systemd/system
sudo systemctl enable simple_rest_api_srv.service
sudo systemctl start simple_rest_api_srv.service
```
11. Для отключения сервиса выполнить
```
sudo systemctl stop simple_rest_api_srv.service
sudo systemctl disable simple_rest_api_srv.service
sudo systemctl daemon-reload
```
12. Или запустить исполняемый файл сервиса:
```
/opt/hw_info_rest_api-exe 
```


## Пример использования
```
wget -O - http://127.0.0.1:8000/cpuinfo
--2025-02-14 21:24:17--  http://127.0.0.1:8000/cpuinfo
Подключение к 127.0.0.1:8000... соединение установлено.
HTTP-запрос отправлен. Ожидание ответа… 200 OK
Длина: 586 [application/json]
Сохранение в: «STDOUT»

-                                       0%[                                                                       ]       0  --.-KB/s               [
  {
    "model": " Intel(R) Core(TM) i5-2400 CPU @ 3.10GHz",
    "coreid": " 0",
    "frequency": " 2333.116",
    "vendor": " GenuineIntel"
  },
  {
    "model": " Intel(R) Core(TM) i5-2400 CPU @ 3.10GHz",
    "coreid": " 1",
    "frequency": " 2153.606",
    "vendor": " GenuineIntel"
  },
  {
    "model": " Intel(R) Core(TM) i5-2400 CPU @ 3.10GHz",
    "coreid": " 2",
    "frequency": " 3082.776",
    "vendor": " GenuineIntel"
  },
  {
    "model": " Intel(R) Core(TM) i5-2400 CPU @ 3.10GHz",
    "coreid": " 3",
    "frequency": " 2499.064",
    "vendor": " GenuineIntel"
  }
-                                     100%[======================================================================>]     586  --.-KB/s    за 0s      

/2025-02-14 21:24:17 (86,9 MB/s) - записан в stdout [586/586]
```

