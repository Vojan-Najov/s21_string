#!/bin/bash

docker build . -t s21_string_test:1.0 -f ./tests/scripts/Dockerfile
docker run s21_string_test:1.0
