func canReach(arr []int, start int) bool {
	/*
		n = len(arr)
		O(n) stack space O(n) time
	*/
	if start < 0 || start >= len(arr) || arr[start] < 0 {
			return false
	}
	if arr[start] == 0 {
			return true
	}

	l, r := start - arr[start], start + arr[start]
	arr[start] *= -1
	reached := canReach(arr, l) || canReach(arr, r)
	arr[start] *= -1
	return reached
}