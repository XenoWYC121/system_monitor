sudo docker build -t monitor .
sudo docker run --name monitor1 -dit -p 25000:25000 monitor