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
root@debian:~/# git clone https://github.com/nasretdinbkru/project.git
Клонирование в «project»…
remote: Enumerating objects: 135, done.
remote: Counting objects: 100% (135/135), done.
remote: Compressing objects: 100% (88/88), done.
remote: Total 135 (delta 62), reused 103 (delta 38), pack-reused 0 (from 0)
Получение объектов: 100% (135/135), 31.65 KiB | 753.00 KiB/s, готово.
Определение изменений: 100% (62/62), готово.
```
2. Перейти в каталог с файлами исходных кодов:
```
root@debian:~/# cd project/hw_info_rest_api/
root@debian:~/project/hw_info_rest_api#
```
3.Установить библиотеку oatpp:
```
root@debian:~/project/hw_info_rest_api# utility/install-oatpp-modules.sh 
```
4.Установить библиотеку libudev
```
root@debian:~/project/hw_info_rest_api/build# apt install libudev-dev
```
5. Создать каталог для сборки и перейти в него:
```
root@debian:~/# mkdir build
root@debian:~/project/hw_info_rest_api# cd build
```
5. Создать сборочные файлы:
```
root@debian:~/project/hw_info_rest_api/build# cmake -S ../ -B .
```
6. Собрать проект:
```
root@debian:~/target/project/hw_info_rest_api/build# cmake --build .
```
7. Запустить исполняемый файл сервиса:
```
root@debian:~/project/hw_info_rest_api/build# ./hw_info_rest_api-exe 
 I |2025-02-14 21:21:53 1739557313789262| MyApp:Server running on port 8000
```
8. В другом терминале выполнить http-запрос, например, на конечную точку /cpuinfo:
```
root@debian:~/# wget -O - http://127.0.0.1:8000/cpuinfo
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

