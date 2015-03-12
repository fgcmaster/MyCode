#!/bin/bash

CMD_NAME=$1
PROGRAM_NAME=$0

printUsage()
{
	echo " 输入参数错误，只能输入一个参数"
	echo " killCmd  cmd"
	exit 1
}

killCmd()
{
	ps -ef | grep ${CMD_NAME} | grep -v ${PROGRAM_NAME} | grep -v grep | awk -F" " '{print $2}' | xargs kill
	exit 1
}


if [ $# -ne 1 ]
then
	printUsage
fi

killCmd
