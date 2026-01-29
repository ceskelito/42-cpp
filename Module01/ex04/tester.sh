#!/bin/bash

set -euo pipefail

EXEC_NAME='./sed'

compare() {
    local output_file="$1"
    local expected="$2"

    if diff -q "${output_file}" <(echo "${expected}") >/dev/null ; then
        echo "OK - Files match for \`$output_file'"
    else
        echo "KO - Files differ for \`$output_file'"
		echo
		diff "${output_file}" <(echo "${expected}")
		return 1
    fi
}

run_sed() {
	
	local old="$1"
	local new="$2"
	local input_file="$3"

    sed "s|${old}|${new}|g" "${input_file}"
}

run_cpp() {
    "$EXEC_NAME" "$@"
}

main() {
    if [ $# -ne 3 ] ; then
        echo "Usage: $0 <old_string> <new_string> [input-file]"
        exit 1
    fi
	
	local old="$1"
	local new="$2"
	local input_file="$3"
	local result_file="${input_file}.replace"

    if [ ! -f "$input_file" ]; then
        echo "Error: File '$input_file' not found"
        exit 1
    fi

    if [ ! -x "$EXEC_NAME" ]; then
        echo "Error: Executable '$EXEC_NAME' not found or not executable"
        exit 1
    fi

    # Run C++ sed simulation
    if run_cpp "$@"; then
        compare "${result_file}" "$(run_sed "$old" "$new" "$input_file")"
    else
        echo "Error: C++ sed simulation failed"
        exit 1
    fi
}

main "$@"
