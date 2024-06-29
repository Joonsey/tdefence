#!/bin/sh

docker build -t windows-builder .
docker run --name=windows-builder windows-builder &

sleep 2

docker cp windows-builder:/build/main.exe .
docker kill windows-builder
