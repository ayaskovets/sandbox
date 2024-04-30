#!/usr/local/bin/bash

#
# Copyright (c) 2020-present, Andrei Yaskovets
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.
#

declare -a _workers=( 1 2 3 4 5 )
declare -a _jobs=( "1" "2" "3" "4" "5" "6" "7" "8" "9" "10" )

#######################################
#	FIFO pop
#	Arguments:
#		1) an array
#######################################
dequeue()
{
	local -n _queue=$1
	unset _queue[0]
	_queue=( "${_queue[@]}" )
}

#######################################
#	FIFO push
#	Arguments:
#		1) an array
#		2) a value to push
#######################################
enqueue()
{
	local -n _queue=$1
	_queue=( "${_queue[@]}" "$2" )
}

#######################################
#	Worker function wrapper
#	Arguments:
#		1) worker id [0-255]
#		2) job id
#######################################
do_work()
{
	echo "worker #$1: job #$2 is started"
	sleep $1
	echo "worker #$1: job #$2 is done"
	exit $1
}

#######################################
#	Trap for preventing the script form hanging on SIGINT
#	Arguments:
#		None
#######################################
cleanup() {
	kill -9 $(jobs -p) >& /dev/null
	exit 1
}
trap cleanup SIGINT

# worker managing loop
while [ ! ${#_jobs[@]} -eq 0 ]; do
	worker=${_workers[0]}
	job=${_jobs[0]}

	dequeue _workers
	dequeue _jobs

	do_work ${worker} ${job} &

	if [[ ${#_workers[@]} -eq 0 ]]; then
		wait -n $(jobs -p)
		enqueue _workers "$?"
	fi
done

wait
