FROM archlinux

COPY . /root/system_monitor

RUN echo "Server = https://mirrors.ustc.edu.cn/archlinux/\$repo/os/\$arch"  > /etc/pacman.d/mirrorlist && \
    pacman -Syy --noconfirm && \
    pacman -S --noconfirm gcc gdb cmake git gtest protobuf grpc ninja pkg-config python tree && \
    cd /root/system_monitor && \
    ls -la /root/system_monitor && \
    tree /root/system_monitor

EXPOSE 25000

CMD bash /root/system_monitor/docker/start.sh

