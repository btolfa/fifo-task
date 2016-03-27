# Тестовое задание на С++

## Как собрать

Для сборки проекта используется [cmake 3.4](https://cmake.org)

    git clone --recursive https://github.com/btolfa/fifo-task.git
    cd fido-task
    mkdir build
    cd build
    cmake .. -DBUILD_TESTS=ON
    cmake --build .

Собранное приложение - `build/fifoserver`

## Тесты

Чтобы запустить тесты, нужно собрать проект с опцией `-DBUILD_TESTS=ON` и из сборочной директории вызывать `ctest`

## Как использовать
Сервер:

    $ fifoserver --help
    Usage:
        ./fifoserver [OPTION...] - LED FIFO Server

        -f, --fifo /tmp/fifo  path to fifo (will be created)
        -h, --help            Print help

Клиент:

    $ client.sh --help
    Usage:
        ./client.sh [ --fifo=<path> ] [ --enable ] [ --color=red|green|blue ] [ --rate=0..5 ]
        ./client.sh [ --fifo=<path> ] --disable
        ./client.sh [ --fifo=<path> ] [ --get-state ] [ --get-color ] [ --get-rate ]
        ./client.sh [ --help | -h ]
    
    Default fifo path is /tmp/fifo. Color and rate options work only if LED enabled

* Код возврата если не удалось (`FAILED`) выполнить `set-led-*` команду - 4
* Код возврата если не удалось (`FAILED`) выполнить `get-led-*` команду - 8


## Пример использования

Сначала нужно запустить сервер

    $ fifoserver

Теперь в другом терминале можно воспользоваться `client.sh`:

    $ client.sh --enable --color=red --rate=2 --get-state --get-color --get-rate
    state:on
    color:red
    rate:2