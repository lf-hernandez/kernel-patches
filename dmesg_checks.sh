#!/bin/bash

# SPDX-License-Identifier: GPL-2.0
# Copyright(c) Shuah Khan <skhan@linuxfoundation.org>
#
# License: GPLv2

# Check if an argument is provided
if [ "$1" = "" ]; then
    echo "Usage: $0 <old_release>"
    exit 1
fi

# Get the current kernel release
current_release=$(uname -r)
echo "Start dmesg regression check for $current_release" > dmesg_checks_results

# Separator for better readability
echo "--------------------------" >> dmesg_checks_results

# Capture dmesg output for different log levels and compare with the previous version
capture_and_compare() {
    level="$1"
    file="$2"

    dmesg -t -l "$level" > "$current_release.$file"
    echo "dmesg $level regressions" >> dmesg_checks_results
    echo "--------------------------" >> dmesg_checks_results
    diff "$1.$file" "$current_release.$file" >> dmesg_checks_results
    echo "--------------------------" >> dmesg_checks_results
}

# Perform regression check for different log levels
capture_and_compare emerg dmesg_emerg
capture_and_compare crit dmesg_crit
capture_and_compare alert dmesg_alert
capture_and_compare err dmesg_err
capture_and_compare warn dmesg_warn

# Compare overall dmesg and kernel messages
diff "$1.dmesg" "$current_release.dmesg" >> dmesg_checks_results
echo "--------------------------" >> dmesg_checks_results
diff "$1.dmesg_kern" "$current_release.dmesg_kern" >> dmesg_checks_results
echo "--------------------------" >> dmesg_checks_results

echo "--------------------------" >> dmesg_checks_results
echo "End dmesg regression check for $current_release" >> dmesg_checks_results
