#!/bin/bash
dmesg -t > dmesg_$(uname -r)
dmesg -t -k > dmesg_$(uname -r)_kernel
dmesg -t -l emerg > dmesg_$(uname -r)_emerg
dmesg -t -l alert > dmesg_$(uname -r)_alert
dmesg -t -l crit > dmesg_$(uname -r)_crit
dmesg -t -l err > dmesg_$(uname -r)_err
dmesg -t -l warn > dmesg_$(uname -r)_warn
dmesg -t -l info > dmesg_$(uname -r)_info
