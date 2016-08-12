#~/bin/bash

echo "Starting master"
MESOS_PATH=/home/prateeks/code/mesos/build/src

$MESOS_PATH/mesos-master --work_dir=/tmp  --ip='127.0.0.1' &

echo "Cleaning up Slave metadata"

#sudo rm -f ./meta/slaves/latest

echo "Starting slaves"
sudo $MESOS_PATH/mesos-slave --master='127.0.0.1:5050' --work_dir=/tmp &

echo "Starting framework"

FMWK_PATH=/home/prateeks/code/mesos/build/src

#sudo $FMWK_PATH/balloon-framework --master='127.0.0.1:5050' --task_memory_usage_limit=2800MB --task_memory=10MB &

#Use the long-running framework instead of the balloon framework because the LL application uses the public MESOS API whereas the balloon app uses internal messages. There is no explicit event handling in balloon, for instance.

$FMWK_PATH/long-lived-framework --master='127.0.0.1:5050'
