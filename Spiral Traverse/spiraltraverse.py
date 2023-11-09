def spiralTraverse(array):
    rows =  len(array)
    cols = len(array[0])
    total_elem = rows * cols
    counter = 0
    result = []
    visited = set()
    i_row = 0
    i_col = 0
    while counter < total_elem:
            
        while i_col < cols and ((i_row,i_col) not in visited) :
            visited.add((i_row,i_col))
            result.append(array[i_row][i_col])
            counter += 1
            i_col += 1
        i_row += 1
        i_col -= 1
        while i_row < rows and ((i_row,i_col) not in visited) :
            visited.add((i_row,i_col))
            result.append(array[i_row][i_col])
            counter += 1
            i_row += 1
        i_col -= 1
        i_row -= 1
        while i_col >= 0 and ((i_row,i_col) not in visited) :
            visited.add((i_row,i_col))
            result.append(array[i_row][i_col])
            counter += 1
            i_col -= 1 
        i_row -= 1
        i_col += 1
        while i_row >= 0 and ((i_row,i_col) not in visited) :
            visited.add((i_row,i_col))
            result.append(array[i_row][i_col])
            counter += 1
            i_row -= 1 
        
        i_col += 1
        i_row += 1
    return result


arr= [
        [1, 2, 3, 4],
        [12, 13, 14, 5],
        [11, 16, 15, 6],
        [10, 9, 8, 7]
      ]
spiralTraverse(arr)
