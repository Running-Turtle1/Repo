def quick_sort(arr):
    if len(arr) <= 1:
        return arr
    pivot = arr[0]
    return quick_sort([x for x in arr[1:] if x < pivot]) + [pivot] + quick_sort([x for x in arr[1:] if x >= pivot])

print(quick_sort([5, 4, 3, 2, 1, 8, -1  ]))