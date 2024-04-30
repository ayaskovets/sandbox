func minJumps(arr []int) int {
	/*
		n = len(arr)
		O(n) space O(n) time
	*/
	indices := make(map[int][]int)
	for i, num := range arr {
			indices[num] = append(indices[num], i)
	}

	visited := make([]bool, len(arr))
	visited[0] = true

	queue := make([]int, 0)
	queue = append(queue, 0)

	for steps := 0; len(queue) != 0; steps++ {
			for size := len(queue); size > 0; size-- {
					i := queue[0]
					queue = queue[1:]
					if i == len(arr) - 1 {
							return steps
					}

					indices[arr[i]] = append(append(indices[arr[i]], i - 1), i + 1)
					for _, j := range indices[arr[i]] {
							if j >= 0 && j < len(arr) && !visited[j] {
									visited[j] = true
									queue = append(queue, j)
							}
					}
					indices[arr[i]] = []int{}
			}
	}
	return 0
}