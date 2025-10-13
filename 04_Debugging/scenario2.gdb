set pagination off

break range.c:43 if step > 0
commands
silent


set $element_count = $element_count + 1



if $element_count >= 28 && $element_count <= 35
    printf "@@@=== Element #%d ===\n", $element_count
    printf "@@@start = %ld\n", start
    printf "@@@end = %ld\n", end
    printf "@@@step = %ld\n", step
    printf "@@@current i = %ld\n\n", i
end

continue
end

break range.c:47 if step < 0
commands
silent

set $element_count = $element_count + 1


if $element_count >= 28 && $element_count <= 35
    printf "@@@=== Element #%d ===\n", $element_count
    printf "@@@start = %ld\n", start
    printf "@@@end = %ld\n", end
    printf "@@@step = %ld\n", step
    printf "@@@current i = %ld\n\n", i
end

continue
end


set $element_count = 0


run -100 100 3 > /dev/null

continue
