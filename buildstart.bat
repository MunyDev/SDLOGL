@echo off
cd nginx
echo  [32mStarting Build[0m
start cmd /X /C "cd C:\Users\avadh\emtest\nginx\ && nginx && nginx -s stop"
