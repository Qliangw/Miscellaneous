#!/bin/bash

# 该脚本默认产生6点-24点随机运行时间
# 配置签到时间范围
STARTTIME=6
ENDTIME=24

# docker文件夹下的哔哩哔哩文件夹的路径
SCRIPTHOME=/appdata/config

# 存放哔哩哔哩定时任务的路径
# 即:- /appdata/config:/config中的/appdata/config
CRONPATH=$SCRIPTHOME

# dokcer id
DOCKERID=docker ps命令显示的id
DOCKERNAME=docker ps命令显示的名字
#############################################

# 随机数 产生随机分钟和小时
DIFF=$(($ENDTIME-$STARTTIME))
RANDMINUTE=$(($RANDOM%60))
RANDHOUR=$(($RANDOM%$DIFF+$STARTTIME))
#进入脚本路径
cd $SCRIPTHOME
if [ ! -d "./rand_run" ]; then
mkdir rand_run
fi
cd $SCRIPTHOME/rand_run
# 创建定时任务脚本
if [ ! -f "./bh-crontab" ]; then
touch bh-crontab
fi
echo $[RANDMINUTE] $[RANDHOUR] "* * * /app-conf/bh-run.sh" > $SCRIPTHOME/rand_run/bh-crontab
# 备份
# cp $CRONPATH/bh-crontab $SCRIPTHOME/bh-crontab.bak
# 移动脚本
mv $SCRIPTHOME/rand_run/bh-crontab $CRONPATH/bh-crontab
#docker 重载定时任务
docker exec $DOCKERNAME crontab /config/bh-crontab
echo "Done!"
exit 0
