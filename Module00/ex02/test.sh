#!/usr/bin/bash

cleanup() {
    rm -f "$old_notime" "$new_notime"
}

trap cleanup EXIT

create_files_for_diff() {
    local old_log="19920104_091532.log"
    local new_log=$(ls -t | grep -E '^[0-9]{8}_[0-9]{4,6}\.log$' | head -n 1)

    old_notime=$(mktemp)
    new_notime=$(mktemp)

    awk '{print $2}' "$old_log" > "$old_notime"
    awk '{print $2}' "$new_log" > "$new_notime"
}

check_diff() {
    create_files_for_diff

    if diff -q "$old_notime" "$new_notime" > /dev/null; then
        echo "OK DIFF"
    else
        echo "KO DIFF"
        diff --color=always "$old_notime" "$new_notime"
    fi
}

check_diff
