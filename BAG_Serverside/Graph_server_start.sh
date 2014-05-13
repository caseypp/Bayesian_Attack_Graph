start()
{
    echo "start testService"
    /root/BAG_Risk_Assessment/BAGRiskd
    exit 0;
}
stop()
{

    echo -n "stop testService"
    if pkill testService
        then

        echo  "              [ok]"

    else

        echo  "              [failed]"

    fi

}

case "$1" in
start)
    start
    ;;
stop)
    stop
    ;;
restart)
    stop
    start
    ;;
*)
    echo "usage: $0 start|stop|restart"
    exit 0;
esac