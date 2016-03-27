#!/usr/bin/env bash


usage() {
    echo "Usage:"
    echo " $0 [ --fifo=<path> ] [ --enable ] [ --color=red|green|blue ] [ --rate=0..5 ]"
    echo " $0 [ --fifo=<path> ] --disable"
    echo " $0 [ --fifo=<path> ] [ --get-state ] [ --get-color ] [ --get-rate ]"
    echo " $0 [ --help | -h ]"
    echo
    echo "Default fifo path is /tmp/fifo. Color and rate options work only if LED enabled"
}

validate_options() {
    if ! [ -p "$fifo" ]; then
        echo "Fifo doesn't exist or it isn't a named pipe file: $fifo" >&2
        exit 3
    fi

    if [ ${options[enable]+_} ] && [ ${options[disable]+_} ]; then
        echo "You couldn't enable and disable LED at the same time" >&2
        exit 3
    fi

    if [ ${options[disable]+_} ] && [ ${#options[@]} -gt 1 ]; then
        echo "You couldn't do anything else then disabling LED" >&2
        exit 3
    fi

    if ! [ ${options[disable]+_} ]; then
        validate_color
        validate_rate
    fi
}

validate_color() {
    if ! [ ${options[color]+_} ]; then
        return 0
    fi

    case "${options[color]}" in
        red|green|blue)
            ;;
        *)
            echo "Syntax error: Unknown color option: ${options[color]}" >&2
            exit 3
    esac
}

validate_rate() {
    if ! [ ${options[rate]+_} ]; then
        return 0
    fi

    if ! [ "${options[rate]}" -eq "${options[rate]}" ] 2>/dev/null
    then
        echo "Syntax error: rate should be integer value between 0 and 5: ${options[rate]}" >&2
        exit 3
    fi

    if [ "${options[rate]}" -lt 0 ] && [ "${options[rate]}" gt 5 ]; then
        echo "Syntax error: rate should be integer value between 0 and 5: ${options[rate]}" >&2
        exit 3
    fi
}

generate_commands() {
    if [ ${options[disable]+_} ]; then
        commands[0]="set-led-state off"
        return 0
    fi

    if [ ${options[enable]+_} ]; then
        commands[0]="set-led-state on"
    fi

    if [ ${options[color]+_} ]; then
        commands["${#commands[@]}"]="set-led-color ${options[color]}"
    fi

    if [ ${options[rate]+_} ]; then
        commands["${#commands[@]}"]="set-led-rate ${options[rate]}"
    fi

    if [ ${options[get-state]+_} ]; then
        commands["${#commands[@]}"]="get-led-state"
    fi

    if [ ${options[get-color]+_} ]; then
        commands["${#commands[@]}"]="get-led-color"
    fi

    if [ ${options[get-rate]+_} ]; then
        commands["${#commands[@]}"]="get-led-rate"
    fi
}

# set defaults
fifo=/tmp/fifo
declare -A options


i=$(($# + 1)) # index of the first non-existing argument
declare -A longoptspec
longoptspec=( [fifo]=1 [enable]=0 [color]=1 [rate]=1 [disable]=0 [get-state]=0 [get-color]=0 [get-rate]=0 )
optspec=":h-:"
while getopts "$optspec" opt; do
while true; do
    case "${opt}" in
        -) #OPTARG is name-of-long-option or name-of-long-option=value
            if [[ ${OPTARG} =~ .*=.* ]] # with this --key=value format only one argument is possible
            then
                opt=${OPTARG/=*/}
                ((${#opt} <= 1)) && {
                    echo "Syntax error: Invalid long option '$opt'" >&2
                    exit 2
                }
                if (($((longoptspec[$opt])) != 1))
                then
                    echo "Syntax error: Option '$opt' does not support this syntax." >&2
                    exit 2
                fi
                OPTARG=${OPTARG#*=}
            else #with this --key value1 value2 format multiple arguments are possible
                opt="$OPTARG"
                ((${#opt} <= 1)) && {
                    echo "Syntax error: Invalid long option '$opt'" >&2
                    exit 2
                }
                OPTARG=(${@:OPTIND:$((longoptspec[$opt]))})
                ((OPTIND+=longoptspec[$opt]))
                # echo $OPTIND
                ((OPTIND > i)) && {
                    echo "Syntax error: Not all required arguments for option '$opt' are given." >&2
                    exit 3
                }
            fi

            continue #now that opt/OPTARG are set we can process them as
            # if getopts would've given us long options
            ;;
        fifo)
            fifo=$OPTARG
            ;;
        enable)
            options[enable]=true
            ;;
        disable)
            options[disable]=true
            ;;
        color)
            options[color]=$OPTARG
            ;;
        rate)
            options[rate]=$OPTARG
            ;;
        get-state)
            options[get-state]=true
            ;;
        get-color)
            options[get-color]=true
            ;;
        get-rate)
            options[get-rate]=true
            ;;
        h|help)
            usage
            exit 0
            ;;
        ?)
            echo "Syntax error: Unknown short option '$OPTARG'" >&2
            exit 2
            ;;
        *)
            echo "Syntax error: Unknown long option '$opt'" >&2
            exit 2
            ;;
    esac
break; done
done

echo "fifo=$fifo"
echo "enable=${options[enable]}"
echo "disable=${options[disable]}"
echo "color=${options[color]}"
echo "rate=${options[rate]}"
echo "get-state=${options[get-state]}"
echo "get-color=${options[get-color]}"
echo "get-rate=${options[get-rate]}"

validate_options

# Если мы оказались тут значит входные данные корректны
# Можно подготавливать инфраструктуру
fifoin="/tmp/$$_in"
fifoout="/tmp/$$_out"

trap "rm -f $fifoin $fifoout" EXIT

[ -p "$fifoin" ] || mkfifo "$fifoin"
[ -p "$fifoout" ] || mkfifo "$fifoout"

declare -a commands
declare -a response

generate_commands

echo ${#commands[@]}
echo -e "${commands[@]}"

# End of file