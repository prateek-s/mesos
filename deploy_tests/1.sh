#~/bin/bash

echo "Starting master"

./mesos-master --work_dir=/tmp  --ip='127.0.0.1'

echo "Cleaning up Slave metadata"

sudo rm -f ./meta/slaves/latest

echo "Starting slaves"
sudo ./mesos-slave --master='127.0.0.1:5050' --work_dir=.

echo "Starting framework"

sudo ./balloon-framework --master='127.0.0.1:5050' --task_memory_usage_limit=2800MB --task_memory=10MB

