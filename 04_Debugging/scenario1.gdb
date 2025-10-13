set pagination off

break range.c:43 if step > 0

commands 1
silent
if (i % 5 == 0)
    printf "@@@=== Element %ld ===\n", i
    printf "@@@start = %ld\n", start
    printf "@@@end = %ld\n", end  
    printf "@@@step = %ld\n", step
end
continue
end

break range.c:47 if step < 0
commands
silent
if (i % 5 == 0)
    printf "@@@=== Element %ld ===\n", i
    printf "@@@start = %ld\n", start
    printf "@@@end = %ld\n", end  
    printf "@@@step = %ld\n", step
end
continue
end

run 1 12 > /dev/null

continue
