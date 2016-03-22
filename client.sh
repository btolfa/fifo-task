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

# set defaults
fifo=/tmp/fifo
to_enable=false
to_disable=false
set_color=
set_rate=
get_state=false
get_color=false
get_rate=false

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
            to_enable=true
            ;;
        disable)
            to_disable=true
            ;;
        color)
            set_color=$OPTARG
            ;;
        rate)
            set_rate=$OPTARG
            ;;
        get-state)
            get_state=true
            ;;
        get-color)
            get-color=true
            ;;
        get-rate)
            get-rate=true
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
echo "enable=$to_enable"
echo "disable=$to_disable"
echo "color=$set_color"
echo "rate=$set_rate"
echo "get-state=$get_state"
echo "get-color=$get_color"
echo "get-rate=$get_rate"

# End of file