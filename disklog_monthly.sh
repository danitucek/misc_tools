#!bin/bash

while true
do
# The first part parses the short form on the month name, it will be used in the output filenames to separate each month. Both the iostat and dstat has a separate log filename appended by the actual month.
	month=$(date +%b)
	iostat_output="iostat_log_${month}"
	dstat_output="dstat_log_${month}"
 
# Put a formatted datestamp in both files on each iteration. The output format looks like this: 'January 1, 1970 12:34:56'.	
	date '+%B %d, %Y %H:%M:%S' >> iostat_output
	date '+%B %d, %Y %H:%M:%S' >> dstat_output
	iostat -xy 1 1 | awk '/Device/ || /sda/ || /sdb/ {print}' >> $iostat_output
	dstat -cdngy -D sda,sdb 1 2 | awk 'NR!=3 {print}' >> $dstat_output
	#sleep 1   #uncomment and adjust for your needs to slow down the logging
done
