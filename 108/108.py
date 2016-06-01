def max_sub_array(v):
    n = len(v)

    if n == 1:
        result = v[0]
    else:
        summ = 0
        max_left = 0
        for x in v[n/2::-1]:
            summ += x
            max_left = max(max_left, summ)
        
        summ = 0
        max_right = 0


    return result

print max_sub_array([3, -9, 1, 2, 3])
print max_sub_array([-2, 1, -3, 4, -1, 2, 1, -5, 4])

v = [-2, 1, -3, 4, -1, 2, 1, -5, 4]
