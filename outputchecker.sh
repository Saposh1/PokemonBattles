#!/bin/bash
cd /home/ise/PokemonPart1ScriptOutputChecker
make
# The tail command hangs forever and does not produce output, thus
# prog will wait.
tail -f /dev/null | valgrind --log-file="valgrindLOG" --show-leak-kinds=all /home/ise/PokemonPart1ScriptOutputChecker/PokemonsBattle 4 4 FullRunData.txt  &
# Capture the PIDs of the two processes
PROGPID=$!
TAILPID=$(jobs -p %+)
# Hijack the write end of the pipe (standard out of the tail command).
# Afterwards, the tail command can be killed.
exec 3>/proc/$TAILPID/fd/1
kill $TAILPID
# Now read line by line from our own standard input
while IFS= read -r line
do
    # Check the state of prog ... we wait while it is Running.  More
    # complex programs than prog might enter other states which you
    # need to take care of!
    state=$(ps --no-headers -wwo stat -p $PROGPID)
    while [[ "x$state" == xR* ]]
    do
        sleep 0.05
        state=$(ps --no-headers -wwo stat -p $PROGPID)
    done
    # Now prog is waiting for input. Display our line, and then send
    # it to prog.
    echo $line
    echo $line >&3
done
# Close the pipe
exec 3>&-

