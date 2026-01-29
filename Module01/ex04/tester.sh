#!/bin/bash

exec_name='./sed'
filename=$3

compare () {

	if diff -q "$1" <(echo "$2") >/dev/null ; then
		echo "OK - Files match"
	else
		echo "KO - Files differ"
	fi
}

run_sed () {
	sed "s/$1/$2/g" $filename
}

run_cpp () {
	$exec_name $@
}

main () {
	if [ $# -ne 3 ] ; then
		echo "Usage: ./tester.sh <old_string> <new_string> [input-file]"
	fi

	if run_cpp $@ ; then
		compare "$filename.replace" "$(run_sed $@)"
	fi
}

main $@
