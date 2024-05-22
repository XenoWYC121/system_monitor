if [ ! -e /root/startup ]
then
  # 如果文件不存在
  touch /root/startup #创建这个文件
  mkdir /root/system_monitor/build -p
  cd /root/system_monitor/build || return
  pwd
  rm -rf /root/system_monitor/build/*
  cmake .. -G Ninja -D IN_DOCKER_ENV=on
  cmake --build . -j 6
fi
nohup /root/system_monitor/build/src/service/cpu_service/cpu_service &
echo "run cpu info service"
nohup /root/system_monitor/build/src/service/memory_service/memory_service &
echo "run memory info service"
/root/system_monitor/build/src/server/grpc_server