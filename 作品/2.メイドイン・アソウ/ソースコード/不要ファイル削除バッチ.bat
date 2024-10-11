@echo off
del Log.txt
rd /s /q x64\Debug
rd /s /q x64\Release
rd /s /q .vs\MyGame\v16\ipch
rd /s /q .vs\MyGame\v17\ipch
