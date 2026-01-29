#!/bin/bash

exec_name='sed'
filename=$1
output_name="$exec_name.tester"

compare () {

	if [diff -q $@] ; then
		echo "KO - Files differ"
	else
		echo "OK - Files match"
	fi

}

run_sed () {
	sed $@ > $output_name
}

run_cpp () {
	exec $exec_name $@
}

main () {
	if [ $# -ne 3 ] ; then
		echo "Usage: [input-file] <s1> <s2>"
	fi

	run_cpp $@
	run_sed $@
	compare "$filename.replace" $output_name
}

main $@
