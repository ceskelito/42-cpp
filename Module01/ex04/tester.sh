#!/bin/bash

exec_name='./sed'
filename="$3"

compare() {
    local output_file="$1"
    local expected="$2"

    if diff -q "${output_file}" <(echo "${expected}") >/dev/null ; then
        echo "OK - Files match for \`$output_file'"
    else
        echo "KO - Files differ for \`$output_file'"
		echo
		diff "${output_file}" <(echo "${expected}")
    fi
}

run_sed() {
    sed "s/$1/$2/g" "$filename"
}

run_cpp() {
    "$exec_name" "$@"
}

main() {
    if [ $# -ne 3 ] ; then
        echo "Usage: $0 <old_string> <new_string> [input-file]"
        exit 1
    fi

    if [ ! -f "$filename" ]; then
        echo "Error: File '$filename' not found"
        exit 1
    fi

    if [ ! -x "$exec_name" ]; then
        echo "Error: Executable '$exec_name' not found or not executable"
        exit 1
    fi

    # Run C++ sed simulation
    if run_cpp "$@"; then
        compare "${filename}.replace" "$(run_sed "$1" "$2")"
    else
        echo "Error: C++ sed simulation failed"
        exit 1
    fi
}

main "$@"
